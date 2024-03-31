#include "tasks.h"
#include <cstdint>
#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <vector>

UTF8String::UTF8String(const char *str)
{
    this->data = std::vector<uint8_t>();

    size_t str_len = std::strlen(str);
    this->data.reserve(str_len);

    for (unsigned long i = 0; i < str_len; i++)
    {
        this->data.emplace_back(static_cast<uint8_t>(str[i]));
    }
}

UTF8String::UTF8String(std::vector<CodePoint> str)
{
    this->data = std::vector<uint8_t>();
    this->data.reserve(str.size() * 4);

    for (CodePoint point : str)
    {
        if (point <= 0x7f)
        {
            this->data.emplace_back(static_cast<uint8_t>(point));
        }
        else if (point <= 0x7ff)
        {
            this->data.emplace_back(0b11000000 | static_cast<uint8_t>((point >> 6) & 0b00011111));
            this->data.emplace_back(0b10000000 | static_cast<uint8_t>(point & 0b00111111));
        }
        else if (point <= 0xffff)
        {
            this->data.emplace_back(0b11100000 | static_cast<uint8_t>((point >> 12) & 0b00001111));
            this->data.emplace_back(0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111));
            this->data.emplace_back(0b10000000 | static_cast<uint8_t>(point & 0b00111111));
        }
        else
        {
            this->data.emplace_back(0b11110000 | static_cast<uint8_t>((point >> 18) & 0b00000111));
            this->data.emplace_back(0b10000000 | static_cast<uint8_t>((point >> 12) & 0b00111111));
            this->data.emplace_back(0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111));
            this->data.emplace_back(0b10000000 | static_cast<uint8_t>(point & 0b00111111));
        }
    }
}

UTF8String::UTF8String(std::vector<uint8_t> str) : data(str)
{
}

UTF8String::UTF8String(std::string str) : data(std::vector<uint8_t>(str.begin(), str.end()))
{
}

UTF8String::UTF8String(const UTF8String &str)
{
    this->data = str.data;
}

UTF8String::UTF8String(UTF8String &&str) noexcept
{
    this->data = std::move(str.data);
}

UTF8String &UTF8String::operator=(const UTF8String &str)
{
    if (this != &str)
    {
        this->data = str.data;
    }

    return *this;
}

UTF8String &UTF8String::operator=(UTF8String &&str) noexcept
{
    if (this != &str)
    {
        this->data = std::move(str.data);
    }

    return *this;
}

std::optional<uint8_t> UTF8String::operator[](unsigned long i) const
{
    if (i >= this->data.size())
    {
        return std::nullopt;
    }

    return std::optional<uint8_t>(this->data[i]);
}

UTF8String UTF8String::operator+(const UTF8String &str)
{
    UTF8String newStr = UTF8String(*this);
    newStr.data.insert(newStr.data.end(), str.data.begin(), str.data.end());

    return newStr;
}

UTF8String &UTF8String::operator+=(const UTF8String &str)
{
    this->data.insert(this->data.end(), str.data.begin(), str.data.end());

    return *this;
}

bool UTF8String::operator==(const UTF8String str) const
{
    return this->data == str.data;
}

UTF8String::operator std::string()
{
    return std::string(this->data.begin(), this->data.end());
}

size_t UTF8String::get_byte_count() const
{
    return this->data.size();
}

size_t UTF8String::get_point_count() const
{
    unsigned long count = 0;

    for (unsigned long i = 0; i < this->data.size(); i++)
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

    for (size_t i = 0; i < this->data.size(); i++)
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
    this->data.emplace_back(static_cast<uint8_t>(c));
}

void UTF8String::append(CodePoint point)
{

    if (point <= 0x7f)
    {
        this->data.emplace_back(static_cast<uint8_t>(point));
    }
    else if (point <= 0x7ff)
    {
        this->data.emplace_back(0b11000000 | static_cast<uint8_t>((point >> 6) & 0b00011111));
        this->data.emplace_back(0b10000000 | static_cast<uint8_t>(point & 0b00111111));
    }
    else if (point <= 0xffff)
    {
        this->data.emplace_back(0b11100000 | static_cast<uint8_t>((point >> 12) & 0b00001111));
        this->data.emplace_back(0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111));
        this->data.emplace_back(0b10000000 | static_cast<uint8_t>(point & 0b00111111));
    }
    else
    {
        this->data.emplace_back(0b11110000 | static_cast<uint8_t>((point >> 18) & 0b00000111));
        this->data.emplace_back(0b10000000 | static_cast<uint8_t>((point >> 12) & 0b00111111));
        this->data.emplace_back(0b10000000 | static_cast<uint8_t>((point >> 6) & 0b00111111));
        this->data.emplace_back(0b10000000 | static_cast<uint8_t>(point & 0b00111111));
    }
}

