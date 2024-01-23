#include "MkSurf.hpp"

// TODO: dynamic size of surfDouble and scaledSurfData, currently fixed at 100x100 but should be able to change

MkSurf::MkSurf()
{
    Init();
}

MkSurf::~MkSurf()
{
}

void MkSurf::Init()
{
    xMin = -1;
    xMax = 1;
    yMin = -1;
    yMax = 1;

    this->surfDouble.Initialize(100, 100);

    MkDouble mean(2);
    MkDouble stdev(2);

    mean(0) = 0.0;
    mean(1) = 0.0;

    stdev(0) = 1.0;
    stdev(1) = 1.0;

    this->gaussDist.Init(mean, stdev);

    scale = 1;
    NumIter = 1;
    Aniso = 1;
    Angle = 0;
    isScaled = false;
}

void MkSurf::Bang(double cx, double cy)
{
    isScaled = false;
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();
    float dev = std::max(this->gaussDist.GetCovar()(0, 0), this->gaussDist.GetCovar()(1, 1));

    for (int i = 0; i < szX; i++)
        for (int j = 0; j < szY; j++)
        {
            // std::cout << std::format("Bang::i = {:3} j = {:3}", i, j) << std::endl;
            float x = (float)i / (float)szX * (this->xMax - this->xMin) + this->xMin;
            float y = (float)j / (float)szY * (this->yMax - this->yMin) + this->yMin;

            // float xt = (x - cx) * cos(this->Angle) - (y - cy) * sin(this->Angle) + cx;
            // float yt = (x - cx) * sin(this->Angle) + (y - cy) * cos(this->Angle) + cy;

            // int ii = (int)((x - this->xMin) / (this->xMax - this->xMin) * szX + 0.5);
            // int jj = (int)((y - this->yMin) / (this->yMax - this->yMin) * szY + 0.5);
            // std::cout << std::format("Bang::x{},xt{},y{},yt{},i = {:3}, ii = {}, j = {:3} jj = {}", x, xt, y, yt, i, ii, j, jj) << std::endl;

            float dis = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            if (dis > 3 * dev)
                continue;
            double z = this->gaussDist.ScaledEval(x - cx, y - cy);
            // std::cout << std::format("Bang::xt = {:3} yt = {:3} z = {:3}", xt, yt, z) << std::endl;
            this->surfDouble(i, j) += z;
            // (*this)(xt, yt) += z;
            // std::cout << std::format("Bang::surfDouble({}, {}) = {:3}",xt ,yt,(*this)(xt, yt)) << std::endl;
        }
}

void MkSurf::NegBang(double cx, double cy)
{
    isScaled = false;
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();
    float dev = std::max(this->gaussDist.GetCovar()(0, 0), this->gaussDist.GetCovar()(1, 1));

    for (int i = 0; i < szX; i++)
        for (int j = 0; j < szY; j++)
        {
            // std::cout << std::format("NegBang::i = {:3} j = {:3}", i, j) << std::endl;
            float x = (float)i / (float)szX * (this->xMax - this->xMin) + this->xMin;
            float y = (float)j / (float)szY * (this->yMax - this->yMin) + this->yMin;

            // float xt = (x - cx) * cos(this->Angle) - (y - cy) * sin(this->Angle) + cx;
            // float yt = (x - cx) * sin(this->Angle) + (y - cy) * cos(this->Angle) + cy;

            // int ii = (int)((x - this->xMin) / (this->xMax - this->xMin) * szX + 0.5);
            // int jj = (int)((y - this->yMin) / (this->yMax - this->yMin) * szY + 0.5);
            // std::cout << std::format("NegBang::x{},xt{},y{},yt{},i = {:3}, ii = {}, j = {:3} jj = {}", x, xt, y, yt, i, ii, j, jj) << std::endl;

            float dis = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            if (dis > 3 * dev)
                continue;
            double z = this->gaussDist.ScaledEval(x - cx, y - cy);
            this->surfDouble(i, j) -= z;
            // std::cout << std::format("NegBang::xt = {:3} yt = {:3} z = {:3}", xt, yt, z) << std::endl;
            // (*this)(xt, yt) -= z;
            // std::cout << std::format("NegBang::surfDouble({}, {}) = {:3}",xt ,yt,(*this)(xt, yt)) << std::endl;
        }
}

