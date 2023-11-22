#include "nevim.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    std::shared_ptr<Disjunction_subets> one = std::make_shared<Disjunction_subets>("Aragorn");
    std::shared_ptr<Disjunction_subets> two = std::make_shared<Disjunction_subets>("Frodo");
    std::shared_ptr<Disjunction_subets> three = std::make_shared<Disjunction_subets>("Gandalf");
    std::shared_ptr<Disjunction_subets> four = std::make_shared<Disjunction_subets>("Legolas");
    std::shared_ptr<Disjunction_subets> five = std::make_shared<Disjunction_subets>("Gimli");
    std::shared_ptr<Disjunction_subets> six = std::make_shared<Disjunction_subets>("Boromir");
    std::shared_ptr<Disjunction_subets> seven = std::make_shared<Disjunction_subets>("Samwise");
    std::shared_ptr<Disjunction_subets> eight = std::make_shared<Disjunction_subets>("Merry");
    std::shared_ptr<Disjunction_subets> nine = std::make_shared<Disjunction_subets>("Pippin");

    Disjunction_subets::make_union(one, two);
    Disjunction_subets::make_union(one, three);
    Disjunction_subets::make_union(three, nine);

    Disjunction_subets::make_union(four, six);
    Disjunction_subets::make_union(five, four);
    Disjunction_subets::make_union(eight, five);

    std::cout << nine->find_in_which_Set() << std::endl;

    return 0;
}
