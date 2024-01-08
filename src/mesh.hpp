#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <raylib.h>
#include <MkPoint.hpp>
#include "surf.hpp"


class mesh
{
private:
    surf surfData;
    Mesh meshData;
    void setupMesh();

public:
    mesh();
    mesh(surf &surfData);
    ~mesh();

    bool update(surf &surfData);
    void log();
    void draw();
    double &operator()(int i, int j);
};
