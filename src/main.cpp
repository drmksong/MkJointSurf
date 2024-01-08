#include "main.hpp"

// Author: Song Myung Kyu (2024.01.04 onwards)
// This is a simple raylib program that draws a hopefully realistic joint surfaces
// of a rock surface. The program is written in C++ and uses raylib as a library.

void fillup(MkDouble &surfData)
{
    for (int i = 0; i < surfData.getSzX(); i++)
    {
        for (int j = 0; j < surfData.getSzY(); j++)
        {
            surfData(i, j) = i + j;
        }
    }
}

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

// Generate a simple triangle mesh from code
static Mesh genMeshTest(void)
{
    Mesh mesh = {0};
    mesh.triangleCount = 2;
    mesh.vertexCount = mesh.triangleCount * 3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));  // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float)); // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));   // 3 vertices, 3 coordinates each (x, y, z)
    mesh.colors = (unsigned char *)MemAlloc(mesh.vertexCount * 4 * sizeof(unsigned char));
    mesh.indices = (unsigned short *)malloc(mesh.triangleCount * 3 * sizeof(unsigned short));

    // Vertex at (0, 0, 0.5)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0.5;
    mesh.normals[0] = 0;
    mesh.normals[1] = 0;
    mesh.normals[2] = 1;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;
    mesh.colors[0] = 254;
    mesh.colors[1] = 254;
    mesh.colors[2] = 254;
    mesh.colors[3] = 254;

    // Vertex at (1, 2, 0)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 2;
    mesh.vertices[5] = 0.0;
    mesh.normals[3] = 0;
    mesh.normals[4] = 0;
    mesh.normals[5] = 1;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;
    mesh.colors[4] = 254;
    mesh.colors[5] = 0;
    mesh.colors[6] = 254;
    mesh.colors[7] = 254;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0.;
    mesh.normals[6] = 0;
    mesh.normals[7] = 0;
    mesh.normals[8] = 1;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] = 0;
    mesh.colors[8] = 254;
    mesh.colors[9] = 254;
    mesh.colors[10] = 0;
    mesh.colors[11] = 254;

    // // Vertex at (2, 0, 0)
    // mesh.vertices[9] = 2;
    // mesh.vertices[10] = 0;
    // mesh.vertices[11] = 0.;
    // mesh.normals[9] = 0;
    // mesh.normals[10] = 0;
    // mesh.normals[11] = 1;
    // mesh.texcoords[6] = 0;
    // mesh.texcoords[7] = 0;
    // mesh.colors[12] = 254;
    // mesh.colors[13] = 254;
    // mesh.colors[14] = 0;
    // mesh.colors[15] = 254;

    // // Vertex at (1, 2, 0)
    // mesh.vertices[12] = 1;
    // mesh.vertices[13] = 2;
    // mesh.vertices[14] = 0.;
    // mesh.normals[12] = 0;
    // mesh.normals[13] = 0;
    // mesh.normals[14] = 1;
    // mesh.texcoords[8] = 0.5f;
    // mesh.texcoords[9] = 1.0f;
    // mesh.colors[16] = 254;
    // mesh.colors[17] = 0;
    // mesh.colors[18] = 254;
    // mesh.colors[19] = 254;

    // // Vertex at (3, 2, 0.5)
    // mesh.vertices[15] = 3;
    // mesh.vertices[16] = 2;
    // mesh.vertices[17] = 0.5;
    // mesh.normals[15] = 0;
    // mesh.normals[16] = 0;
    // mesh.normals[17] = 1;
    // mesh.texcoords[10] = 1;
    // mesh.texcoords[11] = 0;
    // mesh.colors[20] = 254;
    // mesh.colors[21] = 254;
    // mesh.colors[22] = 254;
    // mesh.colors[23] = 254;

    mesh.vertices[9] = 3;
    mesh.vertices[10] = 2;
    mesh.vertices[11] = 0.5;
    mesh.normals[9] = 0;
    mesh.normals[10] = 0;
    mesh.normals[11] = 1;
    mesh.texcoords[6] = 1;
    mesh.texcoords[7] = 0;
    mesh.colors[12] = 254;
    mesh.colors[13] = 254;
    mesh.colors[14] = 254;
    mesh.colors[15] = 254;

    // mesh.indices[0] = 0;
    // mesh.indices[1] = 2;
    // mesh.indices[2] = 1;
    // mesh.indices[3] = 3;
    // mesh.indices[4] = 5;
    // mesh.indices[5] = 4;

    mesh.indices[0] = 0;
    mesh.indices[1] = 2;
    mesh.indices[2] = 1;
    mesh.indices[3] = 2;
    mesh.indices[4] = 3;
    mesh.indices[5] = 1;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}
