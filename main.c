#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "cjson/cJSON.h"
#include "utils/tileUtils.h"
#include "tileRenderer.h"

const int screenWidth = 720;
const int screenHeight = 460;

int main()
{
    grid fgGrid;
    char* jsonContents = readFileToString("test.json");

    jsonToGrid(fgGrid, "test.json");
    
    InitWindow(screenHeight, screenHeight, "wawawawa");

    const Texture2D groundTex = LoadTexture("assets/tile_ground.png");
    struct hashmap* textureMap;
    buildTextureMap();

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("texture rigolo", 190, 200, 20, LIGHTGRAY);
        DrawTexture(groundTex, screenWidth/2, screenHeight/2, WHITE);
        struct hashmap *textureMap = NULL;
        renderGrid(fgGrid);

        EndDrawing();
    }

    CloseWindow();
    printf("Hello !\n");
    return 0;
}