UTF8ByteIterator UTF8String::bytes() const
{
    return UTF8ByteIterator(this->data.data(), this->data.data() + this->data.size());
}

UTF8CodepointIterator UTF8String::codepoints() const
{
    return UTF8CodepointIterator(this->data.data(), this->data.data() + this->data.size());
}

const uint8_t &UTF8ByteIterator::operator*() const
{
    return *this->vecb;
}

UTF8ByteIterator UTF8ByteIterator::begin()
{
    return UTF8ByteIterator(this->vecb, this->vece);
}

UTF8ByteIterator UTF8ByteIterator::end()
{
    return UTF8ByteIterator(this->vece, this->vece);
}

UTF8ByteIterator &UTF8ByteIterator::operator++()
{
    this->vecb++;

    return *this;
}

UTF8ByteIterator UTF8ByteIterator::operator+=(size_t pos)
{
    this->vecb += pos;
    return *this;
}

UTF8ByteIterator UTF8ByteIterator::operator-=(size_t pos)
{
    this->vecb -= pos;
    return *this;
}

UTF8ByteIterator UTF8ByteIterator::operator+(int pos)
{
    return UTF8ByteIterator(this->vecb + pos, this->vece);
}

UTF8ByteIterator UTF8ByteIterator::operator-(int pos)
{
    return UTF8ByteIterator(this->vecb - pos, this->vece);
}

bool UTF8ByteIterator::operator==(const UTF8ByteIterator &other) const
{
    return this->vecb == other.vecb;
}

bool UTF8ByteIterator::operator!=(const UTF8ByteIterator &other) const
{
    return !(*this == other);
}

UTF8CodepointIterator UTF8CodepointIterator::begin()
{
    return UTF8CodepointIterator(this->vecb, this->vece);
}

UTF8CodepointIterator UTF8CodepointIterator::end()
{
    return UTF8CodepointIterator(this->vece, this->vece);
}

CodePoint UTF8CodepointIterator::operator*() const
{
    if ((*this->vecb & 0b10000000) == 0)
    {
        return static_cast<CodePoint>(*this->vecb & 0b01111111);
    }
    else if ((*this->vecb & 0b11100000) == 0b11000000)
    {
        CodePoint tmp = 0;

        tmp |= static_cast<CodePoint>(*this->vecb & 0b00011111);
        tmp <<= 6;
        tmp |= static_cast<CodePoint>(*(this->vecb + 1) & 0b00111111);
        return tmp;
    }
    else if ((*this->vecb & 0b11110000) == 0b11100000)
    {
        CodePoint tmp = 0;

        tmp |= static_cast<CodePoint>(*this->vecb & 0b00001111);
        tmp <<= 6;
        tmp |= static_cast<CodePoint>(*(this->vecb + 1) & 0b00111111);
        tmp <<= 6;
        tmp |= static_cast<CodePoint>(*(this->vecb + 2) & 0b00111111);
        return tmp;
    }
    else
    {
        CodePoint tmp = 0;
        tmp |= static_cast<CodePoint>(*this->vecb & 0b00000111);
        tmp <<= 6;
        tmp |= static_cast<CodePoint>(*(this->vecb + 1) & 0b00111111);
        tmp <<= 6;
        tmp |= static_cast<CodePoint>(*(this->vecb + 2) & 0b00111111);
        tmp <<= 6;
        tmp |= static_cast<CodePoint>(*(this->vecb + 3) & 0b00111111);
        return tmp;
    }
}