static Mesh genmesh(surf &surf)
{
    Mesh mesh = {0};

    mesh.vertexCount = surf.getSurfData().getSzX() * surf.getSurfData().getSzY();
    mesh.triangleCount = (surf.getSurfData().getSzX() - 1) * (surf.getSurfData().getSzY() - 1) * 2;

    mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.colors = (unsigned char *)MemAlloc(mesh.vertexCount * 4 * sizeof(unsigned char));
    mesh.indices = (unsigned short *)MemAlloc(mesh.triangleCount * 3 * sizeof(unsigned short));

    int vCounter = 0;
    int tcCounter = 0;
    int nCounter = 0;
    int cCounter = 0;
    int iCounter = 0;

    int szX = surf.getSurfData().getSzX();
    int szY = surf.getSurfData().getSzY();
    double maxValue = -1e10, minValue = 1e10;

    for (int j = 0; j < szY; j++)
    {
        for (int i = 0; i < szX; i++)
        {
            maxValue = std::max(maxValue, surf(i, j));
            minValue = std::min(minValue, surf(i, j));
        }
    }

    for (int j = 0; j < surf.getSurfData().getSzY(); j++)
    // for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < surf.getSurfData().getSzX(); i++)
        // for (int i = 0; i < 2; i++)
        {
            mesh.vertices[vCounter] = (float)(i - 50) / 10.0f;
            mesh.vertices[vCounter + 1] = (float)(j - 50) / 10.0f;
            mesh.vertices[vCounter + 2] = (float)surf(i, j) / 100.0f + 1;
            if (j == 0)
                std::cout << std::format("i{:3},j{:3} : ({:3}({:3}), {:3}({:3}), {:3}({:3}) )", i, j, mesh.vertices[vCounter], vCounter, mesh.vertices[vCounter + 1], vCounter + 1, mesh.vertices[vCounter + 2], vCounter + 2) << std::endl;
            vCounter += 3;

            mesh.texcoords[tcCounter] = (float)i / 100.0f;
            mesh.texcoords[tcCounter + 1] = (float)j / 100.0f;
            tcCounter += 2;

            mesh.normals[nCounter] = 0.0f;
            mesh.normals[nCounter + 1] = 0.0f;
            mesh.normals[nCounter + 2] = 1.0f;
            nCounter += 3;

            mesh.colors[cCounter + 0] = int((surf(i, j) - minValue) / (maxValue - minValue) * 255);
            mesh.colors[cCounter + 1] = 125;
            mesh.colors[cCounter + 2] = int((maxValue - surf(i, j)) / (maxValue - minValue) * 255);
            mesh.colors[cCounter + 3] = 255;
            cCounter += 4;
        }
    }
    for (int j = 0; j < surf.getSurfData().getSzY() - 1; j++)
        // for (int j = 0; j <  50; j++)
        for (int i = 0; i < surf.getSurfData().getSzX() - 1; i++)
        // for (int i = 0; i < 1; i++)
        {
            {
                mesh.indices[iCounter] = (i)*surf.getSurfData().getSzY() + (j);
                mesh.indices[iCounter + 2] = (i + 1) * surf.getSurfData().getSzY() + (j);
                mesh.indices[iCounter + 1] = (i)*surf.getSurfData().getSzY() + (j + 1);
                // if (i == 0)
                //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, mesh.indices[iCounter], mesh.indices[iCounter + 1], mesh.indices[iCounter + 2]) << std::endl;
                mesh.indices[iCounter + 3] = (i + 1) * surf.getSurfData().getSzY() + (j);
                mesh.indices[iCounter + 5] = (i + 1) * surf.getSurfData().getSzY() + (j + 1);
                mesh.indices[iCounter + 4] = (i)*surf.getSurfData().getSzY() + (j + 1);
                // if (i == 0)
                //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, mesh.indices[iCounter + 3], mesh.indices[iCounter + 4], mesh.indices[iCounter + 5]) << std::endl;
            }
            iCounter += 6;
        }

    // for (int i = 0; i < surf.getSurfData().getSzX() - 1; i++)
    // {
    //     for (int j = 0; j < surf.getSurfData().getSzY() - 1; j++)
    //     {
    //         mesh.indices[iCounter] = (i)*surf.getSurfData().getSzY() + (j);
    //         mesh.indices[iCounter + 1] = (i + 1) * surf.getSurfData().getSzY() + (j + 1);
    //         mesh.indices[iCounter + 2] = (i)*surf.getSurfData().getSzY() + (j + 1);
    //         // if (i == 0)
    //         //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, mesh.indices[iCounter], mesh.indices[iCounter + 1], mesh.indices[iCounter + 2]) << std::endl;
    //         mesh.indices[iCounter + 3] = (i)*surf.getSurfData().getSzY() + (j);
    //         mesh.indices[iCounter + 4] = (i + 1) * surf.getSurfData().getSzY() + (j);
    //         mesh.indices[iCounter + 5] = (i + 1) * surf.getSurfData().getSzY() + (j + 1);
    //         // if (i == 0)
    //         //     std::cout << std::format("{:3}, {:3} : ({:3}, {:3}, {:3} )", i, j, mesh.indices[iCounter + 3], mesh.indices[iCounter + 4], mesh.indices[iCounter + 5]) << std::endl;
    //     }
    //     iCounter += 6;
    // }

    UploadMesh(&mesh, false);

    return mesh;
}

