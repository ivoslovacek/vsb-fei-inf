#include "tasks.h"
#include <algorithm>
#include <ostream>
#include <utility>
#include <vector>
#include <string>

Value *Value::operator[](size_t) const
{
    throw NonIndexableObjectException();
}

Value *Value::operator[](std::string) const
{
    throw NonIndexableObjectException();
}

Integer::Integer(int value) : Value()
{
    this->value = value;
}

int Integer::get_value() const
{
    return this->value;
}

Integer *Integer::clone() const
{
    return new Integer(this->value);
}

void Integer::accept(const PrintVisitor &visitor) const
{
    visitor.visit(*this);
}

void Integer::accept(const RemoveNullVisitor &visitor)
{
    visitor.visit(*this);
}

Array::Array()
{
    this->data = std::vector<Value *>();
}

Array::Array(std::vector<Value *> array)
{
    this->data = array;
}

Array::~Array()
{
    for (auto each : this->data)
    {
        delete each;
    }
}

Value *Array::operator[](size_t index) const
{
    if (index < this->data.size())
    {
        return this->data.at(index);
    }
    else
    {
        return nullptr;
    }
}

Array *Array::clone() const
{
    std::vector<Value *> tmp;
    tmp.reserve(this->data.size());

    for (auto each : data)
    {
        tmp.push_back(each->clone());
    }

    return new Array(tmp);
}

size_t Array::size() const
{
    return this->data.size();
}

void Array::append(Value *value)
{
    this->data.emplace_back(value);
}

void Array::remove(size_t index)
{
    if (index < this->size())
    {
        auto tmp = this->data[index];

        this->data.erase(this->data.begin() + index);
        delete tmp;
    }
}

void Array::accept(const PrintVisitor &visitor) const
{
    visitor.visit(*this);
}

void Array::accept(const RemoveNullVisitor &visitor)
{
    visitor.visit(*this);
}

Object::Object()
{
    this->data = std::unordered_map<std::string, Value *>();
}

Object::Object(std::vector<std::pair<std::string, Value *>> objects)
{
    this->data = std::unordered_map<std::string, Value *>();

    for (auto pair : objects)
    {
        this->data.insert(pair);
    }
}

Object::~Object()
{
    for (auto pair : this->data)
    {
        delete pair.second;
    }
}

Value *Object::operator[](std::string key) const
{
    if (this->data.count(key) == 1)
    {
        return this->data.at(key);
    }
    else
    {
        return nullptr;
    }
}

Object *Object::clone() const
{
    std::vector<std::pair<std::string, Value *>> tmp;
    tmp.reserve(this->data.size());

    for (auto pair : this->data)
    {
        std::pair new_pair = std::make_pair(pair.first, pair.second->clone());
        tmp.push_back(new_pair);
    }

    return new Object(tmp);
}

size_t Object::size() const
{
    return this->data.size();
}

std::vector<std::string> Object::keys() const
{
    std::vector<std::string> tmp;

    for (auto pair : this->data)
    {
        tmp.emplace_back(pair.first);
    }

    std::sort(tmp.begin(), tmp.end());

    return tmp;
};

void Object::insert(std::string key, Value *value)
{
    if (this->data.count(key) == 0)
    {
        this->data.insert(std::make_pair(key, value));
    }
    else
    {
        auto tmp = this->data[key];

        this->data.erase(key);
        delete tmp;

        this->data.insert(std::make_pair(key, value));
    }
}

void Object::remove(std::string key)
{
    auto tmp = (*this)[key];

    if (tmp != nullptr)
    {
        delete tmp;
    }

    this->data.erase(key);
}

void Object::accept(const PrintVisitor &visitor) const
{
    visitor.visit(*this);
}

void Object::accept(const RemoveNullVisitor &visitor)
{
    visitor.visit(*this);
}

Null *Null::clone() const
{
    return new Null;
}

void Null::accept(const PrintVisitor &visitor) const
{
    visitor.visit(*this);
}

void Null::accept(const RemoveNullVisitor &visitor)
{
    visitor.visit(*this);
}

void RemoveNullVisitor::visit(Array &value) const
{
    for (size_t i = 0; i < value.size(); i++)
    {
        auto tmp = value[i];

        if (Null *nulltmp = dynamic_cast<Null *>(tmp))
        {
            value.remove(i);
        }
    }
}

void RemoveNullVisitor::visit(Object &value) const
{
    for (auto key : value.keys())
    {
        if (Null *nulltmp = dynamic_cast<Null *>(value[key]))
        {
            value.remove(key);
        }
        else
        {
            value[key]->accept(*this);
        }
    }
}

PrintVisitor::PrintVisitor(std::ostream &stream) : stream(stream)
{
}

void PrintVisitor::visit(const Integer &value) const
{
    this->stream << value.get_value();
}

void PrintVisitor::visit(const Array &value) const
{
    this->stream << "[";

    for (size_t i = 0; i < value.size(); i++)
    {
        value[i]->accept(*this);

        if (i < value.size() - 1)
        {
            this->stream << ", ";
        }
    }

    this->stream << "]";
}

void PrintVisitor::visit(const Object &value) const
{
    this->stream << "{";

    auto keys = value.keys();

    for (size_t i = 0; i < keys.size(); i++)
    {
        this->stream << keys.at(i) << ": ";

        value[keys.at(i)]->accept(*this);

        if (i < keys.size() - 1)
        {
            this->stream << ", ";
        }
    }

    this->stream << "}";
}

void PrintVisitor::visit(const Null &) const
{
    this->stream << "null";
}
