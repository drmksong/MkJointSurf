#include "MkEvalJRC.hpp"

MkEvalJRC::MkEvalJRC()
{
}

MkEvalJRC::~MkEvalJRC()
{
}

double MkEvalJRC::cal_theta_s()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    int szX = surfData.GetSurfData().getSzX();
    int szY = surfData.GetSurfData().getSzY();

    float xmin = surfData.GetXMin();
    float xmax = surfData.GetXMax();
    float ymin = surfData.GetYMin();
    float ymax = surfData.GetYMax();
    float sum = 0;

    for (int i = 0; i < szX - 1; i++)
    {
        for (int j = 0; j < szY - 1; j++)
        {
            MkPoint p1, p2, p3, p4;
            int ii = i + 1, jj = j + 1;

            p1.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p1.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p1.Z = surfData.GetSurfData()(i, j);

            p2.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p2.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p2.Z = surfData.GetSurfData()(ii, j);

            p3.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p3.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p3.Z = surfData.GetSurfData()(i, jj);

            p4.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p4.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p4.Z = surfData.GetSurfData()(ii, jj);

            // TODO: peculiar bug here that the order of points result in different normal vector -> check MkTriangle::CalNormal()
            MkTriangle t1(p1, p2, p3), t2(p2, p4, p3);

            MkVector<double> v1, v2;
            v1 = t1.GetNormal();
            v2 = t2.GetNormal();
            // std::cout << std::format("t1 dip : {:5.2f}, t2 dip : {:5.2f}", std::acos(v1[2]) * 180 / 3.14159, std::acos(v2[2]) * 180 / 3.14159) << std::endl;
            sum += (std::acos(v1[2]) + std::acos(v2[2])) * 180 / 3.14159;
        }
    }
    this->theta_s = sum / (szX - 1) / (szY - 1) / 2;
    std::cout << std::format("theta_s : {:5.2f}", this->theta_s) << std::endl;

    return this->theta_s;
}

double MkEvalJRC::cal_theta_g()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);
    return this->theta_g;
}

double MkEvalJRC::cal_theta_2s()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    int szX = surfData.GetSurfData().getSzX();
    int szY = surfData.GetSurfData().getSzY();

    float xmin = surfData.GetXMin();
    float xmax = surfData.GetXMax();
    float ymin = surfData.GetYMin();
    float ymax = surfData.GetYMax();
    float sum = 0;
    float tan2 = 0;

    for (int i = 0; i < szX - 1; i++)
    {
        for (int j = 0; j < szY - 1; j++)
        {
            MkPoint p1, p2, p3, p4;
            int ii = i + 1, jj = j + 1;

            p1.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p1.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p1.Z = surfData.GetSurfData()(i, j);

            p2.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p2.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p2.Z = surfData.GetSurfData()(ii, j);

            p3.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p3.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p3.Z = surfData.GetSurfData()(i, jj);

            p4.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p4.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p4.Z = surfData.GetSurfData()(ii, jj);

            // TODO: peculiar bug here that the order of points result in different normal vector -> check MkTriangle::CalNormal()
            MkTriangle t1(p1, p2, p3), t2(p2, p4, p3);

            MkVector<double> v1, v2;
            v1 = t1.GetNormal();
            v2 = t2.GetNormal();
            // std::cout << std::format("t1 dip : {:5.2f}, t2 dip : {:5.2f}", std::acos(v1[2]) * 180 / 3.14159, std::acos(v2[2]) * 180 / 3.14159) << std::endl;
            tan2 = std::tan(std::acos(v1[2])) * std::tan(std::acos(v2[2]));
            sum += tan2;
        }
    }
    this->theta_2s = std::sqrt(sum / (szX - 1) / (szY - 1) / 2);
    std::cout << std::format("theta_2s : {:5.2f}", this->theta_2s) << std::endl;

    return this->theta_2s;
}

