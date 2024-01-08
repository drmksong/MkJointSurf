#include "surf.hpp"

surf::surf()
{
    scale = 1;
    xMin = -1;
    xMax = 1;
    yMin = -1;
    yMax = 1;

    this->surfData.Initialize(100, 100);
}

surf::~surf()
{
}

void surf::init()
{
    MkDouble mean(2);
    MkMatrix<double> covar(2, 2);

    mean(0) = 0.0;
    mean(1) = 0.0;

    covar(0, 0) = 1.0;
    covar(0, 1) = 0.0;
    covar(1, 0) = 0.0;
    covar(1, 1) = 1.0;

    this->gaussDist.init(mean, covar);
}

void surf::bang(double cx, double cy)
{
    float dev = std::max(this->gaussDist.getCovar()(0, 0), this->gaussDist.getCovar()(1, 1));
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
        {
            double x = (double)i / 100.0 * (this->xMax - this->xMin) + this->xMin;
            double y = (double)j / 100.0 * (this->yMax - this->yMin) + this->yMin;
            float dis = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            if (dis > 3 * dev)
                continue;
            double z = this->scale * this->gaussDist.seval(x - cx, y - cy);
            this->surfData(i, j) += z;
        }
}

void surf::rbang(double cx, double cy)
{
    float dev = std::max(this->gaussDist.getCovar()(0, 0), this->gaussDist.getCovar()(1, 1));
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
        {
            double x = (double)i / 100.0 * (this->xMax - this->xMin) + this->xMin;
            double y = (double)j / 100.0 * (this->yMax - this->yMin) + this->yMin;
            float dis = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            if (dis > 3 * dev)
                continue;
            double z = this->scale * this->gaussDist.seval(x - cx, y - cy);
            this->surfData(i, j) -= z;
        }
}

void surf::log()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            std::cout << this->surfData(i, j) << std::endl;
    return;
}

void surf::out()
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

double &surf::operator()(int i, int j)
{
    return this->surfData(i, j);
}

double &surf::operator()(float x, float y)
{
    static double nil = 0;
    nil = 0;
    int i = (int)((x - this->xMin) / (this->xMax - this->xMin) * 100);
    int j = (int)((y - this->yMin) / (this->yMax - this->yMin) * 100);
    if (0 <= i && i < 100 && 0 <= j && j < 100)
        return this->surfData(i, j);
    else
        return nil; // out of range, return nil value to invalidate the updating of mesh
}

void surf::test()
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