#include "kebabshop.hpp"
#include "kebablibrary.hpp"

Kebabshop::Kebabshop(std::string name)
{
    srand(time(nullptr));
    this->name = name;
    this->stock = new Resources();
}

Kebabshop::Kebabshop(std::string name, unsigned int meat, unsigned int sauce, unsigned int vegetables)
{
    this->name = name;
    this->stock = new Resources(meat, sauce, vegetables);
}

Kebabshop::~Kebabshop()
{
    delete this->stock;

    for (auto each : this->orders)
    {
        each->getOwner()->completeOrder(each);
        delete each;
    }

    for (auto each : this->employees)
        delete each;
}

void Kebabshop::printOrders()
{
    for (auto each : this->orders)
    {
        std::cout << each->getName() << std::endl;
    }
}

void Kebabshop::proccessOrder()
{
    if (this->orders.size() == 0)
        return;

    if (this->orders.size() > 1)
        std::swap(this->orders[0], this->orders[this->orders.size() - 1]);

    int index = rand() % this->getEmployeeCount();
    this->getEmployee((size_t)index)->completeOrder();

    this->orders[this->orders.size() - 1]->getOwner()->completeOrder(this->orders[this->orders.size() - 1]);
    delete this->orders.back();
    this->orders.pop_back();
}

void Kebabshop::restock(unsigned int meat, unsigned int sauce, unsigned int vegetables)
{
    this->stock->addResources(meat, sauce, vegetables);
}

void Kebabshop::hireEmployee()
{
    Employee *tmp = new Employee("Kebab Employee");
    this->employees.push_back(tmp);
}

Resources::Resources(unsigned int meat, unsigned int sauce, unsigned int vegetables)
{
    this->meat = meat;
    this->sauce = sauce;
    this->vegetables = vegetables;
}

void Resources::addResources(unsigned int meat, unsigned int sauce, unsigned int vegetables)
{
    this->meat += meat;
    this->sauce += sauce;
    this->vegetables += vegetables;
}

bool Resources::checkResources()
{
    if (this->meat == 0)
        return false;

    if (this->sauce == 0)
        return false;

    if (this->vegetables == 0)
        return false;

    return true;
}

void Resources::useResources()
{
    this->meat--;
    this->vegetables--;
    this->sauce--;
}