#include <iostream>
#include "kebabshop.hpp"

Order::Order(std::string name, float price, uint32_t id, Client *owner)
{
    this->name = name;
    this->price = price;
    this->id = id;
    this->owner = owner;
}