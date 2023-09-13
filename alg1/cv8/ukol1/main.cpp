#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int getCount(int *arr, int len1)
{
    int tmp = 0;
    for (int i = 0; i < len1 - 1; i++)
    {
        for (int j = i + 1; j < len1; j++)
        {
            if (i < j && arr[i] > arr[j])
                tmp++;
        }
    }

    return tmp;
}

void insertionSort(int *arr, int len1)
{
    for (int i = 1; i < len1; i++)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            std::swap(arr[j], arr[j - 1]);
        }
    }
}

void insertionSort2(int *arr, int len1)
{
    for (int i = 1; i < len1; i++)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            int tmp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = tmp;
        }
    }
}

void printArr(int *arr, const int len)
{
    for (int i = 0; i < len; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

bool binarySearchIter(int *arr, int n, int value)
{
    int l = 0;
    int r = n - 1;

    while (l <= r)
    {
        int m = (l + r) / 2;

        if (arr[m] == value)
            return true;

        if (arr[m] > value)
            r = m - 1;

        if (arr[m] < value)
            l = m + 1;
    }

    return false;
}

bool binarySearchRec(int *arr, int l, int r, int value)
{
    if (l > r)
        return false;

    int m = (l + r) / 2;

    if (arr[m] == value)
        return true;

    if (arr[m] > value)
        return binarySearchRec(arr, l, m - 1, value);

    if (arr[m] < value)
        return binarySearchRec(arr, m + 1, r, value);

    return false;
}

int partition(int *arr, int l, int r)
{
    int pivot = arr[r];
    int i = l;

    for (int j = l; j < r; j++)
    {
        if (arr[j] < pivot)
        {
            swap(arr[j], arr[i]);
            i++;
        }
    }

    swap(arr[i], arr[r]);
    return i;
}

void quickSort(int *arr, int l, int r)
{
    if (l > r)
        return;

    int pivot = partition(arr, l, r);

    quickSort(arr, l, pivot - 1);
    quickSort(arr, pivot + 1, r);
}

int main()
{
    srand(time(nullptr));

    const int n = 500000;

    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }

    auto now = std::chrono::system_clock::now();
    quickSort(arr, 0, n - 1);
    auto end = std::chrono::system_clock::now();
    std::cout << "run time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - now) / 1us << std::endl;

    delete[] arr;

    return 0;
}