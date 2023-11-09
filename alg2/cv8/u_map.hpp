#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <iostream>

template <typename K, typename V> class u_map
{
  private:
    std::vector<std::list<std::pair<K, V>>> map;

    int hash(K key)
    {
        uint32_t index = 0;

        int length = sizeof(K);

        uint8_t *keyBytes = nullptr;

        if (std::is_same_v<K, std::string>)
        {
            char tmp[key.size() + 1];
            std::copy(key.begin(), key.end(), tmp);
            tmp[key.size()] = '\0';
            length = key.size();
            keyBytes = reinterpret_cast<uint8_t *>(&tmp);
        }
        else
        {
            K tmp = key;
            length = sizeof(K);
            keyBytes = reinterpret_cast<uint8_t *>(&tmp);
        }

        uint32_t tmp = 0;

        for (size_t i = 0; i < length; i++)
        {
            if (i % 4 == 0)
            {
                index += tmp;
                tmp = 0;
            }

            uint8_t u8_tmp = keyBytes[i];
            tmp <<= 8;
            tmp |= u8_tmp;
        }

        index += tmp;

        return std::floor(this->map.size() * (static_cast<int>(index) * 1.61803398875 -
                                              std::floor(static_cast<int>(index) * 1.61803398875)));
    }

  public:
    u_map(int size)
    {
        static_assert(std::is_same_v<K, std::string> || std::is_integral_v<K>,
                      "Key must be of an integral type or a string");

        this->map = std::vector<std::list<std::pair<K, V>>>(size);
    }

    V &operator[](K key)
    {
        int index = hash(key);

        if (this->map[index].size() != 0)
        {
            auto it = this->map[index].begin();

            for (; it != this->map[index].end(); it++)
            {
                if (it->first == key)
                {
                    return it->second;
                }
            }
        }

        this->map[index].push_back(std::make_pair(key, V()));
        return this->map[index].back().second;
    }

    float getTableSpaceUsage()
    {
        int count = 0;

        for (auto each : this->map)
        {
            if (!each.empty())
            {
                count++;
            }
        }

        return (static_cast<float>(count) / this->map.size()) * 100;
    }
};
