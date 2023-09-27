#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string bruteforce(std::vector<std::string> list)
{
    std::vector<unsigned int> count;
    count.resize(list.size(), 0);

    int highest_index = 0;

    for (int i = 0; i < list.size(); i++)
    {
        for (int j = i; j < list.size(); j++)
        {
            if (list[j] == list[i])
            {
                count[i]++;
            }
        }

        if (count[i] > count[highest_index])
        {
            highest_index = i;
        }
    }

    return list[highest_index];
}

std::string presort(std::vector<std::string> list)
{
    int mode_frequency = 0;
    std::string mode_value;

    std::sort(list.begin(), list.end());

    for (int i = 0; i < list.size();)
    {
        std::string run_value = list[i];
        int run_lenght = 1;

        for (; i + run_lenght < list.size() && list[i + run_lenght] == run_value; run_lenght++)
        {
            run_lenght++;
        }

        if (run_lenght > mode_frequency)
        {
            mode_frequency = run_lenght;
            mode_value = run_value;
        }

        i += run_lenght;
    }

    return mode_value;
}

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Please provide a file to read from\n";
        return EXIT_FAILURE;
    }

    std::vector<std::string> tmp;
    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        tmp.push_back(line);
    }

    std::string result = bruteforce(tmp);
    std::cout << result << "\n";

    result = presort(tmp);
    std::cout << result << "\n";

    return 0;
}
