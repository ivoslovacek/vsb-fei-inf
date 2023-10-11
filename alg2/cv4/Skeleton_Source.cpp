#include <iostream>
#include "Skeleton_Heap.h"

using namespace std;

int main()
{
    vector<int> input = {{-99, 99, 17, -15, 3, -8, -48, 64, 29, 77}};
    Heap object(input);
    object.print_heap();
    object.build_max_heap();
    object.print_heap();
    object.insert_element(12);
    object.print_heap();
    object.heap_sort();
    object.print_sorted();
    object.print_heap();
    object.insert_element(69);
    object.print_sorted();
    object.print_heap();

    return 0;
}
