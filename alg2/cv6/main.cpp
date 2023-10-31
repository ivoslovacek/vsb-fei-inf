#include <iostream>
#include "btree.hpp"

int main(int argv, char **argc)
{
    BTree strom(1);

    strom.add(10);
    strom.add(14);
    strom.add(15);
    strom.add(25);
    strom.add(12);
    strom.add(27);
    strom.add(22);
    strom.add(28);
    strom.add(29);

    strom.print();

    std::cout << (strom.search(29) ? "Číslo nalezeno" : "Číslo nenalezeno") << std::endl;

    return 0;
}
