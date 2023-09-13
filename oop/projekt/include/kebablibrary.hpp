#pragma once
#include "kebabshop.hpp"
#include <iostream>
#include <vector>

namespace skl
{

template <typename T> bool binarySearch(std::vector<T> &vector, const T &value);

template <typename T> bool linearSearch(std::vector<T> &vector, const T &value);
bool linearSearch(std::vector<Order *> &vector, const uint32_t value);
} // namespace skl
