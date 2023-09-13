#include <iostream>
#include <vector>
#include "kebabshop.hpp"

std::string standard_name = "Jožko Ferko";

std::string to_roman(unsigned int value)
{
    struct romandata_t
    {
        unsigned int value;
        char const *numeral;
    };
    const struct romandata_t romandata[] =
        {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}, {0, NULL} // end marker
        };

    std::string result;
    for (const romandata_t *current = romandata; current->value > 0; ++current)
    {
        while (value >= current->value)
        {
            result += current->numeral;
            value -= current->value;
        }
    }
    return result;
}

int main()
{
    Kebabshop *nominos = new Kebabshop("Nominos", 80, 80, 80);
    MemberClient ivo("Ivo", 880);

    std::vector<Client *> clients;

    int guy_counter = 1;

    for (size_t i = 0; i < 25; i++)
    {
        std::string tmp_name = standard_name;
        tmp_name.append(" ");
        tmp_name.append(to_roman(guy_counter));
        tmp_name.append(".");
        guy_counter++;
        Client *tmp = new Client(tmp_name, 200);
        clients.push_back(tmp);
    }

    for (size_t i = 0; i < 25; i++)
    {
        std::string tmp_name = standard_name;
        tmp_name.append(" ");
        tmp_name.append(to_roman(guy_counter));
        tmp_name.append(".");
        guy_counter++;
        Client *tmp = new MemberClient(tmp_name, 200);
        clients.push_back(tmp);
    }

    for (size_t i = 0; i < 5; i++)
        nominos->hireEmployee();

    for (auto each : clients)
        std::cout << each->getName() << " " << each->getMoney() << std::endl;

    for (auto each : clients)
        each->createOrder(*nominos, "kebab s rýží", 110);

    nominos->printOrders();

    while (nominos->getOrderCount() != 0)
        nominos->proccessOrder();

    for (int i = 0; i < nominos->getEmployeeCount(); i++)
        std::cout << nominos->getEmployee(i)->getCompletedOrdersCount() << std::endl;

    for (auto each : clients)
        std::cout << each->getName() << " " << each->getMoney() << std::endl;

    delete nominos;

    for (auto each : clients)
        delete each;

    return 0;
}