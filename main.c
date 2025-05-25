#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "cjson/cJSON.h"
#include "utils.h"

const int screenWidth = 720;
const int screenHeight = 460;

int main()
{
    grid fgGrid;
    char* jsonContents = read_file_to_string("test.json");

    jsonToGrid(fgGrid, "test.json");
    
    InitWindow(screenHeight, screenHeight, "wawawawa");

    const Texture2D groundTex = LoadTexture("assets/ground.png");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("texture rigolo", 190, 200, 20, LIGHTGRAY);
        DrawTexture(groundTex, screenWidth/2, screenHeight/2, WHITE);


        EndDrawing();
    }
    CloseWindow();
    printf("Hello !\n");
    return 0;
}