#pragma once

// Reference: Estimating the three-dimensional joint roughness coefficient value (JRC) of rock fracture (2019)
// calculate theta_s, theta_g, theta_2s, S_sT, S_sF, Van, Zsa, Zrms, Zrange from joint surface data
// theta_s: angularity of the surface
// theta_g: threshold angle of the surface (refer to the original paper for the definition)
// theta_2s: root mean square of the slopes of the surface
// S_sT: ratio of actual and nominal areas of the TIN meshed surface (triangle)
// S_sF: ratio of actual and nominal areas of the wireframed surface (rectangle)
// Van: ratio of net volume of the fracture surface to the nominal area of the surface, Van = Vn / An
// (Vn: net volume of the fracture surface divided by the least square plane)
// Zsa: arithmetic mean of absolute height
// Zrms: root mean square height
// Zrange: range of height (i.e., Zmax - Zmin)

#include <cmath>
#include "MkSurf.hpp"
#include <MkPoint.hpp>
#include <MkTriangle.hpp>
#include <MkMatrix.hpp>

class MkEvalJRC
{
public:
    MkEvalJRC();
    ~MkEvalJRC();

    void SetSurfData(MkSurf &surf) { surfData = surf; }
    MkSurf &GetSurfData() { return surfData; }

    double cal_theta_s();
    double cal_theta_g();
    double cal_theta_2s();
    double cal_S_sT();
    double cal_S_sF();
    double cal_Van();
    double cal_Zsa();
    double cal_Zrms();
    double cal_Zrange();
    void eval();

private:
    MkSurf surfData;
    double theta_s;
    double theta_g;
    double theta_2s;
    double S_sT;
    double S_sF;
    double Van;
    double Zsa;
    double Zrms;
    double Zrange;
};