#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void comparison_counting_sort(std::vector<int> &vec)
{
    std::vector<int> tmp(vec.size(), 0);

    for (int i = 0; i < tmp.size(); i++)
    {
        int count = 0;
        int occurrence = 0;

        for (int j = 0; j < tmp.size(); j++)
        {
            if (j < i && vec[j] == vec[i])
            {
                occurrence++;
            }

            if (vec[j] < vec[i])
            {
                count++;
            }
            else if (j > i)
            {
                tmp[j]++;
            }
        }

        tmp[i] = count + occurrence;
    }

    std::vector<int> result(vec.size(), 0);

    for (int i = 0; i < result.size(); i++)
    {
        result[tmp[i]] = vec[i];
    }

    vec = result;
}

void distribution_counting_sort(std::vector<int> &vec)
{
    int u = *std::max_element(vec.begin(), vec.end());
    int l = *std::min_element(vec.begin(), vec.end());
    int range = u - l + 1;

    std::vector<int> count(range, 0);

    for (int i : vec)
    {
        count[i - l]++;
    }

    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    std::vector<int> tmp(vec.size());

    for (int i = vec.size() - 1; i >= 0; i--)
    {
        tmp[count[vec[i] - l] - 1] = vec[i];
        count[vec[i] - l]--;
    }

    vec = tmp;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "No input file" << std::endl;

        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;

    if (!std::getline(file, line))
    {
        std::cerr << "Failed to read a line from the file." << std::endl;
    }

    std::stringstream stream(line);
    std::string number;

    std::vector<int> vec;

    while (stream >> number)
    {
        vec.push_back(std::stoi(number));
    }

    std::vector<int> vec2 = vec;

    std::cout << "comparison counting sort:" << std::endl;
    comparison_counting_sort(vec);
    for (int i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "distribution counting sort:" << std::endl;
    distribution_counting_sort(vec2);
    for (int i : vec2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 1;
}
