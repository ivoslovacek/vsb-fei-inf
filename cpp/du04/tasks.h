#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

class PrintVisitor;
class RemoveNullVisitor;

class Value
{
  public:
    Value() = default;
    virtual ~Value()
    {
    }

    Value(const Value &) = delete;
    Value operator=(Value &) = delete;

    virtual Value *operator[](size_t index) const;
    virtual Value *operator[](std::string index) const;

    virtual Value *clone() const = 0;
    virtual void accept(const PrintVisitor &visitor) const = 0;
    virtual void accept(const RemoveNullVisitor &visitor) = 0;

  private:
};

class Integer : public Value
{
  public:
    Integer(int value);

    Integer *clone() const override;
    int get_value() const;
    void accept(const PrintVisitor &visitor) const override;
    void accept(const RemoveNullVisitor &visitor) override;

  private:
    int value;
};

class Array : public Value
{
  public:
    Array();
    Array(std::vector<Value *> array);
    ~Array() override;

    Value *operator[](size_t index) const override;

    Array *clone() const override;
    size_t size() const;
    void append(Value *value);
    void remove(size_t index);

    void accept(const PrintVisitor &visitor) const override;
    void accept(const RemoveNullVisitor &visitor) override;

  private:
    std::vector<Value *> data;
};

class Object : public Value
{
  public:
    Object();
    Object(std::vector<std::pair<std::string, Value *>> objects);
    ~Object() override;

    Value *operator[](std::string key) const override;

    Object *clone() const override;
    size_t size() const;
    std::vector<std::string> keys() const;
    void insert(std::string key, Value *value);
    void remove(std::string key);
    void accept(const PrintVisitor &visitor) const override;
    void accept(const RemoveNullVisitor &visitor) override;

  private:
    std::unordered_map<std::string, Value *> data;
};

class Null : public Value
{
  public:
    Null *clone() const override;
    void accept(const PrintVisitor &visitor) const override;
    void accept(const RemoveNullVisitor &visitor) override;

  private:
};

class RemoveNullVisitor
{
  public:
    void visit(Integer &) const {};
    void visit(Array &value) const;
    void visit(Object &value) const;
    void visit(Null &) const {};
};

class PrintVisitor
{
  public:
    PrintVisitor(std::ostream &stream);

    void visit(const Integer &value) const;
    void visit(const Array &value) const;
    void visit(const Object &value) const;
    void visit(const Null &value) const;

  private:
    std::ostream &stream;
};

class NonIndexableObjectException : std::exception
{
    const char *what() const noexcept override
    {
        return "Tried indexing non-indexable object";
    }
};

// [*] Can individual elements be shared among different JSON containers (array/object) with the mentioned
// design? Can you take one specific element (e.g. an integer) allocated on the heap and place it inside
// an array and also inside an object?
//
// [Answer]
// I think that it would be hard to share the allocated memory among multiple objects. It would be solve
// by using `std::shared_ptr` or by creating a similiar custom container.
//
// [*] Could references (or non-owned pointers) be used for storing the elements in JSON containers?
// How would it affect the usability of arrays and objects? Try it and see how easy or hard it is :)
//
// [Answer]
// It would be pretty hard as we would have to make sure that the memory referenced will not be deallocated
// in our JSON containers lifetime. If we would access the deallocated memory from these references,
// it would lead to undefined behaviour.
//
// [*] Non-indexable objects will throw an exception when you attempt to index them using `operator[]`.
// Feel free to use an exception from the standard library, but prefer creating a custom exception
// if you can. Use a name you find suitable for the exception, the tests only check that an exception
// is thrown, not what kind of exception it is.
//
// I dont think that this is a question despite it being marked by [*], nonetheless I did create my custon exception.
//
// [*] Think about this interface. What are its benefits or disadvantages? Is it better to put the
// indexers into the root `Value` element? Or should it only be supported by types that actually
// implement indexing (arrays/objects)? Think about the trade-offs (compile-time safety vs ergonomics).
//
// [Answer]
// It provides an easy access to elements stored inside an another element. The disadvantage is that we can't know
// if the underlying elements stores multiple elements without checking for its type. I think that the operator
// should be available at the base class level as we don't have to cast the element to a specific type that supports
// this interface. I think it would be better if the operator didn't throw an exception when the element doesn't
// support it, instead it could return a nullptr which would keep the same ergonomics and improve compile-time safety.
//
// [*] Think about the return type. What should it be? Is `std::optional` required here?
//
// [Answer]
// I think that it should be a pointer to the base class. I think that `std::optional` is useless here, as we can just
// check if the pointer returned is a nullptr.
//
// [*] How can you implement copying for a polymorphic object hierarchy? What should be the return type
// of the `clone` method? If you are interested, look for "C++ covariance".
//
// [Answer]
// We can create a new copy of the elemenent and don't worry about anything, as polymorphism allows us to cast
// a derived class to its base class. The return type should be a pointer to the type I am copying. (something I didn't
// do (:)
//
//
// [*] Think about the constness of the `accept` method and of the methods in the visitor. What
// parameter type should they take? Should it be const or not? Consider creating two classes
// to represent visitors, `Visitor` and `MutatingVisitor` (or similar names).
//
// The constness depends on the stuff our visitor will be doing. If we dont need to alter the data stored in the object,
// we can make our visitor parameters constant.
//
// [*] How would the implementation look like if you have used e.g. algebraic data types instead?
// Would you need the Visitor design pattern in that case?
//
// We would store the json in simple arrays with a specific data type. We could then just access the data without any
// extra methods making the Visitors useless.
