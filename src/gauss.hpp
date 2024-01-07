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
    double seval(double x, double y) {return eval(x, y) / maxVal;};
    double seval(MkDouble &xy) {return eval(xy) / maxVal; };
    MkDouble &getMean() {return Mean;};
    MkMatrix<double> &getCovar() {return Covar;};

    void test();

private:
    MkDouble Mean;
    MkMatrix<double> Covar;
    double maxVal;
};