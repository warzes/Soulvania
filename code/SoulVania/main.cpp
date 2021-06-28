#include "stdafx.h"
#include <raylib/raylib.h>

#if _WIN32
// Prefer the high-performance GPU on switchable GPU systems
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#pragma comment( lib, "winmm.lib" )
#endif

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); 

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello World!", 190, 200, 20, RED);

        EndDrawing();
    }
    CloseWindow();
}