#include <iostream>
#include <random>

int smallest(int *arr, int n)
{
    if (arr[0] + 1 != arr[1])
        return 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] + 1 != arr[i + 1])
            return arr[i] + 1;
    }

    return -1;
}

int smallestLog(int *arr, int l, int r)
{
    if (l > r)
        return l;

    int m = (l + r) / 2;

    if (arr[m] == m)
        return smallestLog(arr, m + 1, r);
    else
        return smallestLog(arr, l, m - 1);
}

void insertionSort(int *arr, int len1)
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



int main()
{
    srand(time(nullptr));
    const int n = 20;
    int *arr = new int[20];
    const int range = 50;
    bool used[range] = {0};

    int counter = 0;

    while (counter < n)
    {
        int number = rand() % range;

        if (!used[number])
        {
            used[number] = true;
            arr[counter] = number;
            counter++;
        }
    }

    insertionSort(arr, n);

    std::cout << smallestLog(arr, 0, n);

    delete[] arr;

    return 0;
}