void MkSurf::GenSurf(std::normal_distribution<double> &nd)
{
    double xmin = xMin - (xMax - xMin) * 0.1;
    double xmax = xMax + (xMax - xMin) * 0.1;
    double ymin = yMin - (yMax - yMin) * 0.1;
    double ymax = yMax + (yMax - yMin) * 0.1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution nd_bx(xmin, xmax);
    std::uniform_real_distribution nd_by(ymin, ymax);
    MkDouble stdev(2);

    isScaled = false;
    int N = NumIter, N1 = N / 100;

    for (int cnt = 0; cnt < N; cnt++)
    {
        // std::cout << std::format("nd_cov(gen) = {:2}", std::abs(nd_cov(gen))) << std::endl;
        // std::cout << std::format("nd_bx(gen) = {:2}", nd_bx(gen)-5) << std::endl;
        // std::cout << std::format("nd_by(gen) = {:2}", nd_by(gen)-5) << std::endl;

        if (N1 != 0 && cnt % (N1) == 0)
            // std::cout << std::format("\rcnt = {:5}%", cnt / 100) << std::flush;
            std::cout << std::format("\rcnt = {:5}%:", cnt / N1) << std::string(cnt / N1, '.') << std::flush;

        stdev(0) = std::max(std::abs(nd(gen)), 0.01);
        stdev(1) = Aniso * stdev(0);

        // std::cout << std::format("covar(0,0) = {:3} covar1(0,0) = {:3}", covar(0,0), covar1(0,0)) << std::endl;

        this->gaussDist.SetStdDev(stdev);

        if (_nd(_gen) < 0)
            NegBang(std::round(10 * nd_bx(_gen)) / 10.0 , std::round(10 * nd_by(_gen)) / 10.0 );
        else
            Bang(std::round(10 * nd_bx(_gen)) / 10.0 , std::round(10 * nd_by(_gen)) / 10.0 );
    }
    std::cout << std::endl;
}

void MkSurf::Rescale()
{
    double maxV = -1e10, minV = 1e10;
    double factor = 1;
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();

    if (isScaled == false)
    {
        isScaled = true;
        for (int i = 0; i < szX; i++)
        {
            for (int j = 0; j < szY; j++)
            {
                maxV = std::max(surfDouble(i, j), maxV);
                minV = std::min(surfDouble(i, j), minV);
            }
        }
        std::cout << std::format("maxV = {:5} minV = {:5}", maxV, minV) << std::endl;
        if (std::abs(maxV - minV) < 1e-3)
            return;
        else
        {
            factor = scale / (maxV - minV);
            std::cout << std::format("factor = {:5}", factor) << std::endl;
            for (int i = 0; i < szX; i++)
            {
                for (int j = 0; j < szY; j++)
                {
                    surfDouble(i, j) = surfDouble(i, j) * factor;
                }
            }
        }
    }
}

void MkSurf::Log()
{
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();

    for (int i = 0; i < szX; i++)
        for (int j = 0; j < szY; j++)
            std::cout << this->surfDouble(i, j) << std::endl;
    return;
}

void MkSurf::Out() // formatted screen out
{
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();

    for (int j = 0; j < szX; j++)
    {
        std::cout << std::setw(3) << j << " ";
        for (int i = 0; i < szY; i++)
        {
            std::cout << std::format("{:4.1}", std::round(10 * this->surfDouble(i, j)) / 10.0);
        }
        std::cout << std::endl;
    }
    return;
}

double &MkSurf::operator()(int i, int j)
{
    return this->surfDouble(i, j);
}

double &MkSurf::operator()(float x, float y)
{
    static double zero = 0;
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();

    int i = (int)((x - this->xMin) / (this->xMax - this->xMin) * szX);
    int j = (int)((y - this->yMin) / (this->yMax - this->yMin) * szY);

    // std::cout << std::format("i = {:3} j = {:3}", i, j) << std::endl;

    if (0 <= i && i < szX && 0 <= j && j < szY)
    {
        // std::cout << std::format("inside loop, i = {:3} j = {:3}", i, j) << std::endl;
        return this->surfDouble(i, j);
    }

    else
        return zero; // out of range, return zero value to invalidate the updating of mesh
}

float MkSurf::Analyze()
{
    int szX = this->surfDouble.getSzX();
    int szY = this->surfDouble.getSzY();

    this->sum = 0; // reset sum
    for (int i = 0; i < szX; i++)
    {
        for (int j = 0; j < szY; j++)
        {
            this->sum += surfDouble(i, j);
        }
    }
    return this->sum;
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