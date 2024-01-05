#pragma once
#include <cmath>
#include <MkArray.hpp>
#include <MkMatrix.hpp>

class gauss
{
public:
    gauss();
    ~gauss();
    void init();
    void init(MkDouble &Mean, MkMatrix<double> &Covar);
    void setMean(MkDouble &Mean);
    void setCovar(MkMatrix<double> &Covar);
    double eval(double x, double y);
    double eval(MkDouble &xy);
    void test();

private:
    MkDouble Mean;
    MkMatrix<double> Covar;
};