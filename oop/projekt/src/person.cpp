#include <iostream>
#include <random>
#include "kebabshop.hpp"
#include "kebablibrary.hpp"

Employee::Employee(std::string name)
{
    this->name = name;
}

Client::Client(std::string name, float money)
{
    this->name = name;
    this->money = money;
}

void Client::createOrder(Kebabshop &shop, std::string name, float price)
{
    srand(time(nullptr));

    uint32_t id;

    do
    {
        id = rand();
    } while (skl::linearSearch(this->orders, id));

    Order *tmp = new Order(name, price, id, this);

    if (!shop.canOrderBePlaced() || !this->payOrder(tmp))
    {
        delete tmp;
        return;
    }

    this->orders.push_back(tmp);
    shop.placeOrder(tmp);
}

void Client::completeOrder(Order *order)
{
    for(size_t i = 0; i < this->orders.size(); i++)
    {
        if(this->orders[i] == order)
            this->orders.erase(this->orders.begin() + i);
    }
}

bool Client::payOrder(Order *order)
{
    if (this->money < order->getPrice())
        return false;

    this->money -= order->getPrice();

    return true;
}

bool MemberClient::payOrder(Order *order)
{
    if (this->money < order->getPrice() * 0.8)
        return false;

    this->money -= order->getPrice() * 0.8;

    return true;
}