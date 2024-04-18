#include "tasks.h"
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <istream>
#include <iterator>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

bool Array::operator==(const Array &other) const
{
    return other.items == this->items;
}

bool Object::operator==(const Object &other) const
{
    return other.items == this->items;
}

bool String::operator==(const String &other) const
{
    return other.value == this->value;
}

bool Null::operator==(const Null &) const
{
    return true;
}

bool Number::operator==(const Number &other) const
{
    return other.value == this->value;
}

bool Boolean::operator==(const Boolean &other) const
{
    return other.value == this->value;
}

enum class JSONType
{
    Null = 0,
    Bool = 1,
    Number = 2,
    String = 3,
    Array = 4,
    Object = 5
};

std::vector<uint8_t> serialize(const Value &value)
{
    std::vector<uint8_t> result = std::vector<uint8_t>();

    if (auto v = std::get_if<Null>(&value))
    {
        result.emplace_back(static_cast<uint8_t>(JSONType::Null));
    }
    else if (auto v = std::get_if<Boolean>(&value))
    {
        result.emplace_back(static_cast<uint8_t>(JSONType::Bool));
        result.emplace_back(static_cast<uint8_t>(v->value));
    }
    else if (auto v = std::get_if<Number>(&value))
    {
        result.emplace_back(static_cast<uint8_t>(JSONType::Number));

        // let's pretend that every system and compiler conforms
        // with the IEEE 754 standard
        auto tmp = *(reinterpret_cast<const uint64_t *>(&v->value));

        result.emplace_back(static_cast<uint8_t>(tmp));
        result.emplace_back(static_cast<uint8_t>(tmp >> 8));
        result.emplace_back(static_cast<uint8_t>(tmp >> 16));
        result.emplace_back(static_cast<uint8_t>(tmp >> 24));
        result.emplace_back(static_cast<uint8_t>(tmp >> 32));
        result.emplace_back(static_cast<uint8_t>(tmp >> 40));
        result.emplace_back(static_cast<uint8_t>(tmp >> 48));
        result.emplace_back(static_cast<uint8_t>(tmp >> 56));
    }
    else if (auto v = std::get_if<String>(&value))
    {
        result.emplace_back(static_cast<uint8_t>(JSONType::String));

        result.insert(result.end(), 8, 0);
        auto size = reinterpret_cast<size_t *>(&result[1]);
        *size = v->value.size();

        for (auto each : v->value)
        {
            result.emplace_back(static_cast<uint8_t>(each));
        }
    }
    else if (auto v = std::get_if<Array>(&value))
    {
        result.emplace_back(static_cast<uint8_t>(JSONType::Array));
        result.insert(result.end(), 8, 0);

        for (auto item : v->items)
        {
            std::vector<uint8_t> tmp = serialize(item);

            auto size = reinterpret_cast<size_t *>(&result[1]);
            *size += 1;
            result.insert(result.end(), tmp.begin(), tmp.end());
        }
    }
    else if (auto v = std::get_if<Object>(&value))
    {
        result.emplace_back(static_cast<uint8_t>(JSONType::Object));

        auto keys = v->keys();
        std::sort(keys.begin(), keys.end());

        result.insert(result.end(), 8, 0);
        auto size = reinterpret_cast<size_t *>(&result[1]);
        *size = v->keys().size();

        for (auto key : keys)
        {
            result.insert(result.end(), 8, 0);
            auto it = result.end();
            it -= 8;
            auto str_size = reinterpret_cast<size_t *>(&(*it));
            *str_size = key.size();

            for (auto each : key)
            {
                result.emplace_back(static_cast<uint8_t>(each));
            }

            std::vector<uint8_t> tmp = serialize(v->items.find(key)->second);
            result.insert(result.end(), tmp.begin(), tmp.end());
        }
    }

    return result;
}

