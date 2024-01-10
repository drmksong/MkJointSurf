#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <random>
#include <raylib.h>
#include <raymath.h>
#include <MkArray.hpp>
#include "MkMesh.hpp"
#include "MkSurf.hpp"
#include "MkGauss.hpp"
#include "MkNormGen.hpp"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else
#define GLSL_VERSION            100
#endif

Mesh gen_mesh(MkSurf &surf);
