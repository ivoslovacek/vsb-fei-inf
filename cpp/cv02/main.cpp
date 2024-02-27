#include <functional>
#include <initializer_list>
#include <iostream>
#include <ostream>
class MojePole
{
  public:
    static int pocetInstanci;

    MojePole()
    {
        MojePole::pocetInstanci++;
    };

    MojePole(int n) : velikost(n)
    {
        this->pole = new int[n];

        for (int i = 0; i < this->velikost; i++)
        {
            this->pole[i] = i + 1;
        }

        MojePole::pocetInstanci++;
    }

    MojePole(std::initializer_list<int> list) : velikost(list.size())
    {
        this->pole = new int[list.size()];

        size_t i = 0;

        for (auto each : list)
        {
            this->pole[i] = each;
            i++;
        }

        MojePole::pocetInstanci++;
    }

    ~MojePole()
    {
        MojePole::pocetInstanci++;
        delete[] this->pole;
    }

    friend std::ostream &operator<<(std::ostream &os, const MojePole &mojePole);

    MojePole operator+(const MojePole &arr)
    {
        MojePole tmp(this->velikost + arr.velikost);

        for (size_t i = 0; i < this->velikost; i++)
        {
            tmp.pole[i] = this->pole[i];
        }

        for (size_t i = 0; i < arr.velikost; i++)
        {
            tmp.pole[this->velikost + i] = arr.pole[i];
        }

        return tmp;
    }

    void forEach(std::function<void(int &)> fn)
    {
        for (int i = 0; i < this->velikost; i++)
        {
            fn(this->pole[i]);
        }
    }

    int *pole{nullptr};
    size_t velikost{0};
};

int MojePole::pocetInstanci = 0;

std::ostream &operator<<(std::ostream &os, const MojePole &mojePole)
{
    if (mojePole.pole == nullptr)
    {
        return os;
    }

    for (size_t i = 0; i < mojePole.velikost; i++)
    {
        os << mojePole.pole[i];
        if (i != mojePole.velikost - 1)
        {
            os << ',';
        }
    }

    return os;
}

int main()
{
    MojePole mojePole(5);
    MojePole mojePole2({1, 1, 2, 2});    // std::initializer_list example
    std::cout << mojePole2 << std::endl; // [1,2,3,4,5]
    MojePole spojene = mojePole + mojePole;
    std::cout << spojene << std::endl;                 // [1,2,3,4,5,1,2,3,4,5]
    std::cout << MojePole::pocetInstanci << std::endl; // 3
    // std::cout << "MojeStruktura: " << sizeof(MojeStruktura) << std::endl; // MojeStruktura: 1

    int y = 4;
    auto lambda = [y](int &x) { x = x * y; };

    mojePole.forEach(lambda);
    std::cout << mojePole << std::endl; // [1,2,3,4,5]

    return 0;
}