std::pair<Value, size_t> deserialize(std::vector<uint8_t>::const_iterator begin,
                                     std::vector<uint8_t>::const_iterator end)
{

    if (*begin == static_cast<uint8_t>(JSONType::Null))
    {
        return std::make_pair(Null{}, 1);
    }
    else if (*begin == static_cast<uint8_t>(JSONType::Bool))
    {
        begin++;
        return std::make_pair(Boolean{static_cast<bool>(*begin)}, 2);
    }
    else if (*begin == static_cast<uint8_t>(JSONType::Number))
    {
        begin++;

        uint64_t tmp = static_cast<uint64_t>(*begin);
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 8;
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 16;
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 24;
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 32;
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 40;
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 48;
        begin++;
        tmp |= static_cast<uint64_t>(*begin) << 56;

        double result = *(reinterpret_cast<double *>(&tmp));
        return std::make_pair(Number{result}, 9);
    }
    else if (*begin == static_cast<uint8_t>(JSONType::String))
    {
        begin++;

        std::string result = "";
        size_t size = *(reinterpret_cast<const size_t *>(&(*begin)));
        begin += 8;

        for (size_t i = 0; i < size; i++)
        {
            result += static_cast<char>(*begin);
            begin++;
        }

        return std::make_pair(String{result}, 9 + size);
    }
    else if (*begin == static_cast<uint8_t>(JSONType::Array))
    {
        begin++;

        std::vector<Value> result;

        size_t byte_size = 9;
        size_t size = *(reinterpret_cast<const size_t *>(&(*begin)));
        begin += 8;

        for (size_t i = 0; i < size; i++)
        {
            auto tmp = deserialize(begin, end);
            begin += tmp.second;
            byte_size += tmp.second;
            result.emplace_back(tmp.first);
        }

        return std::make_pair(Array{result}, byte_size);
    }
    else if (*begin == static_cast<uint8_t>(JSONType::Object))
    {
        begin++;

        std::map<std::string, Value> result;

        size_t size = *reinterpret_cast<const size_t *>(&(*begin));
        begin += 8;
        size_t byte_size = 9;

        for (size_t i = 0; i < size; i++)
        {
            size_t str_size = *reinterpret_cast<const size_t *>(&(*begin));
            begin += 8;
            byte_size += 8 + str_size;

            std::string key = "";

            for (size_t j = 0; j < str_size; j++)
            {
                key += static_cast<char>(*begin);
                begin++;
            }

            auto value = deserialize(begin, end);
            begin += value.second;
            byte_size += value.second;

            result.emplace(key, value.first);
        }

        return std::make_pair(Object{result}, byte_size);
    }

    return std::make_pair(Null{}, 0);
}

Value deserialize(const std::vector<uint8_t> &data)
{
    return deserialize(data.begin(), data.end()).first;
}

