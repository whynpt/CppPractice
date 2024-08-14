#pragma once

class VirtualBase {
public:
    virtual int intFun(int var1) = 0;
    virtual void fun(int var1, int var2);
};

class Base {
public:
    int baseFun();
};

class Base1 : public VirtualBase {
public:
    int intFun(int var1) = 0;
    void fun(int var1, int var2);
    void printThis();
};

class PartialDerived : public VirtualBase, public Base {
public:
    int intFun(int var1) override;
    int baseFun();
};

class Derived : public Base1, public Base {
public:
    // Derived():addr(3){}
    // int addr = 3;
    void printSelf();
    int intFun(int var1);
};

class A {
public:
    virtual void func() {
        std::cout << "A::func, this = " << this << std::endl;
    }
    virtual ~A() = default;
};

class B {
public:
    virtual void func() {
        std::cout << "B::func, this = " << this << std::endl;
    }
    virtual ~B() = default;
};

class C : public A, public B {
public:
    void func() override {
        A::func();
        B::func();
        std::cout << "C::func, this = " << this << std::endl;
    }
};