double MkEvalJRC::cal_S_sT()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    int szX = surfData.GetSurfData().getSzX();
    int szY = surfData.GetSurfData().getSzY();

    float xmin = surfData.GetXMin();
    float xmax = surfData.GetXMax();
    float ymin = surfData.GetYMin();
    float ymax = surfData.GetYMax();
    float sum3d = 0, sum2d = 0;

    for (int i = 0; i < szX - 1; i++)
    {
        for (int j = 0; j < szY - 1; j++)
        {
            MkPoint p1, p2, p3, p4;
            int ii = i + 1, jj = j + 1;

            p1.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p1.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p1.Z = surfData.GetSurfData()(i, j);

            p2.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p2.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p2.Z = surfData.GetSurfData()(ii, j);

            p3.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p3.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p3.Z = surfData.GetSurfData()(i, jj);

            p4.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p4.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p4.Z = surfData.GetSurfData()(ii, jj);

            // TODO: peculiar bug here that the order of points result in different normal vector -> check MkTriangle::CalNormal()
            MkTriangle t1(p1, p2, p3), t2(p2, p4, p3);
            sum3d += t1.GetArea3D() + t2.GetArea3D();
            sum2d += t1.GetArea2D() + t2.GetArea2D();
        }
    }

    this->S_sT = sum3d / sum2d; // TODO: this is based on the assumption that the surface is a rectangle, which may not be always true...
    std::cout << std::format("S_sT : {:6.4f}", this->S_sT) << std::endl;

    return this->S_sT;
}

double MkEvalJRC::cal_S_sF()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    return this->S_sF;
}

double MkEvalJRC::cal_Van()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);
    return this->Van;
}

double MkEvalJRC::cal_Zsa()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    int szX = surfData.GetSurfData().getSzX();
    int szY = surfData.GetSurfData().getSzY();

    float sum = 0;

    for (int i = 0; i < szX; i++)
    {
        for (int j = 0; j < szY; j++)
        {
            sum += std::abs(surfData.GetSurfData()(i, j));
        }
    }
    this->Zsa = (sum / (szX * szY));
    std::cout << std::format("Zsa : {:5.2f}", this->Zsa) << std::endl;

    return this->Zsa;
}

double MkEvalJRC::cal_Zrms()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    int szX = surfData.GetSurfData().getSzX();
    int szY = surfData.GetSurfData().getSzY();

    float xmin = surfData.GetXMin();
    float xmax = surfData.GetXMax();
    float ymin = surfData.GetYMin();
    float ymax = surfData.GetYMax();
    float sum_2h = 0;

    for (int i = 0; i < szX - 1; i++)
    {
        for (int j = 0; j < szY - 1; j++)
        {
            MkPoint p1, p2, p3, p4;
            int ii = i + 1, jj = j + 1;
            float height = 0, area = 0;

            p1.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p1.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p1.Z = surfData.GetSurfData()(i, j);
            height += p1.Z;

            p2.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p2.Y = (float)(j) / (float)szY * (ymax - ymin) + ymin;
            p2.Z = surfData.GetSurfData()(ii, j);
            height += p1.Z;

            p3.X = (float)(i) / (float)szX * (xmax - xmin) + xmin;
            p3.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p3.Z = surfData.GetSurfData()(i, jj);
            height += p1.Z;

            p4.X = (float)(ii) / (float)szX * (xmax - xmin) + xmin;
            p4.Y = (float)(jj) / (float)szY * (ymax - ymin) + ymin;
            p4.Z = surfData.GetSurfData()(ii, jj);
            height += p1.Z;

            // TODO: peculiar bug here that the order of points result in different normal vector -> check MkTriangle::CalNormal()
            MkTriangle t1(p1, p2, p3), t2(p2, p4, p3);

            height /= 4;
            area = t1.GetArea2D() + t2.GetArea2D();
            // sum_2h += height * height * area; // TODO: equation shows the integral of h^2 dA, but not sure if it is summation of h^2
            sum_2h += height * height; // TODO: equation shows the integral of h^2 dA, but not sure if it is summation of h^2
        }
    }

    this->Zrms = std::sqrt(sum_2h/(szX*szY)) ; // TODO: this is based on the assumption that the surface is a rectangle, which may not be always true...
    std::cout << std::format("Zrms : {:6.4f}", this->Zrms) << std::endl;

    return this->Zrms;
}

double MkEvalJRC::cal_Zrange()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);

    int szX = surfData.GetSurfData().getSzX();
    int szY = surfData.GetSurfData().getSzY();

    double zmax = -1e10, zmin = 1e10;

    for (int i = 0; i < szX; i++)
    {
        for (int j = 0; j < szY; j++)
        {
            zmax = std::max(zmax, surfData.GetSurfData()(i, j));
            zmin = std::min(zmin, surfData.GetSurfData()(i, j));
        }
    }
    this->Zrange = zmax - zmin;
    std::cout << std::format("Zrange : {:5.2f}", this->Zrange) << std::endl;

    return this->Zrange;
}

void MkEvalJRC::eval()
{

    cal_theta_s();
    cal_theta_g();
    cal_theta_2s();
    cal_S_sT();
    cal_S_sF();
    cal_Van();
    cal_Zsa();
    cal_Zrms();
    cal_Zrange();
}

void MkEvalJRC::findRMSplane()
{




}
