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
#define GLSL_VERSION 330
#else
#define GLSL_VERSION 100
#endif

Mesh gen_mesh(MkSurf &surf);

// For reference, here are the definitions of the raylib structs:
// Mesh, vertex data and vao/vbo
// typedef struct Mesh {
//     int vertexCount;        // Number of vertices stored in arrays
//     int triangleCount;      // Number of triangles stored (indexed or not)

//     // Vertex attributes data
//     float *vertices;        // Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
//     float *texcoords;       // Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
//     float *texcoords2;      // Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
//     float *normals;         // Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
//     float *tangents;        // Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
//     unsigned char *colors;      // Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
//     unsigned short *indices;    // Vertex indices (in case vertex data comes indexed)

//     // Animation vertex data
//     float *animVertices;    // Animated vertex positions (after bones transformations)
//     float *animNormals;     // Animated normals (after bones transformations)
//     unsigned char *boneIds; // Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning)
//     float *boneWeights;     // Vertex bone weight, up to 4 bones influence by vertex (skinning)

//     // OpenGL identifiers
//     unsigned int vaoId;     // OpenGL Vertex Array Object id
//     unsigned int *vboId;    // OpenGL Vertex Buffer Objects id (default vertex data)
// } Mesh;

// // Shader
// typedef struct Shader {
//     unsigned int id;        // Shader program id
//     int *locs;              // Shader locations array (RL_MAX_SHADER_LOCATIONS)
// } Shader;

// // MaterialMap
// typedef struct MaterialMap {
//     Texture2D texture;      // Material map texture
//     Color color;            // Material map color
//     float value;            // Material map value
// } MaterialMap;

// // Material, includes shader and maps
// typedef struct Material {
//     Shader shader;          // Material shader
//     MaterialMap *maps;      // Material maps array (MAX_MATERIAL_MAPS)
//     float params[4];        // Material generic parameters (if required)
// } Material;

// // Transform, vertex transformation data
// typedef struct Transform {
//     Vector3 translation;    // Translation
//     Quaternion rotation;    // Rotation
//     Vector3 scale;          // Scale
// } Transform;

// // Texture, tex data stored in GPU memory (VRAM)
// typedef struct Texture {
//     unsigned int id;        // OpenGL texture id
//     int width;              // Texture base width
//     int height;             // Texture base height
//     int mipmaps;            // Mipmap levels, 1 by default
//     int format;             // Data format (PixelFormat type)
// } Texture;
