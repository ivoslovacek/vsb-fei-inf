#include "tasks.h"
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <vector>

UTF8String::UTF8String() : size(2), byteSize(0)
{
    this->data = new uint8_t[this->size];
    std::memset(this->data, 0, this->size);
}

UTF8String::UTF8String(const char *str) : size(2 * std::strlen(str) + 1), byteSize(std::strlen(str))
{
    this->data = new uint8_t[this->size];
    std::memset(this->data, 0, this->size);

    for (unsigned long i = 0; i < std::strlen(str); i++)
    {
        this->data[i] = static_cast<uint8_t>(str[i]);
    }
}

UTF8String::UTF8String(std::vector<CodePoint> str) : size(str.size() * 4), byteSize(0)
{
    this->data = new uint8_t[this->size];
    std::memset(this->data, 0, this->size);

    size_t i = this->byteSize;

    for (CodePoint point : str)
    {
        if (point <= 0x7f)
        {
            this->data[i] = static_cast<uint8_t>(point);
            i++;
            this->byteSize++;
        }
        else if (point <= 0x7ff)
        {
            this->data[i] = 0b11000000 | static_cast<uint8_t>((point >> 6) & 0b00011111);
            i++;
            this->data[i] = 0b10000000 | static_cast<uint8_t>(point & 0b00111111);
            i++;
            this->byteSize += 2;
        }
        else if (point <= 0xffff)
        {
            this->data[i] = 0b11100000 | static_cast<uint8_t>((point >> 12) & 0b00001111);
            i++;
            this->data[i] = 0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111);
            i++;
            this->data[i] = 0b10000000 | static_cast<uint8_t>(point & 0b00111111);
            i++;
            this->byteSize += 3;
        }
        else
        {
            this->data[i] = 0b11110000 | static_cast<uint8_t>((point >> 18) & 0b00000111);
            i++;
            this->data[i] = 0b10000000 | static_cast<uint8_t>((point >> 12) & 0b00111111);
            i++;
            this->data[i] = 0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111);
            i++;
            this->data[i] = 0b10000000 | static_cast<uint8_t>(point & 0b00111111);
            i++;
            this->byteSize += 4;
        }
    }
}

UTF8String::~UTF8String()
{
    delete[] this->data;
}

UTF8String::UTF8String(const UTF8String &str)
{
    this->size = str.size;
    this->byteSize = str.byteSize;
    this->data = new uint8_t[this->size];
    std::memcpy(this->data, str.data, this->size);
}

UTF8String &UTF8String::operator=(const UTF8String &str)
{
    if (this != &str)
    {
        delete[] this->data;

        this->size = str.size;
        this->byteSize = str.byteSize;
        this->data = new uint8_t[this->size];
        std::memcpy(this->data, str.data, this->size);
    }

    return *this;
}

std::optional<uint8_t> UTF8String::operator[](unsigned long i) const
{
    if (i >= this->byteSize)
    {
        return std::nullopt;
    }

    return std::optional<uint8_t>(this->data[i]);
}

UTF8String UTF8String::operator+(const UTF8String &str)
{
    uint8_t *tmp = new uint8_t[this->size + str.size];
    std::memcpy(tmp, this->data, this->size);
    std::memcpy(tmp + this->byteSize, str.data, str.byteSize);

    UTF8String newStr = UTF8String("");
    delete[] newStr.data;
    newStr.data = tmp;
    newStr.size = this->size + str.size;
    newStr.byteSize = this->byteSize + str.byteSize;

    return newStr;
}

UTF8String &UTF8String::operator+=(const UTF8String &str)
{
    uint8_t *tmp = new uint8_t[this->size + str.size];
    std::memcpy(tmp, this->data, this->size);
    std::memcpy(tmp + this->byteSize, str.data, str.byteSize);
    delete[] this->data;
    this->data = tmp;
    this->size += str.size;
    this->byteSize += str.byteSize;

    return *this;
}

bool UTF8String::operator==(const UTF8String &str) const
{
    if (this->byteSize != str.byteSize)
    {
        return false;
    }

    return (std::memcmp(this->data, str.data, this->byteSize) == 0) ? true : false;
}

UTF8String::operator std::string()
{
    return std::string(reinterpret_cast<const char *>(this->data));
}

