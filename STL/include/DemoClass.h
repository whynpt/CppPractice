#pragma once
#include <iostream>

class DemoClass {
public:
    DemoClass()
    : pubInt(1), pubDou(1.0), priInt(10), priDou(10.0)
    {}

    DemoClass (int i1, double d1, int i2, double d2) {
        pubInt = i1;
        pubDou = i2;
        priInt = i2;
        priDou = d2;
    }

    ~DemoClass() {
        std::cout << "delete object\n";
    }

public:
    int pubInt;
    double pubDou;

private:
    int priInt;
    double priDou;
};

struct DemoStruct {
    int i;
    double d;
};