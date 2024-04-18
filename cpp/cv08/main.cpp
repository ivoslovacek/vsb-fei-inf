#include <iostream>

template <int T>
struct Fibonacci {
    constexpr static int value =
        (Fibonacci<T - 1>::value) + (Fibonacci<T - 2>::value);
};

template <>
struct Fibonacci<0> {
    constexpr static int value = 0;
};

template <>
struct Fibonacci<1> {
    constexpr static int value = 1;
};

constexpr int fibonacci(long long n) {
    if (n == 0) return 0;

    if (n == 1) return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

template <typename Derived>
class Shape {
   public:
    void print() const { static_cast<const Derived*>(this)->print_impl(); }
};

class Circle : public Shape<Circle> {
   public:
    void print_impl() const { std::cout << "Circle" << std::endl; };
};

class Square : public Shape<Square> {
   public:
    void print_impl() const { std::cout << "Square" << std::endl; };
};

int main() {
    Fibonacci<0> x0;
    static_assert(x0.value == 0);
    Fibonacci<1> x1;
    static_assert(x1.value == 1);
    Fibonacci<2> x2;
    static_assert(x2.value == 1);
    Fibonacci<3> x3;
    static_assert(x3.value == 2);
    Fibonacci<9> x9;
    static_assert(x9.value == 34);
    static_assert(Fibonacci<46>::value == 1836311903);

    std::cout << Fibonacci<46>::value << std::endl;

    static_assert(fibonacci(0) == 0);
    static_assert(fibonacci(1) == 1);
    static_assert(fibonacci(2) == 1);
    static_assert(fibonacci(3) == 2);
    static_assert(fibonacci(9) == 34);
    static_assert(fibonacci(10) == 55);

    std::cout << fibonacci(10) << std::endl;

    Shape y = Circle();
    y.print();

    Shape x = Square();
    x.print();

    return 0;
}
