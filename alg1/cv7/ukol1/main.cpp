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

int main()
{
    srand(time(nullptr));

    const int n = 100;

    int *arr = new int[n];
    int *arr2 = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 20 + 5;
        arr2[i] = rand() % 20 + 5;
    }

    printArr(arr, n);

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    insertionSort(arr, n);
    const auto end = std::chrono::system_clock::now();
    printArr(arr, n);
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now) / 1us << std::endl;

    printArr(arr2, n);
    std::chrono::time_point<std::chrono::system_clock> now2 = std::chrono::system_clock::now();
    insertionSort2(arr2, n);
    const auto end2 = std::chrono::system_clock::now();
    printArr(arr2, n);
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end2 - now2) / 1us << std::endl;

    delete[] arr;
    delete[] arr2;

    return 0;
}