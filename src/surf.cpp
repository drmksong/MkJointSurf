#include "surf.hpp"

surf::surf()
{
    this->surfData.Initialize(100, 100);
}

surf::~surf()
{
}

double &surf::operator()(int i, int j)
{
    return this->surfData(i, j);
}

void surf::log()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            std::cout << this->surfData(i, j) << std::endl;
    return;
}

void surf::fillup()
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            this->surfData(i, j) = rand() % 100;
    return;
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