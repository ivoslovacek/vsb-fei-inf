#include <iostream>
#include "btree.hpp"

int main(int argv, char **argc)
{
    BTree x(1);

    x.add(3);
    x.add(22);
    x.add(10);
    x.add(44);
    x.print();

    std::cout << x.search(22) << std::endl;

    return 0;
}
