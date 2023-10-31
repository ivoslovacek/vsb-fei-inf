#include <iostream>
#include "btree.hpp"

int main(int argv, char **argc)
{
    BTree x(1);

    x.add(10);
    x.add(22);
    x.add(3);
    x.add(25);
    x.add(24);
    x.add(27);
    x.add(26);
    x.print();

    return 0;
}
