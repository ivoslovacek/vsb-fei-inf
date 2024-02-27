#pragma once

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>
namespace math
{
int fibonacci(int n);
}

namespace strutils
{
std::string camel_to_snake(std::string camel);

bool parse_uint(std::string str, uint32_t &result);

bool validate_utf8(std::vector<uint8_t> bytes, size_t &result);
} // namespace strutils
