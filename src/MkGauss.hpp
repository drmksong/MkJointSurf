#pragma once
#include <cmath>
#include <MkArray.hpp>
#include <MkMatrix.hpp>

// https://en.wikipedia.org/wiki/Gaussian_function
// https://enwikipedia.org/wiki/Multivariate_normal_distribution

class MkGauss
{
public:
    MkGauss();
    ~MkGauss();
    void Init();
    void Init(MkDouble &Mean, MkDouble &StdDev);

    void SetMean(MkDouble &Mean);
    void SetStdDev(MkDouble &StdDev);
    void SetAngle(float angle)
    {
        this->angle = angle * M_PI / 180.0;
        InitCovar();
    };

    double Eval(double x, double y);
    double Eval(MkDouble &xy);
    // double Eval_bak(MkDouble &xy);
    double ScaledEval(double x, double y) { return Eval(x, y) / maxVal; };
    double ScaledEval(MkDouble &xy) { return Eval(xy) / maxVal; };
    MkDouble &GetMean() { return mean; };
    MkDouble &GetStdDev() { return stdev; };
    MkMatrix<double> &GetCovar() { return coVar; };

    void Test();

private:
    float angle;
    MkDouble mean;
    MkDouble stdev;
    MkMatrix<double> coVar;
    double maxVal;

    void InitCovar();
};