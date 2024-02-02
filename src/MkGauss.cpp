#include "MkGauss.hpp"

MkGauss::MkGauss()
{
    Init();
}

MkGauss::MkGauss(const MkGauss &gauss)
{
    angle = gauss.angle;
    mean = gauss.mean;
    stdev = gauss.stdev;
    coVar = gauss.coVar;
    maxVal = gauss.maxVal;
}

MkGauss::~MkGauss()
{
}

void MkGauss::Init()
{
    angle = 0.0;
    mean.Initialize(2);
    stdev.Initialize(2);
    coVar.Initialize(2, 2);
    mean(0) = 0.0;
    mean(1) = 0.0;
    stdev(0) = 1.0;
    stdev(1) = 1.0;
    coVar(0, 0) = 1.0;
    coVar(0, 1) = 0.0;
    coVar(1, 0) = 0.0;
    coVar(1, 1) = 1.0;
    maxVal = Eval(mean[0], mean[1]);
}

void MkGauss::Init(MkDouble &mean, MkDouble &stdev)
{
    assert(mean.getSzX() > 0);
    assert(mean.getSzX() == stdev.getSzX());
    assert(mean.getSzY() == 1);
    assert(mean.getSzZ() == 1);

    assert(stdev.getSzX() > 0);
    assert(stdev.getSzX() == stdev.getSzX());
    assert(stdev.getSzY() == 1);
    assert(stdev.getSzZ() == 1);

    this->mean = mean;
    this->stdev = stdev;
    maxVal = Eval(mean[0], mean[1]);
    InitCovar();
}

void MkGauss::InitCovar()
{
    assert(coVar.GetFI() == 2);
    assert(coVar.GetFJ() == 2);

    coVar(0, 0) = std::cos(angle) * std::cos(angle) / 2.0 / stdev(0) / stdev(0) + std::sin(angle) * std::sin(angle) / 2.0 / stdev(1) / stdev(1);
    coVar(1, 1) = std::sin(angle) * std::sin(angle) / 2.0 / stdev(0) / stdev(0) + std::cos(angle) * std::cos(angle) / 2.0 / stdev(1) / stdev(1);
    coVar(0, 1) = coVar(1, 0) = -std::sin(angle) * std::cos(angle) / 2.0 / stdev(0) / stdev(0) + std::sin(angle) * std::cos(angle) / 2.0 / stdev(1) / stdev(1);
}

void MkGauss::SetMean(MkDouble &mean)
{
    assert(mean.getSzX() > 0);
    assert(mean.getSzX() == this->coVar.GetFI());
    assert(mean.getSzY() == 1);
    assert(mean.getSzZ() == 1);

    this->mean = mean;
    maxVal = Eval(mean[0], mean[1]);
}

void MkGauss::SetStdDev(MkDouble &stdev)
{
    assert(stdev.getSzX() > 0);
    assert(stdev.getSzX() == this->coVar.GetFI());
    assert(stdev.getSzY() == 1);
    assert(stdev.getSzZ() == 1);

    this->stdev = stdev;
    maxVal = Eval(mean[0], mean[1]);
    InitCovar();
}

double MkGauss::Eval(double x, double y)
{
    assert(this->mean.getSzX() == 2);
    assert(this->coVar.GetFI() == 2);
    assert(this->coVar.GetFJ() == 2);

    MkDouble xy(2);
    xy(0) = x;
    xy(1) = y;
    return Eval(xy);
}

double MkGauss::Eval(MkDouble &xy)
{
    assert(xy.getSzX() > 0);
    assert(xy.getSzX() == mean.getSzX());
    assert(mean.getSzX() == coVar.GetFI());
    assert(coVar.GetFI() == coVar.GetFJ());

    double expo = 0, res = 0;
    // -(a(x-x0)^2 + 2b(x-x0)(y-y0) + c(y-y0)^2)
    expo = -(coVar(0, 0) * std::pow(xy(0) - mean(0), 2) + 2 * coVar(0, 1) * (xy(0) - mean(0)) * (xy(1) - mean(1)) + coVar(1, 1) * std::pow(xy(1) - mean(1), 2));
    res = std::exp(expo);

    return res;
}

// double MkGauss::Eval_bak(MkDouble &xy)
// {
//     assert(xy.getSzX() > 0);
//     assert(xy.getSzX() == mean.getSzX());
//     assert(mean.getSzX() == coVar.GetFI());
//     assert(coVar.GetFI() == coVar.GetFJ());

//     float D = (float)xy.getSzX();

//     MkMatrix<double> covar = coVar;
//     covar.LUDecompose();
//     double det = 1.0;
//     for (int i = 0; i < D; i++)
//         det *= covar(i, i);

//     double a = 1 / std::pow(M_PI * 2.0, D / 2.0);
//     double z = 1.0 / std::sqrt(det);
//     double res = 0;

//     covar = coVar;

//     MkVector<double> v_xy(xy);
//     MkVector<double> t1(xy.getSzX());

//     for (int i = 0; i < D; i++)
//     {
//         v_xy(i) = xy(i) - mean(i);
//     }

//     MkMatrix<double> covari(covar.GetInvert());

//     for (int i = 0; i < D; i++)
//     {
//         for (int j = 0; j < D; j++)
//         {
//             t1(i) += covari(i, j) * v_xy(j);
//         }
//     }

//     double expo = 0;

//     for (int i = 0; i < D; i++)
//     {
//         expo += v_xy(i) * t1(i);
//     }

//     expo *= -0.5;

//     res = a * z * std::exp(expo);

//     return res;
// }

MkGauss &MkGauss::operator=(const MkGauss &gauss)
{
    // TODO: insert return statement here

    angle = gauss.angle;
    mean = gauss.mean;
    stdev = gauss.stdev;
    coVar = gauss.coVar;
    maxVal = gauss.maxVal;

    return *this;
}

void MkGauss::Test()
{
    std::string bef{"before.txt"}, aft{"after.txt"};
    MkMatrix<double> coVar(4, 4);
    coVar(0, 0) = 1.0;
    coVar(1, 1) = 2.0;
    coVar(2, 2) = 3.0;
    coVar(3, 3) = 4.0;

    coVar(0, 1) = 0.2;
    coVar(0, 2) = 0.3;
    coVar(0, 3) = 0.4;
    coVar(1, 2) = 0.5;
    coVar(1, 3) = 0.6;
    coVar(2, 3) = 0.7;

    coVar(1, 0) = 0.2;
    coVar(2, 0) = 0.3;
    coVar(3, 0) = 0.4;
    coVar(2, 1) = 0.5;
    coVar(3, 1) = 0.6;
    coVar(3, 2) = 0.7;

    coVar.Out((char *)bef.c_str());

    coVar.LUDecompose();

    coVar.Out((char *)aft.c_str());
}