int main(void)
{
    // Initialization of general variables
    //--------------------------------------------------------------------------------------
    MkDouble mean(2);
    MkMatrix<double> covar(2, 2);

    mean(0) = 0.0;
    mean(1) = 0.0;

    covar(0, 0) = 0.1;
    covar(0, 1) = 0.0;
    covar(1, 0) = 0.0;
    covar(1, 1) = 0.1;

    // test code block for gauss::eval
    // gauss gaussDist;
    // gaussDist.init(mean, covar);

    // double val, sval;
    // for (int i = -10; i <= 10; i++)
    // {
    //     for (int j = -10; j <= 10; j++)
    //     {
    //         val = gaussDist.eval(i / 10.0, j / 10.0);
    //         sval = gaussDist.seval(i / 10.0, j / 10.0);
    //         std::printf("evaluation and scaled evaluation at (%f,%f) are %f and %f repectively.\n", i / 10.0, j / 10.0, val, sval);
    //     }
    // }
    // test code block ends

    int scale = 1;
    surf surfData;
    surfData.init();
    // surfData.init(mean, covar);
    surfData.setRange(-5.0, 5.0, -5.0, 5.0);
    surfData.setScale(scale);

    // test code block for surf::bang
    // covar(0, 0) = 0.2;
    // covar(0, 1) = 0.0;
    // covar(1, 0) = 0.0;
    // covar(1, 1) = 1.0;
    // surfData.setGauss(mean, covar);
    // surfData.bang(0.0, 0.0);

    // covar(0, 0) = 1.1;
    // covar(0, 1) = 0.0;
    // covar(1, 0) = 0.0;
    // covar(1, 1) = 0.2;
    // surfData.setGauss(mean, covar);
    // surfData.bang(3.0, 3.0);

    // covar(0, 0) = 1.1;
    // covar(0, 1) = 0.0;
    // covar(1, 0) = 0.0;
    // covar(1, 1) = 1.2;
    // surfData.setGauss(mean, covar);
    // surfData.bang(1.5, 1.5);
    // test code block ends

    // actual code block for surf::bang
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> nd(0, 1);
    std::normal_distribution<double> nd_05(0, 0.01);
    std::normal_distribution<double> nd1(0, 0.1);
    std::normal_distribution<double> nd2(0, 0.2);
    std::normal_distribution<double> nd3(0, 0.3);
    std::normal_distribution<double> nd4(0, 0.4);
    std::normal_distribution<double> nd5(0, 0.5);
    std::normal_distribution<double> nd6(0, 0.6);
    std::normal_distribution<double> nd7(0, 0.7);
    std::normal_distribution<double> nd8(0, 0.8);
    std::normal_distribution<double> nd9(0, 0.9);

    std::uniform_real_distribution<double> nd_bx(12);
    std::uniform_real_distribution<double> nd_by(12);

    // test code block for randon number generation
    // std::map<int, int> hist{};
    // for (int n = 0; n < 10000; ++n)
    // {
    //     ++hist[std::round(nd(gen))];
    // }
    // for (auto p : hist)
    // {
    //     std::cout << std::setw(2) << p.first << ' '
    //               << std::string(p.second / 100, '*') << " " << p.second << '\n';
    // }
    // test code block ends
    for (int cnt = 0; cnt < 10000 / scale; cnt++)
    {
        // std::cout << std::format("nd_cov(gen) = {:2}", std::abs(nd_cov(gen))) << std::endl;
        // std::cout << std::format("nd_bx(gen) = {:2}", nd_bx(gen)-5) << std::endl;
        // std::cout << std::format("nd_by(gen) = {:2}", nd_by(gen)-5) << std::endl;

        if (cnt % 100 == 0)
            // std::cout << std::format("\rcnt = {:5}%", cnt / 100) << std::flush;
            std::cout << std::format("\rcnt = {:5}%:", cnt / 100) << std::string(cnt / 100, '.') << std::flush;

        covar(1, 1) = covar(0, 0) = std::max(std::abs(nd1(gen)), 0.01);
        covar(1, 1) = 1 * covar(0, 0);
        // covar(1, 1) = std::max(std::abs(nd1(gen)), 0.01);
        surfData.setGauss(mean, covar);
        if (nd(gen) > 0)
            surfData.bang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
        else
            surfData.rbang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    }

    for (int cnt = 0; cnt < 1000 / scale; cnt++)
    {
        // std::cout << std::format("nd_cov(gen) = {:2}", std::abs(nd_cov(gen))) << std::endl;
        // std::cout << std::format("nd_bx(gen) = {:2}", nd_bx(gen)-5) << std::endl;
        // std::cout << std::format("nd_by(gen) = {:2}", nd_by(gen)-5) << std::endl;

        if (cnt % 100 == 0)
            // std::cout << std::format("\rcnt = {:5}%", cnt / 100) << std::flush;
            std::cout << std::format("\rcnt = {:5}%:", cnt / 10) << std::string(cnt / 10, '.') << std::flush;

        covar(1, 1) = covar(0, 0) = std::max(std::abs(nd1(gen)), 0.01);
        covar(1, 1) = 20 * covar(0, 0);
        // covar(1, 1) = std::max(std::abs(nd5(gen)), 0.01);
        surfData.setGauss(mean, covar);
        if (nd(gen) > 0)
            surfData.bang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
        else
            surfData.rbang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    }

    std::cout << std::endl;

    // for (int cnt = 0; cnt < 100 / scale; cnt++)
    // {
    //     covar(0, 0) = std::max(std::abs(nd8(gen)), 0.01);
    //     covar(1, 1) = std::max(std::abs(nd8(gen)), 0.01);
    //     surfData.setGauss(mean, covar);
    //     if (nd(gen) > 0)
    //         surfData.bang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    //     else
    //         surfData.rbang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    // }

    // for (int cnt = 0; cnt < 100 / scale; cnt++)
    // {
    //     covar(0, 0) = std::max(std::abs(nd7(gen)), 0.01);
    //     covar(1, 1) = std::max(std::abs(nd7(gen)), 0.01);
    //     surfData.setGauss(mean, covar);
    //     if (nd(gen) > 0)
    //         surfData.bang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    //     else
    //         surfData.rbang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    // }

    // for (int cnt = 0; cnt < 100 / scale; cnt++)
    // {
    //     covar(0, 0) = std::max(std::abs(nd6(gen)), 0.01);
    //     covar(1, 1) = std::max(std::abs(nd6(gen)), 0.01);
    //     surfData.setGauss(mean, covar);
    //     if (nd(gen) > 0)
    //         surfData.bang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    //     else
    //         surfData.rbang(std::round(10 * nd_bx(gen)) / 10.0 - 6, std::round(10 * nd_by(gen)) / 10.0 - 6);
    // }

    // surfData.out();

    // mesh rs;
    // rs(1, 1) = 1;
    // rs(99, 99) = 99.0;
    // rs.update(surfData);
    // // rs.log();

    // Initialization of raylib
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    // mesh<double> rockSurface;

    InitWindow(screenWidth, screenHeight, "Rock Surface");

    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.01f, 5.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};    // Camera looking at point
    camera.up = (Vector3){0.0f, 0.0f, 1.0f};        // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // Camera projection type
    Vector3 targetPosition = {0.0f, 0.0f, -0.5f};

    Mesh mesh, mesh2;
    mesh = genmesh(surfData);
    // mesh2 = genMeshTest();

    Texture2D texture = LoadTexture("../resources/space.png");
    Shader shader = LoadShader(TextFormat("../resources/shaders/glsl330/base.vs"), TextFormat("../resources/shaders/glsl330/base.fs"));
    Matrix trans = MatrixIdentity();
    Material material = LoadMaterialDefault();

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

        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawMesh(mesh, material, trans); // ***
        // DrawMesh(mesh2, material, trans); // ***

        // for (int i = 0; i < surfData.getSurfData().getSzX() - 1; i++)
        // {
        //     for (int j = 0; j < surfData.getSurfData().getSzY() - 1; j++)
        //     {
        //         // std::cout << std::format("({:3}, {:3} )", screenWidth * float(i) / 100.0f, screenWidth * float(i + 1) / 100.0f) << std::endl;
        //         // DrawTriangle3D((Vector3){screenWidth * float(i) / 100.0f, screenWidth * float(j) / 100.0f, (float)surfData(i, j)},
        //         //                (Vector3){screenWidth * float(i) / 100.0f, screenWidth * float(j + 1) / 100.0f, (float)surfData(i, j + 1)},
        //         //                (Vector3){screenWidth * float(i + 1) / 100.0f, screenWidth * float(j) / 100.0f, (float)surfData(i + 1, j)}, WHITE);
        //         // DrawTriangle3D((Vector3){screenWidth * float(i) / 100.0f, screenWidth * float(j + 1) / 100.0f, (float)surfData(i, j + 1)},
        //         //                (Vector3){screenWidth * float(i + 1) / 100.0f, screenWidth * float(j + 1) / 100.0f, (float)surfData(i + 1, j + 1)},
        //         //                (Vector3){screenWidth * float(i + 1) / 100.0f, screenWidth * float(j) / 100.0f, (float)surfData(i + 1, j)}, YELLOW);
        //         DrawTriangle3D((Vector3){float(i) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j)},
        //                        (Vector3){float(i + 1) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j)},
        //                        (Vector3){float(i) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j + 1)}, YELLOW);
        //         DrawTriangle3D((Vector3){float(i + 1) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j)},
        //                        (Vector3){float(i + 1) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j + 1)},
        //                        (Vector3){float(i) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j + 1)}, YELLOW);
        //         DrawLine3D((Vector3){float(i) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j)},
        //                    (Vector3){float(i + 1) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j)}, BLACK);
        //         DrawLine3D((Vector3){float(i + 1) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j)},
        //                    (Vector3){float(i) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j + 1)}, BLACK);
        //         DrawLine3D((Vector3){float(i) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j + 1)},
        //                    (Vector3){float(i) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j)}, BLACK);
        //         DrawLine3D((Vector3){float(i + 1) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j)},
        //                    (Vector3){float(i + 1) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j + 1)}, BLACK);
        //         DrawLine3D((Vector3){float(i + 1) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j + 1)},
        //                    (Vector3){float(i) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j + 1)}, BLACK);
        //         DrawLine3D((Vector3){float(i) / 10.0f - 5.0f, float(j + 1) / 10.0f - 5.0f, 0.01f * (float)surfData(i, j + 1)},
        //                    (Vector3){float(i + 1) / 10.0f - 5.0f, float(j) / 10.0f - 5.0f, 0.01f * (float)surfData(i + 1, j)}, BLACK);
        //     }
        //     // std::cout << std::endl;
        // }

        // DrawCube(targetPosition, 2.0f, 2.0f, -0.5f, RED);
        // DrawCubeWires(targetPosition, 2.0f, 2.0f, -0.5f, MAROON);
        // DrawGrid(5, 2.0f);

        EndMode3D();

        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        // // Triangle shapes and lines
        // DrawTriangle((Vector2){screenWidth / 4.0f * 4.0f, 80.0f},
        //              (Vector2){screenWidth / 4.0f * 4.0f - 60.0f, 150.0f},
        //              (Vector2){screenWidth / 4.0f * 4.0f + 60.0f, 150.0f}, VIOLET);

        EndDrawing();
    }

    //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}