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

int main(void)
{
    // Initialization of general variables
    //--------------------------------------------------------------------------------------
    MkDouble mean(2);
    MkMatrix<double> covar(2, 2);

    mean(0) = 0.3;
    mean(1) = 0.3;

    covar(0, 0) = 0.1;
    covar(0, 1) = 0.0;
    covar(1, 0) = 0.0;
    covar(1, 1) = 0.1;

    gauss gaussDist;
    gaussDist.init(mean, covar);
    // gaussDist.test();
    double val;
    for (int i = -10; i <= 10; i++)
    {
        for (int j = -10; j <= 10; j++)
        {
            val = gaussDist.eval(i / 10.0, j / 10.0);
            std::printf("evaluation (%f,%f) is %f\n", i / 10.0, j / 10.0, val);
        }
    }

    surf surfData;

    surfData.fillup();
    surfData.test();

    mesh rs;
    rs(1, 1) = 1;
    rs(99, 99) = 99.0;
    rs.update(surfData);
    // rs.log();

    // // Initialization of raylib
    // //--------------------------------------------------------------------------------------
    // const int screenWidth = 800;
    // const int screenHeight = 450;
    // // mesh<double> rockSurface;

    // InitWindow(screenWidth, screenHeight, "Rock Surface");

    // SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    // //--------------------------------------------------------------------------------------

    // // Main game loop
    // while (!WindowShouldClose())
    // { // Detect window close button or ESC key
    //     // Update
    //     //----------------------------------------------------------------------------------
    //     BeginDrawing();

    //     ClearBackground(RAYWHITE);

    //     DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    //     EndDrawing();
    // }

    // //----------------------------------------------------------------------------------

    // // De-Initialization
    // //--------------------------------------------------------------------------------------
    // CloseWindow(); // Close window and OpenGL context
    // //--------------------------------------------------------------------------------------
    return 0;
}