#include <iostream>
#include "VirtualBase.h"

using namespace std;

int main()
{
    // Base* p = new PartialDerived();
    // p->intFun(100);
    // p->baseFun();
    // cout << "done\n";
    // std::shared_ptr<Derived> p = std::make_shared<Derived>();
    std::shared_ptr<C> c = std::make_shared<C>();
    C* ptrC = c.get();
    B* ptrB = dynamic_cast<B*>(ptrC);
    ptrC->func();
    std::cout << "Address from ptrB = " << ptrB << std::endl;
    return 0;
    return 0;
}