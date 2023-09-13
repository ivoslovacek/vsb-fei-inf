#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

void bubblesort(int *array, int lenght)
{
    bool swapped = false;

    for (int i = 0; i < lenght - 1; i++)
    {
        for (int j = 0; j < lenght - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swapped = true;
                swap(array[j], array[j + 1]);
            }
        }

        if (!swapped)
            break;
    }
}

void selectionSort(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (array[j] < array[i])
            {
                min = j;
            }
        }

        if (min != i)
            swap(array[i], array[min]);
    }
}

void printArr(int *array, int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        cout << array[i] << endl;
    }
}

void idk(int *array, int lenght, int x, int y)
{
    selectionSort(array, lenght);

    int i = 0;
    for (; i < lenght && array[i] < x; i++)
        ;

    int element = x;

    while (i < lenght)
    {
        while (array[i] != element && element <= y)
        {
            cout << element++ << "\t";
        }

        while (i < lenght - 1 && array[i] == array[i + 1])
            i++;

        i++;
        element++;
    }

    while (element <= y)
    {
        cout << element++ << "\t";
    }

    cout << endl;
}

int main()
{
    const int n = 10;
    int *arr = new int[n];

    srand(time(nullptr));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }

    chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();

    selectionSort(arr, n);

    const auto end = chrono::system_clock::now();

    cout << chrono::duration_cast<chrono::microseconds>(end - now) / 1ms << endl;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }

    chrono::time_point<chrono::system_clock> now2 = chrono::system_clock::now();

    bubblesort(arr, n);

    const auto end2 = chrono::system_clock::now();

    cout << endl;
    cout << chrono::duration_cast<chrono::microseconds>(end2 - now2) / 1ms << endl
         << endl;

    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    idk(arr, n, 5, 12);

    delete[] arr;

    return 0;
}