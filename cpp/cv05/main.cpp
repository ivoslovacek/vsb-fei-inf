#include <cstdint>
#include <iostream>

class MyArray
{
  public:
    MyArray(int size) : size(size), data(new int[size])
    {
    }
    ~MyArray()
    {
        delete[] data;
    }

    size_t getSize() const
    {
        return size;
    }
    int &operator[](int index)
    {
        return data[index];
    }
    const int &operator[](int index) const
    {
        return data[index];
    }

    int *begin()
    {
        return data;
    }
    int *end()
    {
        return data + size;
    }

  private:
    size_t size = 0;
    int *data = nullptr;
};

class OddIterator
{
  public:
    OddIterator(const int *begin, const int *end) : b(begin), e(end)
    {
        if (*begin % 2 == 0)
            ++(*this);
    }

    const int &operator*() const
    {
        return *this->b;
    }

    OddIterator &operator++()
    {
        do
        {
            this->b++;
        } while (*this->b % 2 != 1 && this->b != this->e);

        return *this;
    }

    bool operator!=(const OddIterator &other) const
    {
        return this->b != other.e;
    }

    const int *b;
    const int *e;
};

class OddIterable
{
  public:
    OddIterable(const MyArray &arr) : arr(arr)
    {
    }

    OddIterator begin() const
    {
        return OddIterator(&arr[0], &arr[arr.getSize()]);
    }

    OddIterator end() const
    {
        return OddIterator(&arr[arr.getSize()], &arr[arr.getSize()]);
    }

  private:
    const MyArray &arr;
};

int main()
{
    MyArray arr(10);
    for (int i = 0; i < 10; ++i)
    {
        arr[i] = i * 7;
    }
    std::cout << "Iterable " << std::endl;
    for (auto &item : arr)
    {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    OddIterable oddIterable(arr);
    std::cout << "OddIterable " << std::endl;
    for (auto &item : oddIterable)
    {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    // EvenIterable evenIterable(arr);
    // std::cout << "EvenIterable " << std::endl;
    // for (auto &item : evenIterable) {
    //     std::cout << item << " ";
    // }

    return 0;
}
