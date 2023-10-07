#include <iostream>
#include <vector>

// polynom = b0 * x^0 + ... + bn * x^n
double horner(const std::vector<double> &polynom, double x)
{
    int n = polynom.size();
    double result = polynom[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        result = result * x + polynom[i];
    }

    return result;
}

int greatestCommonDivisor(int a, int b)
{
    while (a != b)
    {
        (a > b) ? a = a - b : b = b - a;
    }

    return a;
}

int greatestCommonMultiple(int a, int b)
{
    return (a * b) / greatestCommonDivisor(a, b);
}

int main()
{
    int a = 140;
    int b = 72;

    std::cout << greatestCommonDivisor(a, b) << std::endl;
    std::cout << greatestCommonMultiple(a, b) << std::endl;

    std::vector<double> polynom = {-7, 5, -2, 4, 0, 5};
    std::cout << horner(polynom, 5.3) << std::endl;

    return 0;
}
