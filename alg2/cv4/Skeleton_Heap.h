#pragma once
#include <vector>

class Heap
{
private:
    std::vector<int> heap;
    std::vector<int> sorted;

public:
    Heap(std::vector<int> input);
    std::vector<int> get_heap();
    std::vector<int> get_sorted();
    void build_max_heap();
    void heapify(int index);
    void heap_sort();
    void insert_element(int new_element);
    void remove_root();
    void print_heap();
    void print_sorted();
};
