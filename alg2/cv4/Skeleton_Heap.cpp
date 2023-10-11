#include <iostream>
#include "Skeleton_Heap.h"

using namespace std;

Heap::Heap(vector<int> input)
{
    this->heap = input;
}

std::vector<int> Heap::get_heap()
{
    return this->heap;
}

std::vector<int> Heap::get_sorted()
{
    return this->sorted;
}

void Heap::build_max_heap()
{
    for (int i = this->heap.size() - 1; i >= 0; i--)
    {
        this->heapify(i);
    }
}

void Heap::heapify(int parent)
{
    int maximum = parent;
    int left_child = 2 * parent + 1;
    int right_child = 2 * parent + 2;

    if (left_child < this->heap.size() && this->heap[left_child] > this->heap[maximum])
    {
        maximum = left_child;
    }

    if (right_child < this->heap.size() && this->heap[right_child] > this->heap[maximum])
    {
        maximum = right_child;
    }

    if (maximum != parent)
    {
        swap(this->heap[maximum], this->heap[parent]);

        this->heapify(maximum);
    }
}

void Heap::heap_sort()
{
    std::vector<int> tmp = heap;
    int length = this->heap.size();

    for (int i = 0; i < length; i++)
    {
        this->remove_root();
    }

    this->heap = tmp;
}

void Heap::insert_element(int new_element)
{
    this->heap.push_back(new_element);
    int current = this->heap.size() - 1;

    while (current > 0)
    {
        int parent = (current - 1) / 2;

        if (this->heap[current] > this->heap[parent])
        {
            swap(this->heap[current], this->heap[parent]);
            current = parent;
        }
        else
        {
            break;
        }
    }

    this->sorted = std::vector<int>(0);
}

void Heap::remove_root()
{
    swap(this->heap[0], this->heap[this->heap.size() - 1]);
    this->sorted.push_back(this->heap.back());
    this->heap.pop_back();

    heapify(0);
}

void Heap::print_heap()
{
    std::cout << "Say printing heap: " << std::endl;
    for (auto each : this->heap)
    {
        std::cout << each << " ";
    }

    std::cout << std::endl;
}

void Heap::print_sorted()
{
    std::cout << "Say printing sorted: " << std::endl;
    for (auto each : this->sorted)
    {
        std::cout << each << " ";
    }

    std::cout << std::endl;
}
