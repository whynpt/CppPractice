#include <iostream>
#include <stdio.h>
#include "VirtualBase.h"

using namespace std;

int Base1::intFun(int var1) {
    cout << "Base1::intFun\n";
    return 0;
}

void Base1::fun(int var1, int var2) {
    cout << "Base1::fun\n";
}

void Base1::printThis() {
    printf("Base1 is %p\n", this);
}

void VirtualBase::fun(int var1, int var2) {
    cout << "this is fun of VirtualBase with " << var1 << " " << var2 << endl;
}
int Base::baseFun() {
    cout << "this is base fun.\n";
    return 0;
}

int PartialDerived::intFun(int var1) {
    cout << "this is int fun with " << var1 << " in PartialDerived.\n";
    return 0;
}

int PartialDerived::baseFun() {
    cout << "this is base fun in PartialDerived.\n";
    return 0;
}

void Derived::printSelf() {
    printf("Derived is %p\n", this);
    Base1::printThis();
}

// int Derived::baseFun() {
//     cout << "this is Derived::baseFun\n";
//     return 0;
// }

int Derived::intFun(int var1) {
    cout << "Derived::intFun\n";
    return 0;
}