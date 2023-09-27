#pragma once
#include <iostream>
#include <vector>

enum NumberOfSolutions
{
    zero = 0,
    one = 1,
    inf = 2
};

class MatrixAndFun
{
  private:
    std::vector<std::vector<double>> a;
    std::vector<double> b;
    std::vector<std::vector<double>> ab;
    std::vector<std::vector<double>> ge;
    std::vector<std::vector<double>> l;
    std::vector<std::vector<double>> u;

  public:
    void setA(std::vector<std::vector<double>> a);
    void setB(std::vector<double> a);

    void GEPartialPivot();
    void swapRows();
    void LUDecomp();
    NumberOfSolutions findNumberOfSolutions();

    void print();
    void printGE();
    void printLU();
};
