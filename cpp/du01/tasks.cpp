#include "tasks.h"
#include <cstdint>
#include <limits>

namespace math
{
int fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    int last = 0, current = 1, tmp = 0;

    for (int i = 2; i <= n; i++)
    {
        tmp = last + current;
        last = current;
        current = tmp;
    }

    return current;
}
} // namespace math

namespace strutils
{

std::string camel_to_snake(std::string camel)
{
    std::string snake = camel;
    for (unsigned long i = 0; i < snake.length(); i++)
    {
        if (std::isupper(snake[i]))
        {
            snake[i] = std::tolower(snake[i]);
            if (i != 0)
            {
                snake.insert(snake.begin() + i, 1, '_');
                i++;
            }
        }
    }

    return snake;
}

bool parse_uint(std::string str, uint32_t &result)
{
    if (str.length() == 0)
    {
        return false;
    }

    uint64_t tmp = 0;

    for (unsigned long i = 0; i < str.length(); i++)
    {
        char current = str[i];

        if (current < 48 || current > 57)
        {
            return false;
        }

        tmp *= 10;
        tmp += static_cast<uint64_t>(str[i] - 48);
        if (tmp > std::numeric_limits<uint32_t>::max())
        {
            return false;
        }
    }

    result = static_cast<uint32_t>(tmp);

    return true;
}

bool validate_utf8(std::vector<uint8_t> bytes, size_t &result)
{
    size_t point_count = 0;

    for (unsigned long i = 0; i < bytes.size(); i++)
    {
        bool valid = false;
        int next_bytes = 0;

        if ((bytes[i] & 0b10000000) == 0b00000000)
        {
            point_count++;
            continue;
        }
        else if ((bytes[i] & 0b11100000) == 0b11000000)
        {
            point_count++;
            next_bytes = 1;
            valid = true;
        }
        else if ((bytes[i] & 0b11110000) == 0b11100000)
        {
            point_count++;
            next_bytes = 2;
            valid = true;
        }
        else if ((bytes[i] & 0b11111000) == 0b11110000)
        {
            point_count++;
            next_bytes = 3;
            valid = true;
        }

        if (valid == false)
        {
            return false;
        }

        for (int j = 1; j <= next_bytes; j++)
        {
            if (i + j >= bytes.size())
            {
                return false;
            }

            if ((bytes[i + j] & 0b11000000) != 0b10000000)
            {
                return false;
            }
        }

        i += next_bytes;
    }

    result = point_count;
    return true;
}
} // namespace strutils
