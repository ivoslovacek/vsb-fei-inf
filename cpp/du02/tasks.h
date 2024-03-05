#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <optional>

using CodePoint = uint32_t;

class UTF8String
{
  private:
    uint8_t *data;
    size_t size;
    size_t byteSize;

    void grow();
    void grow(unsigned long min);

  public:
    UTF8String();
    UTF8String(const char *str);
    UTF8String(std::vector<CodePoint> str);
    UTF8String(const UTF8String &str);
    ~UTF8String();

    UTF8String &operator=(const UTF8String &str);
    std::optional<uint8_t> operator[](unsigned long i) const;
    UTF8String operator+(const UTF8String &str);
    UTF8String &operator+=(const UTF8String &str);
    bool operator==(const UTF8String &str) const;
    operator std::string();

    size_t get_byte_count() const;
    size_t get_point_count() const;
    std::optional<CodePoint> nth_code_point(unsigned long n) const;

    void append(char c);
    void append(CodePoint c);
};
