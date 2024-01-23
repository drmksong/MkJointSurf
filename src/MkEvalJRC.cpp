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
    return this->theta_2s;
}

double MkEvalJRC::cal_S_sT()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);
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
    return this->Zsa;
}

double MkEvalJRC::cal_Zrms()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);
    return this->Zrms;
}

double MkEvalJRC::cal_Zrange()
{
    assert(surfData.GetSurfData().getSzX() > 0 && surfData.GetSurfData().getSzY() > 0);
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
