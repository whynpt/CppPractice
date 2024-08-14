#include "Demo.h"
#include <iostream>

int main()
{
    Demo d;
    if(d.empty()) {
        std::cout << "empty\n";
    }
    if(d.full()) {
        std::cout << "full\n";
    }
    return 0;
}
