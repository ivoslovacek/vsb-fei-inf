#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Order;
class Person;
class Employee;
class Client;

class Resources
{
  private:
    unsigned int meat = 0;
    unsigned int sauce = 0;
    unsigned int vegetables = 0;

  public:
    Resources(unsigned int meat, unsigned int sauce, unsigned int vegetables);
    Resources(){};

    unsigned int getMeatCount() const
    {
        return this->meat;
    }
    unsigned int getSauceCount() const
    {
        return this->sauce;
    }
    unsigned int getVegetableCount() const
    {
        return this->vegetables;
    }

    void addResources(unsigned int meat, unsigned int sauce, unsigned int vegetables);
    bool checkResources();
    void useResources();
};

class Kebabshop
{
  private:
    std::string name;
    Resources *stock;
    std::vector<Order *> orders;
    std::vector<Employee *> employees;

  public:
    Kebabshop(std::string name);
    Kebabshop(std::string name, unsigned int meat, unsigned int sauce, unsigned int vegetables);

    ~Kebabshop();

    size_t getEmployeeCount() const
    {
        return this->employees.size();
    }
    void hireEmployee();
    Employee *getEmployee(size_t id) const
    {
        return this->employees[id];
    }

    bool canOrderBePlaced() const
    {
        return ((this->stock->checkResources()) ? true : false);
    }
    void placeOrder(Order *order)
    {
        this->orders.push_back(order);
    }
    size_t getOrderCount() const
    {
        return this->orders.size();
    }
    void printOrders();
    void proccessOrder();

    void restock(unsigned int meat, unsigned int sauce, unsigned int vegetables);
    Resources *getStock() const
    {
        return this->stock;
    }
};

class Order
{
  private:
    std::string name;
    float price;
    uint32_t id;
    Client *owner;

  public:
    Order(std::string name, float price, uint32_t id, Client *owner);

    std::string getName() const
    {
        return this->name;
    }
    float getPrice() const
    {
        return this->price;
    }
    uint32_t getId() const
    {
        return this->id;
    }
    Client *getOwner() const
    {
        return this->owner;
    }
};

class Person
{
  public:
    virtual std::string getName() const = 0;
};

class Employee : public Person
{
  private:
    std::string name;
    uint64_t completed_orders = 0;

  public:
    Employee(std::string name);

    std::string getName() const
    {
        return this->name;
    }
    void completeOrder()
    {
        this->completed_orders++;
    }
    uint64_t getCompletedOrdersCount() const
    {
        return this->completed_orders;
    }
};

class Client : public Person
{
  protected:
    std::string name;
    std::vector<Order *> orders;
    float money;
    virtual bool payOrder(Order *order);

  public:
    Client(std::string name, float money);

    std::string getName() const
    {
        return this->name;
    }
    float getMoney() const
    {
        return this->money;
    }
    size_t getPlacedOrdersCount() const
    {
        return this->orders.size();
    }

    void createOrder(Kebabshop &shop, std::string name, float price);
    void completeOrder(Order *order);
};

class MemberClient : public Client
{
  private:
    bool payOrder(Order *order) override;

  public:
    MemberClient(std::string name, float money) : Client(name, money){};
};