UTF8CodepointIterator &UTF8CodepointIterator::operator++()
{
    if ((*this->vecb & 0b10000000) == 0)
    {
        this->vecb++;
    }
    else if ((*this->vecb & 0b11100000) == 0b11000000)
    {
        this->vecb += 2;
    }
    else if ((*this->vecb & 0b11110000) == 0b11100000)
    {
        this->vecb += 3;
    }
    else if ((*this->vecb & 0b11111000) == 0b11110000)
    {
        this->vecb += 4;
    }

    return *this;
}

UTF8CodepointIterator &UTF8CodepointIterator::operator--()
{
    do
    {
        this->vecb--;
    } while ((*this->vecb & 0b11000000) == 0b10000000);

    return *this;
}

bool UTF8CodepointIterator::operator==(const UTF8CodepointIterator &other) const
{
    return this->vecb == other.vecb;
}

bool UTF8CodepointIterator::operator!=(const UTF8CodepointIterator &other) const
{
    return not(*this == other);
}

Tree *Tree::get_parent() const
{
    return this->parent;
}

bool Tree::has_parent() const
{
    return (this->parent != nullptr) ? true : false;
}

Tree *Tree::get_left_child() const
{
    return this->left.get();
}

Tree *Tree::get_right_child() const
{
    return this->right.get();
}

const Tree *Tree::get_root() const
{
    if (!this->has_parent())
    {
        return this;
    }

    auto root = this->get_parent();

    for (auto tmp = this->get_parent(); tmp != nullptr; tmp = tmp->get_parent())
    {
        root = tmp;
    }

    return root;
}

BigData &Tree::get_value() const
{
    return *(this->value.get());
}

std::unique_ptr<Tree> Tree::take_left_child()
{
    if (this->left)
    {
        this->left->parent = nullptr;
    }
    return std::move(this->left);
}

std::unique_ptr<Tree> Tree::take_right_child()
{
    if (this->right)
    {
        this->right->parent = nullptr;
    }

    return std::move(this->right);
}

std::unique_ptr<Tree> Tree::take_child(Tree &child)
{
    if (this->left.get() == &child)
    {
        this->left->parent = nullptr;
        return std::move(this->left);
    }
    else if (this->right.get() == &child)
    {
        this->right->parent = nullptr;
        return std::move(this->right);
    }
    else
    {
        throw InvalidChildException();
    }
}

std::unique_ptr<Tree> Tree::set_left_child(std::unique_ptr<Tree> child)
{
    auto old = std::move(this->left);

    if (old)
    {
        old->parent = nullptr;
    }

    if (child)
    {
        child->parent = this;
    }

    this->left = std::move(child);

    return std::move(old);
}

std::unique_ptr<Tree> Tree::set_right_child(std::unique_ptr<Tree> child)
{
    auto old = std::move(this->right);

    if (old)
    {
        old->parent = this;
    }

    if (child)
    {
        child->parent = this;
    }

    this->right = std::move(child);

    return std::move(old);
}

void Tree::swap_children()
{
    auto tmp = std::move(this->left);
    this->left = std::move(this->right);
    this->right = std::move(tmp);
}

bool Tree::is_same_tree_as(Tree *tree)
{
    return (this->get_root() == tree->get_root());
}

void Tree::replace_value(std::shared_ptr<BigData> value)
{
    this->value = value;

    if (this->left)
    {
        this->left->replace_value(value);
    }

    if (this->right)
    {
        this->right->replace_value(value);
    }
}

Tree::iterator::iterator(Tree *tree)
{
    while (tree != nullptr)
    {
        this->nodes.push(tree);
        tree = tree->get_left_child();
    }
}

Tree &Tree::iterator::operator*() const
{
    return *(this->nodes.top());
}

Tree::iterator &Tree::iterator::operator++()
{
    auto current = this->nodes.top();
    this->nodes.pop();

    if (current->get_right_child())
    {
        current = current->get_right_child();

        while (current != nullptr)
        {
            this->nodes.push(current);
            current = current->get_left_child();
        }
    }

    return *this;
}

bool Tree::iterator::operator==(Tree::iterator &other) const
{
    return (this->nodes == other.nodes);
}

bool Tree::iterator::operator!=(Tree::iterator &other) const
{
    return !(*this == other);
}

Tree::iterator Tree::begin()
{
    return iterator(this);
}

Tree::iterator Tree::end()
{
    return iterator(nullptr);
}

const char *InvalidChildException::what() const noexcept
{
    return "Given child is not a child of the tree";
}
