#include <iostream>

using namespace std;

bool find(int *array, size_t len, int a)
{
    for (size_t i = 0; i < len; i++)
    {
        if (array[i] == a)
        {
            return true;
        }
    }

    return false;
}

class Matice
{
  private:
    int rows;
    int cols;

  public:
    int **data;

    Matice(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;

        this->data = new int *[rows];

        for (int i = 0; i < rows; i++)
        {
            this->data[i] = new int[cols];

            for (int j = 0; j < cols; j++)
            {
                this->data[i][j] = 0;
            }
        }
    }
    ~Matice()
    {
        for (int i = 0; i < this->rows; i++)
        {
            delete[] this->data[i];
        }

        delete[] this->data;

        this->data = nullptr;
    }

    void init()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                this->data[i][j] = i + j;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }

        cout << endl;
    }

    int getRows()
    {
        return this->rows;
    }

    int getCols()
    {
        return this->cols;
    }
};

void nasobeniMatic(Matice &a, Matice &b, Matice &c)
{
    int tmp = 0;

    for (int i = 0; i < c.getRows(); i++)
    {
        for (int j = 0; j < c.getCols(); j++)
        {
            for (int d = 0; d < a.getCols(); d++)
            {
                tmp += a.data[i][d] * b.data[d][j];
            }

            c.data[i][j] = tmp;
            tmp = 0;
        }
    }
}

bool isUnique(int *arr, int len)
{

    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = i; j < len - (i + 1); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    for (int i = 0; i < len - 1; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    const int n = 10;
    int arr[n];

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    arr[9] = 8;

    cout << (isUnique(arr, n) ? "yup" : "nope") << endl;

    Matice A(1, 10);
    Matice B(10, 1);
    Matice C(A.getRows(), B.getCols());

    A.init();
    A.print();

    B.init();
    B.print();

    C.init();

    nasobeniMatic(A, B, C);

    C.print();

    return 0;
}
