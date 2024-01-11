#include "MkSurf.hpp"

MkSurf::MkSurf()
{
    Init();
}

MkSurf::~MkSurf()
{
}

void MkSurf::Init()
{
    scale = 1;
    xMin = -1;
    xMax = 1;
    yMin = -1;
    yMax = 1;

    this->surfData.Initialize(100, 100);

    MkDouble mean(2);
    MkMatrix<double> covar(2, 2);

    mean(0) = 0.0;
    mean(1) = 0.0;

    covar(0, 0) = 1.0;
    covar(0, 1) = 0.0;
    covar(1, 0) = 0.0;
    covar(1, 1) = 1.0;

    this->gaussDist.Init(mean, covar);
}

void MkSurf::Bang(double cx, double cy)
{
    float dev = std::max(this->gaussDist.GetCovar()(0, 0), this->gaussDist.GetCovar()(1, 1));
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
        {
            // std::cout << std::format("Bang::i = {:3} j = {:3}", i, j) << std::endl;
            float x = (float)i / 100.0 * (this->xMax - this->xMin) + this->xMin;
            float y = (float)j / 100.0 * (this->yMax - this->yMin) + this->yMin;
            // float xt = (x - cx) * cos(this->Angle) - (y - cy) * sin(this->Angle)+cx;
            // float yt = (x - cx) * sin(this->Angle) + (y - cy) * cos(this->Angle)+cy;
            float dis = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            if (dis > 3 * dev)
                continue;
            double z = this->scale * this->gaussDist.ScaledEval(x - cx, y - cy);
            // std::cout << std::format("Bang::xt = {:3} yt = {:3} z = {:3}", xt, yt, z) << std::endl;
            this->surfData(i, j) += z;
            // (*this)(xt, yt) += z;
            // std::cout << std::format("Bang::surfData({}, {}) = {:3}",xt ,yt,(*this)(xt, yt)) << std::endl;
        }
}

void MkSurf::NegBang(double cx, double cy)
{
    float dev = std::max(this->gaussDist.GetCovar()(0, 0), this->gaussDist.GetCovar()(1, 1));
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
        {
            // std::cout << std::format("NegBang::i = {:3} j = {:3}", i, j) << std::endl;
            float x = (float)i / 100.0 * (this->xMax - this->xMin) + this->xMin;
            float y = (float)j / 100.0 * (this->yMax - this->yMin) + this->yMin;
            // float xt = (x - cx) * cos(this->Angle) - (y - cy) * sin(this->Angle)+cx;
            // float yt = (x - cx) * sin(this->Angle) + (y - cy) * cos(this->Angle)+cy;

            float dis = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            if (dis > 3 * dev)
                continue;
            double z = this->scale * this->gaussDist.ScaledEval(x - cx, y - cy);
            this->surfData(i, j) -= z;
            // std::cout << std::format("NegBang::xt = {:3} yt = {:3} z = {:3}", xt, yt, z) << std::endl;
            // (*this)(xt, yt) -= z;
            // std::cout << std::format("NegBang::surfData({}, {}) = {:3}",xt ,yt,(*this)(xt, yt)) << std::endl;
        }
}

void MkSurf::GenSurf(std::normal_distribution<double> &nd)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    MkDouble &mean = this->gaussDist.GetMean();
    MkMatrix<double> covar(2, 2), covar1(2, 2);
    int N = NumIter, N1 = N / 100;

    for (int cnt = 0; cnt < N; cnt++)
    {
        // std::cout << std::format("nd_cov(gen) = {:2}", std::abs(nd_cov(gen))) << std::endl;
        // std::cout << std::format("nd_bx(gen) = {:2}", nd_bx(gen)-5) << std::endl;
        // std::cout << std::format("nd_by(gen) = {:2}", nd_by(gen)-5) << std::endl;

        if (cnt % (N1) == 0)
            // std::cout << std::format("\rcnt = {:5}%", cnt / 100) << std::flush;
            std::cout << std::format("\rcnt = {:5}%:", cnt / N1) << std::string(cnt / N1, '.') << std::flush;

        covar(0, 1) = covar(1, 0) = 0;
        covar(0, 0) = std::max(std::abs(nd(gen)), 0.01);
        covar(1, 1) = Aniso * covar(0, 0);
        
        // std::cout << std::format("covar(0,0) = {:3} covar1(0,0) = {:3}", covar(0,0), covar1(0,0)) << std::endl;

        SetGauss(mean, covar);
        if (_nd(_gen) > 0)
            Bang(std::round(10 * _nd_bx(_gen)) / 10.0 - 6, std::round(10 * _nd_by(_gen)) / 10.0 - 6);
        else
            NegBang(std::round(10 * _nd_bx(_gen)) / 10.0 - 6, std::round(10 * _nd_by(_gen)) / 10.0 - 6);
    }
    std::cout << std::endl;
}

void MkSurf::Log()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            std::cout << this->surfData(i, j) << std::endl;
    return;
}

void MkSurf::Out() // formatted screen out
{

    for (int j = 0; j < 100; j++)
    {
        std::cout << std::setw(3) << j << " ";
        for (int i = 0; i < 100; i++)
        {
            std::cout << std::format("{:4.1}", std::round(10 * this->surfData(i, j)) / 10.0);
        }
        std::cout << std::endl;
    }

    return;
}

double &MkSurf::operator()(int i, int j)
{
    return this->surfData(i, j); 
}

double &MkSurf::operator()(float x, float y)
{
    static double zero = 0;

    int i = (int)((x - this->xMin) / (this->xMax - this->xMin) * 100);
    int j = (int)((y - this->yMin) / (this->yMax - this->yMin) * 100);
    
    // std::cout << std::format("i = {:3} j = {:3}", i, j) << std::endl;

    if (0 <= i && i < 100 && 0 <= j && j < 100) {
        // std::cout << std::format("inside loop, i = {:3} j = {:3}", i, j) << std::endl;
        return this->surfData(i, j);
    }
        
    else
        return zero; // out of range, return zero value to invalidate the updating of mesh
}

void MkSurf::Test() // simple random generation test code
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(/* 평균 = */ 0, /* 표준 편차 = */ 2);

    std::map<int, int> hist{};
    for (int n = 0; n < 10000; ++n)
    {
        ++hist[std::round(dist(gen))];
    }
    for (auto p : hist)
    {
        std::cout << std::setw(2) << p.first << ' '
                  << std::string(p.second / 100, '*') << " " << p.second << '\n';
    }
}