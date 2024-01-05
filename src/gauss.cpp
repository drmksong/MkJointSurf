#include "gauss.hpp"

gauss::gauss()
{
    init();
}

gauss::~gauss()
{
}

void gauss::init()
{
    Mean.Initialize(2);
    Covar.Initialize(2, 2);
    Mean(0) = 0.0;
    Mean(1) = 0.0;
    Covar(0, 0) = 1.0;
    Covar(0, 1) = 0.0;
    Covar(1, 0) = 0.0;
    Covar(1, 1) = 1.0;
}

void gauss::init(MkDouble &Mean, MkMatrix<double> &Covar)
{
    assert(Covar.GetFI() > 0);
    assert(Covar.GetFI() == Covar.GetFJ());
    assert(Mean.getSzX() == Covar.GetFI());
    assert(Mean.getSzY() == 1);
    assert(Mean.getSzZ() == 1);

    this->Mean = Mean;
    this->Covar = Covar;
}

void gauss::setMean(MkDouble &Mean)
{
    assert(Mean.getSzX() > 0);
    assert(Mean.getSzX() == this->Covar.GetFI());
    assert(Mean.getSzY() == 1);
    assert(Mean.getSzZ() == 1);

    this->Mean = Mean;
}

void gauss::setCovar(MkMatrix<double> &Covar)
{
    assert(Covar.GetFI() > 0);
    assert(Covar.GetFI() == Covar.GetFJ());
    assert(this->Mean.getSzX() == Covar.GetFI());

    this->Covar = Covar;
}

double gauss::eval(double x, double y)
{
    assert(this->Mean.getSzX() == 2);
    assert(this->Covar.GetFI() == 2);
    assert(this->Covar.GetFJ() == 2);

    MkDouble xy(2);
    xy(0) = x;
    xy(1) = y;
    return eval(xy);
}

double gauss::eval(MkDouble &xy)
{
    assert(xy.getSzX() > 0);
    assert(xy.getSzX() == Mean.getSzX());
    assert(Mean.getSzX() == Covar.GetFI());
    assert(Covar.GetFI() == Covar.GetFJ());

    float D = (float)xy.getSzX();

    MkMatrix<double> covar = Covar;
    covar.LUDecompose();
    double det = 1.0;
    for (int i = 0; i < D; i++)
        det *= covar(i, i);

    double a = 1 / std::pow(M_PI * 2.0, D / 2.0);
    double z = 1.0 / std::sqrt(det);
    double res = 0;

    covar = Covar;

    MkVector<double> v_xy(xy);
    MkVector<double> t1(xy.getSzX());

    for (int i = 0; i < D; i++)
    {
        v_xy(i) = xy(i) - Mean(i);
    }
    MkMatrix<double> covari(covar.GetInvert());

    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
            t1(i) += covari(i, j) * v_xy(j);
        }
    }

    double expo = 0;

    for (int i = 0; i < D; i++)
    {
        expo += v_xy(i) * t1(i);
    }

    expo *= -0.5;

    res = a * z * std::exp(expo);

    return res;
}

void gauss::test()
{
    std::string bef{"before.txt"}, aft{"after.txt"};
    MkMatrix<double> Covar(4, 4);
    Covar(0, 0) = 1.0;
    Covar(1, 1) = 2.0;
    Covar(2, 2) = 3.0;
    Covar(3, 3) = 4.0;

    Covar(0, 1) = 0.2;
    Covar(0, 2) = 0.3;
    Covar(0, 3) = 0.4;
    Covar(1, 2) = 0.5;
    Covar(1, 3) = 0.6;
    Covar(2, 3) = 0.7;

    Covar(1, 0) = 0.2;
    Covar(2, 0) = 0.3;
    Covar(3, 0) = 0.4;
    Covar(2, 1) = 0.5;
    Covar(3, 1) = 0.6;
    Covar(3, 2) = 0.7;

    Covar.Out((char *)bef.c_str());

    Covar.LUDecompose();

    Covar.Out((char *)aft.c_str());
}