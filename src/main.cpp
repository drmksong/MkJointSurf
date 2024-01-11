#include "main.hpp"

// Author: Song Myung Kyu (2024.01.04 onwards)
// This is a simple raylib program that draws a hopefully realistic joint surfaces
// of a rock surface. The program is written in C++ and uses raylib as a library.

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

int main(int argc, char **argv)
{
    int scale = 1;
    if (argc == 2)
    {
        std::string fname = argv[1];
        if (std::filesystem::exists(fname))
        {
            std::cout << "File exists" << std::endl;
            std::ifstream fin(fname);
            Json::Value root;
            if (fin.fail())
            {
                std::cout << "File open failed" << std::endl;
                exit(1);
            }

            Json::CharReaderBuilder builder;
            builder["collectComments"] = true;
            JSONCPP_STRING errs;
            if (!parseFromStream(builder, fin, &root, &errs))
            {
                std::cout << errs << std::endl;
                return EXIT_FAILURE;
            }
            std::cout << std::format("root[key] is {}",root["key"].asString()) << std::endl;
            // return EXIT_SUCCESS;

            fin.close();
        }
        else
        {
            std::cout << "File does not exist" << std::endl;
            exit(1);
        }
    }
    else if (argc > 2 || argc < 2)
    {
        std::cout << std::format("Usage: {} [filename]", argv[0]) << std::endl;
        exit(1);
    }

    MkDouble mean(2);
    MkMatrix<double> covar(2, 2);

    mean(0) = 0.0;
    mean(1) = 0.0;

    covar(0, 0) = 0.1;
    covar(0, 1) = 0.0;
    covar(1, 0) = 0.0;
    covar(1, 1) = 0.1;

    MkSurf surf;
    surf.Init();
    surf.SetScale(scale);
    surf.SetAngle(0.0);
    surf.SetRange(-5.0, 5.0, -5.0, 5.0);
    // surf.SetNumIter(5000);
    // surf.SetAniso(1);
    // surf.GenSurf(_nd3);
    surf.SetNumIter(1000);
    surf.SetAniso(2);
    surf.GenSurf(_nd9);

    // Initialization of raylib
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Rock Surface");

    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.01f, 5.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};    // Camera looking at point
    camera.up = (Vector3){0.0f, 0.0f, 1.0f};        // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // Camera projection type
    Vector3 targetPosition = {0.0f, 0.0f, -0.5f};

    Texture2D texture = LoadTexture("../resources/space.png");
    Shader shader = LoadShader(TextFormat("../resources/shaders/glsl330/base.vs"), TextFormat("../resources/shaders/glsl330/base.fs"));
    Matrix trans = MatrixIdentity();
    Material material = LoadMaterialDefault();

    MkMesh mkmesh;
    mkmesh.Update(surf);
    Mesh &mesh = mkmesh.GetMesh();

    SetTargetFPS(15); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    { // Detect window close button or ESC key
      // Update
        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed('Z'))
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};

        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(BLACK);
            BeginMode3D(camera);
            {
                DrawMesh(mesh, material, trans); // ***
            }
            EndMode3D();
        }
        EndDrawing();
    }

    //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}