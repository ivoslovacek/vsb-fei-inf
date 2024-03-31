#pragma once

#include <exception>
#include <memory>
#include <cstdint>
#include <stack>
#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <optional>

/// UTF-8 string (reuse your previous implementation and modify it)

using CodePoint = uint32_t;

class UTF8ByteIterator;
class UTF8CodepointIterator;

class UTF8String
{
  private:
    std::vector<uint8_t> data;

  public:
    UTF8String() = default;
    UTF8String(const char *str);
    UTF8String(std::vector<CodePoint> str);
    UTF8String(std::vector<uint8_t> str);
    UTF8String(std::string str);
    UTF8String(const UTF8String &str);
    UTF8String(UTF8String &&str) noexcept;
    ~UTF8String() = default;

    UTF8String &operator=(const UTF8String &str);
    UTF8String &operator=(UTF8String &&str) noexcept;
    std::optional<uint8_t> operator[](unsigned long i) const;
    UTF8String operator+(const UTF8String &str);
    UTF8String &operator+=(const UTF8String &str);
    bool operator==(const UTF8String str) const;
    bool operator!=(const UTF8String str) const
    {
        return not(*this == str);
    }
    operator std::string();

    size_t get_byte_count() const;
    size_t get_point_count() const;
    std::optional<CodePoint> nth_code_point(unsigned long n) const;

    void append(char c);
    void append(CodePoint c);

    UTF8ByteIterator bytes() const;
    UTF8CodepointIterator codepoints() const;
};

class UTF8ByteIterator
{
  private:
    const uint8_t *vecb;
    const uint8_t *vece;

  public:
    UTF8ByteIterator(const uint8_t *begin, const uint8_t *end) : vecb(begin), vece(end){};

    const uint8_t &operator*() const;
    UTF8ByteIterator &operator++();
    UTF8ByteIterator operator+=(size_t pos);
    UTF8ByteIterator operator-=(size_t pos);
    UTF8ByteIterator operator+(int pos);
    UTF8ByteIterator operator-(int pos);
    bool operator==(const UTF8ByteIterator &other) const;
    bool operator!=(const UTF8ByteIterator &other) const;

    UTF8ByteIterator begin();
    UTF8ByteIterator end();
};

class UTF8CodepointIterator
{
  private:
    const uint8_t *vecb;
    const uint8_t *vece;

  public:
    UTF8CodepointIterator(const uint8_t *begin, const uint8_t *end) : vecb(begin), vece(end){};

    CodePoint operator*() const;
    UTF8CodepointIterator &operator++();
    UTF8CodepointIterator &operator--();
    bool operator==(const UTF8CodepointIterator &other) const;
    bool operator!=(const UTF8CodepointIterator &other) const;

    UTF8CodepointIterator begin();
    UTF8CodepointIterator end();
};

/// Binary tree
// Big data that we cannot afford to copy
struct BigData
{
    explicit BigData(int value) : value(value)
    {
    }

    BigData(const BigData &) = delete;
    BigData &operator=(const BigData &) = delete;

    int value;
};

class Tree
{
  private:
    std::shared_ptr<BigData> value;
    Tree *parent;
    std::unique_ptr<Tree> left;
    std::unique_ptr<Tree> right;

  public:
    class iterator
    {
      private:
        std::stack<Tree *> nodes;

      public:
        iterator(Tree *tree);

        Tree &operator*() const;
        iterator &operator++();
        bool operator==(iterator &other) const;
        bool operator!=(iterator &other) const;
    };

    Tree(int value)
        : value(std::make_shared<BigData>(value)), parent(nullptr), left(std::unique_ptr<Tree>()),
          right(std::unique_ptr<Tree>()){};
    Tree(std::shared_ptr<BigData> value)
        : value(value), parent(nullptr), left(std::unique_ptr<Tree>()), right(std::unique_ptr<Tree>()){};
    ~Tree() = default;

    Tree *get_parent() const;
    bool has_parent() const;
    Tree *get_left_child() const;
    Tree *get_right_child() const;
    const Tree *get_root() const;
    BigData &get_value() const;

    std::unique_ptr<Tree> take_left_child();
    std::unique_ptr<Tree> take_right_child();
    std::unique_ptr<Tree> take_child(Tree &child);

    std::unique_ptr<Tree> set_left_child(std::unique_ptr<Tree> child);
    std::unique_ptr<Tree> set_right_child(std::unique_ptr<Tree> child);

    void swap_children();
    bool is_same_tree_as(Tree *tree);
    void replace_value(std::shared_ptr<BigData> value);

    iterator begin();
    iterator end();
};

class InvalidChildException : std::exception
{
  public:
    const char *what() const noexcept override;
};
