#pragma once
#include <iomanip>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <MkArray.hpp>
#include "MkGauss.hpp"
#include "MkNormGen.hpp"

class MkSurf
{

public:
    MkSurf();
    ~MkSurf();
    void Init();
    void Init(MkDouble &Mean, MkMatrix<double> &Covar)
    {
        this->gaussDist.Init(Mean, Covar);
    }

    void SetGauss(MkDouble &Mean, MkMatrix<double> &Covar)
    {
        this->gaussDist.Init(Mean, Covar);
    }

    void SetRange(float xMin, float xMax, float yMin, float yMax)
    {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMin = yMin;
        this->yMax = yMax;
    }

    void SetScale(float scale)
    {
        this->scale = scale;
    }

    void SetNumIter(int numiter)
    {
        this->NumIter = numiter;
    }

    void SetAniso(float aniso)
    {
        this->Aniso = aniso;
    }

    void SetAngle(float angle)
    {
        this->Angle = angle * M_PI / 180.0;
    }

    MkDouble &GetSurfData()
    {
        return this->surfData;
    }

    void Bang(double cx, double cy);
    void NegBang(double cx, double cy);

    void GenSurf(std::normal_distribution<double> &);

    void Log();
    void Out();
    double &operator()(int i, int j);
    double &operator()(float x, float y);
    void Test();

    MkSurf &operator=(MkSurf &surf)
    {
        this->surfData = surf.surfData;
        this->gaussDist = surf.gaussDist;
        this->xMin = surf.xMin;
        this->xMax = surf.xMax;
        this->yMin = surf.yMin;
        this->yMax = surf.yMax;
        this->scale = surf.scale;
        this->NumIter = surf.NumIter;
        this->Aniso = surf.Aniso;
        this->Angle = surf.Angle;
        return *this;
    }

    MkSurf &operator=(MkSurf &&surf)
    {
        this->surfData = surf.surfData;
        this->gaussDist = surf.gaussDist;
        this->xMin = surf.xMin;
        this->xMax = surf.xMax;
        this->yMin = surf.yMin;
        this->yMax = surf.yMax;
        this->scale = surf.scale;
        this->NumIter = surf.NumIter;
        this->Aniso = surf.Aniso;
        this->Angle = surf.Angle;
        return *this;
    }

private:
    MkDouble surfData;
    MkGauss gaussDist;
    float xMin, xMax, yMin, yMax;
    float scale;
    int NumIter;
    float Aniso;
    float Angle;
};
