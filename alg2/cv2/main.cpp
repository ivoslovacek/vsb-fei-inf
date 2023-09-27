#include "matrix.hpp"
#include <iostream>
#include <vector>

std::vector<std::vector<double>> A_1 = {
    {1, 2, -3, 4, 5}, {2, 1, 0, 3, 0}, {0, 2, 1, 2, -1}, {3, -1, 0, 5, 2}, {2, 1, 2, 3, -4}};
std::vector<std::vector<double>> A_2 = {{2, 4, -2, -2}, {1, 2, 4, -3}, {-3, -3, 8, -2}, {-1, 1, 6, -3}};
std::vector<std::vector<double>> A_3 = {
    {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
std::vector<std::vector<double>> A_4 = {{2, 5, 0, 8}, {1, 4, 2, 6}, {7, 8, 9, 3}, {1, 5, 7, 8}};

std::vector<double> B_1 = {4, 9, 5, 3, 2};
std::vector<double> B_2 = {-4, 5, 7, 7};
std::vector<double> B_3 = {1, 2, 3, 4, 5};
std::vector<double> B_4 = {6, 5, 4, 3};

int main(int argc, char **argv)
{
    MatrixAndFun tmp;
    tmp.setA(A_3);
    tmp.setB(B_3);

    tmp.GEPartialPivot();
    tmp.printGE();

    tmp.LUDecomp();
    tmp.printLU();

    NumberOfSolutions num = tmp.findNumberOfSolutions();
    switch (num)
    {
    case zero:
        std::cout << "Number of solutions is zero" << std::endl;
        break;

    case one:
        std::cout << "Number of solutions is one" << std::endl;
        break;

    case inf:
        std::cout << "Number of solution is infinite" << std::endl;
        break;
    }

    return 0;
}
