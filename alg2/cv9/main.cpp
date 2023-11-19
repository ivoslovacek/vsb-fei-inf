#include <iostream>
#include <vector>

int maximum_coins(std::vector<std::vector<int>> arr)
{
    int max = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            int current = arr[i][j];
            int current_i = 0;
            int current_j = 0;

            if (i - 1 >= 0)
            {
                current_i = arr[i - 1][j];
            }

            if (j - 1 >= 0)
            {
                current_j = arr[i][j - 1];
            }

            current += std::max(current_i, current_j);
            std::cout << current << " ";

            arr[i][j] = current;
        }

        std::cout << std::endl;
    }

    return arr.back().back();
}

int main(int argc, char **argv)
{
    std::vector<std::vector<int>> arr = {{0, 1, 0, 0, 1}, {1, 0, 0, 1, 0}, {1, 1, 1, 0, 0}, {0, 1, 0, 1, 1}};

    int count = maximum_coins(arr);

    std::cout << "Maximum ammount: " << count << std::endl;

    return 0;
}