void UTF8String::grow()
{
    uint8_t *tmp = new uint8_t[2 * this->size];
    std::memcpy(tmp, this->data, this->byteSize);
    delete[] this->data;
    this->data = tmp;
    this->size *= 2;
}

void UTF8String::grow(unsigned long min)
{
    uint8_t *tmp = new uint8_t[2 * this->size + min];
    std::memcpy(tmp, this->data, this->byteSize);
    delete[] this->data;
    this->data = tmp;
    this->size *= 2;
}

size_t UTF8String::get_byte_count() const
{
    return this->byteSize;
}

size_t UTF8String::get_point_count() const
{
    unsigned long count = 0;

    for (unsigned long i = 0; i < this->byteSize; i++)
    {
        if ((this->data[i] & 0b10000000) == 0 || (this->data[i] & 0b11100000) == 0b11000000 ||
            (this->data[i] & 0b11110000) == 0b11100000 || (this->data[i] & 0b11111000) == 0b11110000)
        {
            count++;
        }
    }

    return count;
}

std::optional<CodePoint> UTF8String::nth_code_point(unsigned long n) const
{
    size_t count = 0;

    for (size_t i = 0; i < this->byteSize; i++)
    {
        if ((this->data[i] & 0b10000000) == 0 || (this->data[i] & 0b11100000) == 0b11000000 ||
            (this->data[i] & 0b11110000) == 0b11100000 || (this->data[i] & 0b11111000) == 0b11110000)
        {
            count++;

            if (count == n + 1)
            {
                if ((this->data[i] & 0b10000000) == 0)
                {
                    return static_cast<CodePoint>(this->data[i] & 0b01111111);
                }
                else if ((this->data[i] & 0b11100000) == 0b11000000)
                {
                    CodePoint tmp = 0;

                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00011111);
                    tmp <<= 6;
                    i++;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00111111);
                    return tmp;
                }
                else if ((this->data[i] & 0b11110000) == 0b11100000)
                {
                    CodePoint tmp = 0;

                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00001111);
                    tmp <<= 6;
                    i++;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00111111);
                    tmp <<= 6;
                    i++;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00111111);
                    return tmp;
                }
                else if ((this->data[i] & 0b11111000) == 0b11110000)
                {
                    CodePoint tmp = 0;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00000111);
                    tmp <<= 6;
                    i++;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00111111);
                    tmp <<= 6;
                    i++;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00111111);
                    tmp <<= 6;
                    i++;
                    tmp |= static_cast<CodePoint>(this->data[i] & 0b00111111);
                    return tmp;
                }
            }
        }
    }

    return std::nullopt;
}

void UTF8String::append(char c)
{
    size_t i = get_byte_count();

    if (i >= this->size - 1)
    {
        this->grow();
    }

    this->data[i] = static_cast<uint8_t>(c);
    this->byteSize++;
}

void UTF8String::append(CodePoint point)
{
    size_t i = this->byteSize;

    if (this->size < 4)
    {
        this->grow(4);
    }

    if (i >= this->size - 4)
    {
        this->grow(4);
    }

    if (point <= 0x7f)
    {
        this->data[i] = static_cast<uint8_t>(point);
        i++;
        this->byteSize++;
    }
    else if (point <= 0x7ff)
    {
        this->data[i] = 0b11000000 | static_cast<uint8_t>((point >> 6) & 0b00011111);
        i++;
        this->data[i] = 0b10000000 | static_cast<uint8_t>(point & 0b00111111);
        this->byteSize += 2;
    }
    else if (point <= 0xffff)
    {
        this->data[i] = 0b11100000 | static_cast<uint8_t>((point >> 12) & 0b00001111);
        i++;
        this->data[i] = 0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111);
        i++;
        this->data[i] = 0b10000000 | static_cast<uint8_t>(point & 0b00111111);
        this->byteSize += 3;
    }
    else
    {
        this->data[i] = 0b11110000 | static_cast<uint8_t>((point >> 18) & 0b00000111);
        i++;
        this->data[i] = 0b10000000 | static_cast<uint8_t>((point >> 12) & 0b00111111);
        i++;
        this->data[i] = 0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111);
        i++;
        this->data[i] = 0b10000000 | static_cast<uint8_t>(point & 0b00111111);
        this->byteSize += 4;
    }
}
