#pragma once

#include <random>
#include <raylib.h>
#include <raymath.h>
#include <MkArray.hpp>
#include "mesh.hpp"
#include "surf.hpp"
#include "gauss.hpp"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else
#define GLSL_VERSION            100
#endif

Mesh gen_mesh(surf &surf);
