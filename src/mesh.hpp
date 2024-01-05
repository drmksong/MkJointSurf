#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <MkPoint.hpp>

class point
{
public:
    double x, y, z;
    point(double x, double y, double z) : x(x), y(y), z(z) {}
};

class mesh
{
private:
    MkPoints vertices;
    void setupMesh();

public:
    mesh();
    mesh(MkPoints &vertices);
    ~mesh();

    bool update(MkArray<double> &surfData);
    void log();
    void draw();
    double &operator()(int i, int j);
};
