#pragma once
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <MkArray.hpp>

class surf
{

public:
    surf();
    ~surf();
    void fillup();
    void log();
    double &operator()(int i, int j);
    void test();

private:
    MkDouble surfData;
};
