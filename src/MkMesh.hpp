#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <raylib.h>
#include <MkPoint.hpp>
#include "MkSurf.hpp"

// TODO: rename member function and member variable names to be more descriptive

class MkMesh
{
private:
    MkSurf surfData;
    Mesh meshData {0};
    void SetupMesh();
    // bool bDone;

public:
    MkMesh();
    MkMesh(MkSurf &surf);
    ~MkMesh();

    bool Update(MkSurf &surf);
    bool Update();
    Mesh &GetMesh(){return meshData;}
    MkSurf &GetSurf(){return surfData;}
    
    void Log();
    void Draw();
    double &operator()(int i, int j);
};
