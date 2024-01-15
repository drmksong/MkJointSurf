#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <random>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <MkArray.hpp>
#include <json/json.h>
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
