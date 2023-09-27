#include "matrix.hpp"
#include <valarray>

void MatrixAndFun::setA(std::vector<std::vector<double>> a)
{
    this->a = a;
}

void MatrixAndFun::setB(std::vector<double> b)
{
    this->b = b;
}

void MatrixAndFun::print()
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a.size(); j++)
        {
            std::cout << a[i][j] << " ";
        }

        std::cout << b[i] << std::endl;
    }
}

void MatrixAndFun::printGE()
{
    std::cout << "Soustava rovnic po GE:" << std::endl;
    for (auto each : this->ge)
    {
        for (auto each2 : each)
        {
            std::cout << each2 << " ";
        }

        std::cout << std::endl;
    }
}

void MatrixAndFun::printLU()
{
    std::cout << "Matice L:" << std::endl;

    for (auto each : this->l)
    {
        for (auto each2 : each)
        {
            std::cout << each2 << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "Matice U:" << std::endl;

    for (auto each : this->u)
    {
        for (auto each2 : each)
        {
            std::cout << each2 << " ";
        }

        std::cout << std::endl;
    }
}

void MatrixAndFun::GEPartialPivot()
{
    std::vector<std::vector<double>> tmp_a = this->a;

    size_t n = tmp_a.size();
    for (int i = 0; i < n; i++)
    {
        tmp_a[i].push_back(this->b[i]);
    }

    this->ab = tmp_a;

    for (int i = 0; i < n - 1; i++)
    {
        int pivotrow = i;

        for (int j = i + 1; j < n; j++)
        {
            if (std::abs(tmp_a[j][i]) > std::abs(tmp_a[pivotrow][i]))
            {
                pivotrow = j;
            }
        }

        for (int j = i; j < n + 1; j++)
        {
            std::swap(tmp_a[i][j], tmp_a[pivotrow][j]);
        }

        for (int j = i + 1; j < n; j++)
        {
            double temp = tmp_a[j][i] / tmp_a[i][i];

            for (int k = i; k < n + 1; k++)
            {
                tmp_a[j][k] -= tmp_a[i][k] * temp;
            }
        }
    }

    this->ge = tmp_a;
}

void MatrixAndFun::LUDecomp()
{
    size_t n = this->a.size();
    std::vector<std::vector<double>> L;
    std::vector<std::vector<double>> U;

    for (int i = 0; i < this->a.size(); i++)
    {
        L.push_back(std::vector<double>(this->a.size(), 0));
        U.push_back(std::vector<double>(this->a.size(), 0));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i <= j)
            {
                U[i][j] = this->a[i][j];

                for (int k = 0; k < i; k++)
                {
                    U[i][j] -= L[i][k] * U[k][j];
                }

                if (i == j)
                {
                    L[i][j] = 1.0;
                }
                else
                {
                    L[i][j] = 0.0;
                }
            }
            else
            {
                L[i][j] = this->a[i][j];

                for (int k = 0; k < j; k++)
                {
                    L[i][j] -= L[i][k] * U[k][j];
                }

                L[i][j] /= U[j][j];
                U[i][j] = 0.0;
            }
        }
    }

    this->l = L;
    this->u = U;
}

NumberOfSolutions MatrixAndFun::findNumberOfSolutions()
{
    int n = this->ab.size();
    int ABRank = 0;

    for (int i = 0; i < n; i++)
    {
        bool allZero = true;
        for (int j = 0; j < n; j++)
        {
            if (std::fabs(ab[i][j]) > 1e-9)
            {
                allZero = false;
                break;
            }
        }
        if (!allZero)
        {
            ABRank++;
        }
    }

    int rank = 0;

    for (int i = 0; i < n; i++)
    {
        bool allZero = true;
        for (int j = 0; j < n; j++)
        {
            if (std::fabs(this->u[i][j]) > 1e-9)
            {
                allZero = false;
                break;
            }
        }
        if (!allZero)
        {
            rank++;
        }
    }

    if (rank < ABRank)
    {
        return (rank < n) ? inf : zero;
    }
    else
    {
        return (rank == n) ? one : inf;
    }
}
