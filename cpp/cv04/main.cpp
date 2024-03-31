#include <iostream>
#include <memory>
#include <variant>
#include <vector>

namespace ClassInheritanceExample
{
class Animal
{
  public:
    virtual void make_sound() = 0;
};

class Cat : public Animal
{
    void make_sound()
    {
        std::cout << "Meow" << std::endl;
    }
};

class Dog : public Animal
{
    void make_sound()
    {
        std::cout << "Bark" << std::endl;
    }
};
} // namespace ClassInheritanceExample

namespace VisitorExample
{
class Cat
{
};
class Dog
{
};

using Animal = std::variant<Cat, Dog>;

class Visitor
{
  public:
    void operator()(const Cat &cat) const
    {
        std::cout << "Meow" << std::endl;
    }
    void operator()(const Dog &dog) const
    {
        std::cout << "Bark" << std::endl;
    }
};
} // namespace VisitorExample

namespace LambdaVisitorExample
{
template <class... Ts> struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

class Cat
{
};
class Dog
{
};

using Animal = std::variant<Cat, Dog>;

inline void make_sound(Animal animal)
{
    std::visit(overloaded{[](const Cat &) { std::cout << "Meow" << std::endl; },
                          [](const Dog &) { std::cout << "Bark" << std::endl; }},
               animal);
}

inline void run(std::vector<Animal> animals)
{
    for (auto &animal : animals)
    {
        make_sound(animal);
    }
}
} // namespace LambdaVisitorExample

int main()
{
    {
        std::vector<std::shared_ptr<ClassInheritanceExample::Animal>> animals = {
            std::make_shared<ClassInheritanceExample::Cat>(), std::make_shared<ClassInheritanceExample::Dog>(),
            std::make_shared<ClassInheritanceExample::Cat>()};

        for (auto &animal : animals)
        {
            animal->make_sound();
        }
    }

    {
        std::vector<VisitorExample::Animal> animals = {VisitorExample::Cat(), VisitorExample::Dog(),
                                                       VisitorExample::Cat()};
        VisitorExample::Visitor visitor;

        for (auto &animal : animals)
        {
            std::visit(visitor, animal);
        }
    }

    {
        LambdaVisitorExample::run(
            {LambdaVisitorExample::Cat(), LambdaVisitorExample::Dog(), LambdaVisitorExample::Cat()});
    }

    return 0;
}
