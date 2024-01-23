#include "MkEvalJRC.hpp"

MkEvalJRC::MkEvalJRC()
{
}

MkEvalJRC::~MkEvalJRC()
{
}

double MkEvalJRC::cal_theta_s()
{

    return this->theta_s;
}

double MkEvalJRC::cal_theta_g()
{
    return this->theta_g;
}

double MkEvalJRC::cal_theta_2s()
{
    return this->theta_2s;
}

double MkEvalJRC::cal_S_sT()
{
    return this->S_sT;
}

double MkEvalJRC::cal_S_sF()
{
    return this->S_sF;
}

double MkEvalJRC::cal_Van()
{
    return this->Van;
}

double MkEvalJRC::cal_Zsa()
{
    return this->Zsa;
}

double MkEvalJRC::cal_Zrms()
{
    return this->Zrms;
}

double MkEvalJRC::cal_Zrange()
{
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
