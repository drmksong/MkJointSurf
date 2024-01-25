#include "main.hpp"

// Author: Song Myung Kyu (2024.01.04 onwards)
// This is a simple raylib program that draws a hopefully realistic joint surfaces
// of a rock surface. The program is written in C++ and uses raylib as a library.

int main(int argc, char **argv)
{
    // double numiter[2] = {10000, 1000}, aniso[2] = {1, 4}, angle[2] = {0.0, 30};
    // int nd[2] = {1, 8};
    std::vector<double> numiter, aniso, angle;
    std::vector<int> nd;
    std::vector<std::normal_distribution<double>> vnd;
    vnd.push_back(_nd);
    vnd.push_back(_nd1);
    vnd.push_back(_nd2);
    vnd.push_back(_nd3);
    vnd.push_back(_nd4);
    vnd.push_back(_nd5);
    vnd.push_back(_nd6);
    vnd.push_back(_nd7);
    vnd.push_back(_nd8);
    vnd.push_back(_nd9);
    std::string fname = "";
    int batch_num = 0;
    float scale = 1;
    float size_x = 10.0, size_y = 10.0;
    int grid_x = 100, grid_y = 100;

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

            const Json::Value &data = root["data"];
            for (Json::Value::ArrayIndex i = 0; i < data.size(); i++)
            {
                numiter.push_back(data[i]["NumIter"].asDouble());
                aniso.push_back(data[i]["Aniso"].asDouble());
                nd.push_back(data[i]["ND"].asInt());
                angle.push_back(-data[i]["Angle"].asDouble());
            }
            const Json::Value &scale_ = root["Scale"];
            const Json::Value &imag = root["Image"];
            const Json::Value &batch = root["Batch"];
            const Json::Value &sizex = root["SizeX"]; // width
            const Json::Value &sizey = root["SizeY"]; // length
            const Json::Value &gridx = root["GridX"]; // number of  x grid points
            const Json::Value &gridy = root["GridY"]; // number of  y grid points

            scale = scale_.asFloat();
            fname = imag.asString();
            batch_num = batch.asInt();
            size_x = sizex.asFloat();
            size_y = sizey.asFloat();
            grid_x = gridx.asInt();
            grid_y = gridy.asInt();

            // std::cout << std::format("root[NumIter] is {}", root["NumIter"].asDouble()) << std::endl;
            // std::cout << std::format("root[Aniso] is {}", root["Aniso"].asDouble()) << std::endl;
            // std::cout << std::format("root[ND] is {}", root["ND"].asInt()) << std::endl;
            // std::cout << std::format("root[Angle] is {}", root["Angle"].asInt()) << std::endl;

            // numiter = root["NumIter"].asDouble();
            // aniso = root["Aniso"].asDouble();
            // nd = root["ND"].asInt();
            // angle = -root["Angle"].asDouble();
            // // return EXIT_SUCCESS;

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

    MkDouble mean(2), stdev(2);

    mean(0) = 0.0;
    mean(1) = 0.0;

    stdev(0) = 1.0;
    stdev(1) = 1.0;

    // Initialization of raylib
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Rock Surface");

    Camera3D camera = {0};
    camera.position = (Vector3){0.01f, 0.0f, 5.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};    // Camera looking at point
    camera.up = (Vector3){0.0f, 0.0f, 1.0f};        // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // Camera projection type
    Vector3 targetPosition = {0.0f, 0.0f, -0.5f};

    Texture2D texture = LoadTexture("../resources/space.png");
    Shader shader = LoadShader(TextFormat("../resources/shaders/glsl330/base.vs"), TextFormat("../resources/shaders/glsl330/base.fs"));
    Matrix trans = MatrixIdentity();
    Material material = LoadMaterialDefault();

    MkSurf surf;

    surf.Init();
    surf.SetRange(-size_x / 2.0, size_x / 2.0, -size_y / 2.0, size_y / 2.0);
    surf.SetGridSize(grid_x, grid_y);

    // test code with fixed parameters, to be deleted...
    // surf.SetRange(-10.0, 10.0, -10.0, 10.0);
    // surf.SetGridSize(200,200);
    // surf.SetNumIter(5000);
    // surf.SetAniso(1);
    // surf.GenSurf(_nd3);

    for (std::vector<double>::size_type i = 0; i < numiter.size(); i++)
    {
        std::cout << std::format("numiter[{}] is {} ", i, numiter[i]) << std::endl;
        std::cout << std::format("aniso[{}] is {} ", i, aniso[i]) << std::endl;
        std::cout << std::format("nd[{}] is {} ", i, nd[i]) << std::endl;
        std::cout << std::format("angle[{}] is {} ", i, -angle[i]) << std::endl;

        surf.SetNumIter(numiter[i]);
        surf.SetAniso(aniso[i]);
        surf.SetAngle(angle[i]);
        surf.GenSurf(vnd[nd[i]]);
    }
    surf.SetScale(scale);
    std::cout << std::format("scale is {}", scale) << std::endl;

    surf.Rescale();

    MkEvalJRC evalJRC;
    evalJRC.SetSurfData(surf);
    evalJRC.cal_theta_s();
    evalJRC.cal_theta_2s();
    evalJRC.cal_S_sT();

    // TODO: Checking for the area of a triangle is completed and the code below is to be deleted...soon
    MkPoint p1, p2, p3;
    p1.X = 0.0;
    p1.Y = 0.0;
    p1.Z = 0.0;
    p2.X = 1.0;
    p2.Y = 0.0;
    p2.Z = 1.0;
    p3.X = 0.0;
    p3.Y = 1.0;
    p3.Z = 1.0;
    MkTriangle t1(p1, p2, p3);

    MkVector<double> v1, v2, u;
    MkLine l1, l2;

    l1.SetLine(t1[0], t1[1]);
    l2.SetLine(t1[0], t1[2]);

    v1 = l1.GetVector() * l1.GetLength();
    v2 = l2.GetVector() * l2.GetLength();

    v1.Cross(v2, u); // u = v1 x v2
    double len = std::sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2]);
    std::cout << std::format("v1 is ({} {} {}), v2 is ({} {} {}), u is ({} {} {}), |u| is {} or {}", v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], u[0], u[1], u[2], u.GetLength(), len) << std::endl;

    double FArea3D = u.GetLength() / 2;
    std::cout << std::endl;
    std::cout << std::format("t1.GetArea() is {}, t1.GetArea3D() is {}", t1.GetArea2D(), t1.GetArea3D()) << std::endl
              << std::endl; // TODO: this is not correct, check MkTriangle::CalArea(), very very important

    float sum = surf.Analyze();
    std::cout << std::format("surface (positive - negative) is {:5}", sum) << std::endl;

    // surf.SetNumIter(numiter);
    // surf.SetAniso(aniso);
    // surf.SetAngle(angle);
    // surf.GenSurf(vnd[nd]);

    MkMesh mkmesh;
    mkmesh.Update(surf);
    Mesh &mesh = mkmesh.GetMesh();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    { // Detect window close button or ESC key
      // Update
        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed('Z'))
        {
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
            camera.position = (Vector3){0.01f, 0.0f, 5.0f}; // Camera position
            camera.up = (Vector3){0.0f, 0.0f, 1.0f};        // Camera up vector (rotation towards target)
        }
        if (IsKeyPressed('X'))
        {
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
            camera.position = (Vector3){5.01f, 0.0f, 0.0f}; // Camera position
            camera.up = (Vector3){0.0f, 0.0f, 1.0f};        // Camera up vector (rotation towards target)
        }
        if (IsKeyPressed('Y'))
        {
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
            camera.position = (Vector3){0.01f, 5.0f, 0.0f}; // Camera position
            camera.up = (Vector3){0.0f, 0.0f, 1.0f};        // Camera up vector (rotation towards target)
        }
        if (IsKeyPressed('C'))
        {
            TakeScreenshot(std::format("{}_{:03}.png", fname, batch_num).c_str());
        }
        if (IsKeyPressed('V'))
        {
            std::ofstream fout(std::format("{}_{:03}.dat", fname, batch_num));
            fout << surf;
            fout.close();
        }

        UpdateCameraPro(&camera,
                        (Vector3){
                            (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * 0.1f - // Move forward-backward
                                (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * 0.1f,
                            (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * 0.1f - // Move right-left
                                (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * 0.1f,
                            (IsKeyDown(KEY_R)) * 0.1f - (IsKeyDown(KEY_F)) * 0.1f // Move up-down
                        },
                        (Vector3){
                            GetMouseDelta().x * 0.05f, // Rotation: yaw
                            GetMouseDelta().y * 0.05f, // Rotation: pitch
                            0.0f                       // Rotation: roll
                        },
                        GetMouseWheelMove() * 2.0f);

        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                DrawMesh(mesh, material, trans);
            }
            EndMode3D();

            DrawFPS(10, 10);
            DrawText(TextFormat("surface (positive - negative) is %.3f", sum), 10, 40, 20, BLUE);
            DrawText("\'W\': forward, \'S\': backward, \'A\': left, \'D\': right ", 10, 60, 20, BLUE);
            DrawText("\'Z\': reset camera in z direction, \'X\': reset camera in x-direction, \'Y\': reset camera in y-direction, ", 10, 80, 20, BLUE);
            DrawText("\'R\': upward, \'F\': downward ", 10, 100, 20, BLUE);
            DrawText("\'C\': take screenshot, \'V\': save data, ", 10, 120, 20, BLUE);
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