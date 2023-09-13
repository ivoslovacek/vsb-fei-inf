#include "kebablibrary.hpp"

template <typename T>
bool skl::binarySearch(std::vector<T> &vector, const T &value)
{
    int l = 0;
    int r = vector.size() - 1;

    while (l < r)
    {
        int mid = l + (r - l) / 2;

        if (vector[mid] == value)
            return true;

        if (vector[mid] < value)
            l = mid + 1;

        if (vector[mid] > value)
            r = mid - 1;
    }

    return false;
}

template <typename T>
bool skl::linearSearch(std::vector<T> &vector, const T &value)
{
    for (auto each : vector)
    {
        if (each == value)
            return true;
    }

    return false;
}

bool skl::linearSearch(std::vector<Order *> &vector, const uint32_t value)
{
    for (auto each : vector)
    {
        if (each->getId() == value)
            return true;
    }

    return false;
}