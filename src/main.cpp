#include "main.hpp"

// Author: Song Myung Kyu (2024.01.04 onwards)
// This is a simple raylib program that draws a hopefully realistic joint surfaces
// of a rock surface. The program is written in C++ and uses raylib as a library.

void fillup(MkArray<double> &surfData)
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
    MkArray<double> surfData(100, 100);
    mesh rs;

    fillup(surfData);
    rs(1, 1) = 1;
    rs(99, 99) = 99.0;
    rs.update(surfData);
    rs.log();

    // Initialization of raylib
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    // mesh<double> rockSurface;

    InitWindow(screenWidth, screenHeight, "Rock Surface");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}