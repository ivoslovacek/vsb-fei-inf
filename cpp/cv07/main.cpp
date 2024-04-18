#include <array>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
class Iterable {
    T m_begin;
    T m_end;

   public:
    Iterable(T begin, T end) {
        this->m_begin = begin;
        this->m_end = end;
    }

    class Map {
        auto begin();
        auto end();
    };

    auto begin() const { return this->m_begin; }
    auto end() const { return this->m_end; }

    auto& operator*() { return *this->m_begin; }

    Iterable& operator++() {
        this->m_begin++;
        return *this;
    }

    bool operator==(Iterable& other) { return this->m_begin == other->m_end; }
    bool operator!=(Iterable& other) { return this->m_begin == other->m_end; }
};

template <typename T>
class MojePole {
   public:
    std::vector<T> pole;
    MojePole(std::initializer_list<T> list) {
        pole.insert(pole.end(), list.begin(), list.end());
    }

    auto iter() { return Iterable(pole.begin(), pole.end()); }
};

int main() {
    {
        MojePole<std::string> pole{"jedna", "dva",  "tri", "ctyri", "pet",
                                   "sest",  "sedm", "osm", "devet", "deset"};
        auto iter = pole.iter();
        for (auto item : iter) {
            std::cout << "MojePole iter " << item << std::endl;
        }
        // std::cout << "--------" << std::endl;

        // auto iter_map = iter.map([](auto x) {
        //     return x + " x " + x;
        // });
        // for (auto item : iter_map) {
        //     std::cout << "MojePole map " << item << std::endl;
        // }
        // std::cout << "--------" << std::endl;
    }

    {
        int pole[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto iter = Iterable(pole, pole + 10);
        for (auto item : iter) {
            std::cout << "pole iter " << item << std::endl;
        }
        // std::cout << "--------" << std::endl;
        // auto iter_map = iter.map([](int x) {
        //     return x * 2;
        // });
        // for (auto item : iter_map) {
        //     std::cout << "pole map " << item << std::endl;
        // }
    }

    return 0;
}
