// segfault.cpp
#include <iostream>

void cause_segfault()
{
    int *ptr = nullptr;
    *ptr = 42;
}

int main()
{
    cause_segfault();
    return 0;
}

// g++ -g -o segfault segfault.cpp