std::optional<Value> parse_json_number(std::istream &is)
{
    uint64_t whole = 0;
    uint64_t decimal = 0;
    size_t decimal_count = 0;
    bool decimal_part = false;
    bool negative_num = false;

    if (is.peek() == '-')
    {
        negative_num = true;
        is.get();
    }

    char next = is.peek();

    if (next < '0' || next > '9')
    {
        return std::nullopt;
    }

    for (next = is.peek(); !is.eof(); next = is.peek())
    {
        if (next >= '0' && next <= '9')
        {
            if (decimal_part)
            {
                decimal *= 10;
                decimal += static_cast<uint64_t>(next - '0');
                decimal_count++;
            }
            else
            {
                whole *= 10;
                whole += static_cast<uint64_t>(next - '0');
            }
            is.get();
        }
        else if (next == '.')
        {
            if (!decimal_part)
            {
                is.get();
                decimal_part = true;
                next = is.peek();
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    double value = whole;

    if (decimal_part)
    {
        value += decimal / (std::pow(10, decimal_count));
    }

    if (negative_num)
    {
        value *= -1;
    }

    return Number{value};
}

std::optional<Value> parse_json_null(std::istream &is)
{
    is.get();

    if (is.peek() == 'u')
    {
        is.get();
    }
    else
    {
        return std::nullopt;
    }

    if (is.peek() == 'l')
    {
        is.get();
    }
    else
    {
        return std::nullopt;
    }

    if (is.peek() == 'l')
    {
        is.get();
    }
    else
    {
        return std::nullopt;
    }

    return Null();
}

std::optional<Value> parse_json_bool(std::istream &is)
{
    bool result = true;

    if (is.peek() == 't')
    {
        is.get();

        if (is.peek() != 'r')
        {
            return std::nullopt;
        }
        is.get();

        if (is.peek() != 'u')
        {
            return std::nullopt;
        }
        is.get();

        if (is.peek() != 'e')
        {
            return std::nullopt;
        }
        is.get();

        result = true;
    }
    else
    {
        is.get();

        if (is.peek() != 'a')
        {
            return std::nullopt;
        }
        is.get();

        if (is.peek() != 'l')
        {
            return std::nullopt;
        }
        is.get();

        if (is.peek() != 's')
        {
            return std::nullopt;
        }
        is.get();

        if (is.peek() != 'e')
        {
            return std::nullopt;
        }
        is.get();

        result = false;
    }

    return Boolean{result};
}

std::optional<Value> parse_json_string(std::istream &is)
{
    std::string result;
    is.get();

    for (char next = is.peek(); !is.eof(); next = is.peek())
    {
        if (next == '\\')
        {
            is.get();
            if (is.peek() == '\\')
            {
                is.get();
                result += '\\';
            }
            else if (is.peek() == '\"')
            {
                is.get();
                result += '\"';
            }
            else
            {
                return std::nullopt;
            }
        }
        else if (next == '\"')
        {
            is.get();
            return String{result};
        }
        else
        {
            is.get();
            result += next;
        }
    }

    return std::nullopt;
}

std::optional<Value> parse_json_array(std::istream &is)
{
    auto result = std::vector<Value>();
    is.get();

    char next = is.peek();
    if (next == ',')
    {
        return std::nullopt;
    }

    bool parsable = true;

    for (next = is.peek(); !is.eof(); next = is.peek())
    {
        if (next == ',')
        {
            is.get();
            next = is.peek();

            if (next == ',' || next == ']')
            {
                is.get();
                return std::nullopt;
            }

            parsable = true;
        }
        else if (next == ']')
        {
            is.get();
            return Array{result};
        }
        else if (std::isspace(next))
        {
            is.get();
        }
        else if (parsable)
        {
            parsable = false;
            auto current = parse_json(is);
            if (!current.has_value())
            {
                return std::nullopt;
            }
            else
            {
                result.emplace_back(current.value());
            }
        }
        else
        {
            return std::nullopt;
        }
    }

    return std::nullopt;
}

std::optional<Value> parse_json_object(std::istream &is)
{
    std::map<std::string, Value> result;
    is.get();

    char next = is.peek();
    if (next == ',')
    {
        return std::nullopt;
    }

    bool parsable = true;

    for (next = is.peek(); !is.eof(); next = is.peek())
    {
        if (next == ',')
        {
            is.get();
            next = is.peek();

            if (next == ',' || next == '}')
            {
                is.get();
                return std::nullopt;
            }

            parsable = true;
        }
        else if (next == '}')
        {
            is.get();
            return Object{result};
        }
        else if (std::isspace(next))
        {
            is.get();
        }
        else
        {
            if (!parsable)
            {
                return std::nullopt;
            }

            auto current = parse_json(is);
            if (!current.has_value())
            {
                return std::nullopt;
            }

            std::string key;
            if (auto current_str = std::get_if<String>(&(current).value()))
            {
                key = current_str->value;
            }
            else
            {
                return std::nullopt;
            }

            for (next = is.peek(); !is.eof(); next = is.peek())
            {
                if (next == ':')
                {
                    is.get();
                    break;
                }
                else if (!std::isspace(next))
                {
                    is.get();
                    return std::nullopt;
                }
                else
                {
                    is.get();
                }
            }

            current = parse_json(is);
            if (!current.has_value())
            {
                return std::nullopt;
            }
            else
            {
                result[key] = current.value();
            }
        }
    }

    return std::nullopt;
}

std::optional<Value> parse_json(std::istream &is)
{
    for (char next = is.peek(); !is.eof(); next = is.peek())
    {
        if (next == '-' || (next >= '0' && next <= '9'))
        {
            return parse_json_number(is);
        }
        else if (next == 'n')
        {
            return parse_json_null(is);
        }
        else if (next == 't' || next == 'f')
        {
            return parse_json_bool(is);
        }
        else if (next == '\"')
        {
            return parse_json_string(is);
        }
        else if (next == '[')
        {
            return parse_json_array(is);
        }
        else if (next == '{')
        {
            return parse_json_object(is);
        }
        else if (std::isspace(next))
        {
            is.get();
        }
        else
        {
            break;
        }
    }

    return std::nullopt;
};

std::ostream &operator<<(std::ostream &os, const Value &value)
{
    std::visit(overloaded{
                   [&os](const Boolean &v) { os << ((v.value) ? "true" : "false"); },
                   [&os](const Number &v) { os << v.value; },
                   [&os](const String &v) {
                       os << '\"';

                       for (auto each : v.value)
                       {
                           if (each == '\"' || each == '\\')
                           {
                               os << '\\';
                           }

                           os << each;
                       }

                       os << '\"';
                   },
                   [&os](const Null &v) { os << "null"; },
                   [&os](const Array &v) {
                       os << '[';

                       for (auto it = v.items.begin(); it != v.items.end(); it++)
                       {
                           os << *it;

                           if (std::distance(it, v.items.end()) != 1)
                           {
                               os << ", ";
                           }
                       }

                       os << ']';
                   },
                   [&os](const Object &v) {
                       os << '{';

                       for (auto it = v.items.begin(); it != v.items.end(); it++)
                       {
                           os << '\"' << it->first << "\": ";
                           os << it->second;

                           if (std::distance(it, v.items.end()) != 1)
                           {
                               os << ", ";
                           }
                       }

                       os << '}';
                   },
               },
               value);
    return os;
}
