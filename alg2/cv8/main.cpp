#include <iostream>
#include <string>
#include <fstream>
#include "u_map.hpp"

/* Prohledat vsechna unikatni slova a vratit nejhorsi hledani
 * (napr. word: the, checked buckets: 99)*/

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    u_map<std::string, std::string> map(17509);

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string word;
    while (file >> word)
    {
        map[word] = word;
    }

    std::string str = "the";

    std::cout << "Value stored under " << str << ": " << map[str] << std::endl;

    std::cout << "Table space usage: " << map.getTableSpaceUsage() << "%" << std::endl;

    return 0;
}
