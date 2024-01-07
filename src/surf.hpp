#pragma once
#include <iomanip>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <MkArray.hpp>
#include "gauss.hpp"

class surf
{

public:
    surf();
    ~surf();
    void init();
    void init(MkDouble &Mean, MkMatrix<double> &Covar)
    {
        this->gaussDist.init(Mean, Covar);
    }

    void setGauss(MkDouble &Mean, MkMatrix<double> &Covar)
    {
        this->gaussDist.init(Mean, Covar);
    }

    void setRange(float xMin, float xMax, float yMin, float yMax)
    {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMin = yMin;
        this->yMax = yMax;
    }

    void setScale(float scale)
    {
        this->scale = scale;
    }

    MkDouble &getSurfData()
    {
        return this->surfData;
    }

    void bang(double cx, double cy);
    void rbang(double cx, double cy);

    void log();
    void out();
    double &operator()(int i, int j);
    double &operator()(float x, float y);
    void test();

private:
    MkDouble surfData;
    gauss gaussDist;
    float xMin, xMax, yMin, yMax;
    float scale;
};
