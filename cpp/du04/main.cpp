#include "tasks.h"
#include <iostream>

int main()
{

    auto *object = new Object{{
        {"a", new Integer{1}},
        {"b", new Null{}},
        {"c", new Integer{2}},
        {"d", new Object{{{"a", new Null{}},
                          {"b", new Array({new Integer{1}, new Null{}, new Integer{3}, new Integer{2}, new Null{}})}}}},
    }};

    delete object;

    return 0;
}
