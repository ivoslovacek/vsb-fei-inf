#include "nevim.hpp"
#include <iostream>
#include <memory>
#include <cassert>

int Disjunction_subets::current_index = 1;

Disjunction_subets::Disjunction_subets(std::string name)
{
    this->name = name;
    this->parent = std::weak_ptr<Disjunction_subets>();
    this->index = current_index;
    Disjunction_subets::current_index++;
}

void Disjunction_subets::make_union(std::shared_ptr<Disjunction_subets> name_1,
                                    std::shared_ptr<Disjunction_subets> name_2)
{

    assert("name_2 is part of another union" && name_2->parent.expired());

    name_1->elements.push_back(name_2);
    name_2->parent = std::weak_ptr<Disjunction_subets>(name_1);
}

int Disjunction_subets::find_in_which_Set()
{
    int index = this->index;

    std::weak_ptr<Disjunction_subets> tmp = this->parent;

    while (!tmp.expired())
    {
        std::shared_ptr<Disjunction_subets> ptr = tmp.lock();
        index = ptr->index;

        tmp = std::weak_ptr<Disjunction_subets>(ptr->parent);
    }

    return index;
}
