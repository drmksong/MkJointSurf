#pragma once
#include <cmath>
#include <MkArray.hpp>
#include <MkMatrix.hpp>

class MkGauss
{
public:
    MkGauss();
    ~MkGauss();
    void Init();
    void Init(MkDouble &Mean, MkMatrix<double> &Covar);
    void SetMean(MkDouble &Mean);
    void SetCovar(MkMatrix<double> &Covar);
    double Eval(double x, double y);
    double Eval(MkDouble &xy);
    double ScaledEval(double x, double y) {return Eval(x, y) / maxVal;};
    double ScaledEval(MkDouble &xy) {return Eval(xy) / maxVal; };
    MkDouble &GetMean() {return mean;};
    MkMatrix<double> &GetCovar() {return coVar;};

    void Test();

private:
    MkDouble mean;
    MkMatrix<double> coVar;
    double maxVal;
};