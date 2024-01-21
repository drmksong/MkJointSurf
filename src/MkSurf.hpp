#pragma once
#include <iomanip>
#include <format>
#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include <MkArray.hpp>
#include "MkGauss.hpp"
#include "MkNormGen.hpp"

// TODO: rename member function and member variable names to be more descriptive

class MkSurf
{

public:
    MkSurf();
    ~MkSurf();
    void Init();
    void Init(MkDouble &Mean, MkDouble &StdDev)
    {
        this->gaussDist.Init(Mean, StdDev);
    }

    void SetGauss(MkDouble &Mean, MkDouble &StdDev)
    {
        this->gaussDist.Init(Mean, StdDev);
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
        // TODO: implement Scale()
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
        this->gaussDist.SetAngle(angle);
    }

    MkDouble &GetSurfData()
    {
        return this->surfDouble;
    }

    void Bang(double cx, double cy);
    void NegBang(double cx, double cy);

    void GenSurf(std::normal_distribution<double> &);
    void Rescale(); // TODO: run automatically after GenSurf ran
    void Log();
    void Out();
    double &operator()(int i, int j);
    double &operator()(float x, float y);
    float Analyze(); // evaluate the surface if the surface is positive or negative
    void Test();

    friend std::ofstream &operator<<(std::ofstream &fs, MkSurf &surf)
    {
        fs << std::to_string(surf.surfDouble.getSzX()) << " " << std::to_string(surf.surfDouble.getSzY()) << std::endl;
        for (int i = 0; i < surf.surfDouble.getSzX(); i++)
        {
            for (int j = 0; j < surf.surfDouble.getSzY(); j++)
            {
                fs << std::to_string(surf.surfDouble(i, j)) << ", ";
            }
            fs << std::endl;
        }

        for (int i = 0; i < surf.surfDouble.getSzX(); i++)
        {
            fs << std::to_string(surf.X(i)) << ", " << std::endl;
        }

        for (int j = 0; j < surf.surfDouble.getSzY(); j++)
        {
            fs << std::to_string(surf.Y(j)) << ", " << std::endl;
        }

        return fs;
    }

    MkSurf &operator=(MkSurf &surf)
    {
        this->surfDouble = surf.surfDouble;
        this->gaussDist = surf.gaussDist;
        this->xMin = surf.xMin;
        this->xMax = surf.xMax;
        this->yMin = surf.yMin;
        this->yMax = surf.yMax;
        this->scale = surf.scale;
        this->NumIter = surf.NumIter;
        this->Aniso = surf.Aniso;
        this->Angle = surf.Angle;
        this->isScaled = surf.isScaled;
        return *this;
    }

    MkSurf &operator=(MkSurf &&surf)
    {
        this->surfDouble = surf.surfDouble;
        this->gaussDist = surf.gaussDist;
        this->xMin = surf.xMin;
        this->xMax = surf.xMax;
        this->yMin = surf.yMin;
        this->yMax = surf.yMax;
        this->scale = surf.scale;
        this->NumIter = surf.NumIter;
        this->Aniso = surf.Aniso;
        this->Angle = surf.Angle;
        this->isScaled = surf.isScaled;
        return *this;
    }

    float X(int i)
    {
        return (float)i / (float)(surfDouble.getSzX() - 1) * (xMax - xMin) + xMin;
    }

    float Y(int j)
    {
        return (float)j / (float)(surfDouble.getSzY() - 1) * (yMax - yMin) + yMin;
    }

private:
    MkDouble surfDouble;
    MkGauss gaussDist;
    float xMin, xMax, yMin, yMax;
    float scale;
    int NumIter;
    float Aniso;
    float Angle;
    bool isScaled;
    float sum; // of surfDouble to see if it is positive side or negative side

};
