#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "cjson/cJSON.h"
#include "utils/utils.h"
#include "utils/tileUtils.h"
#include "tileRenderer.h"

const int screenWidth = 720;
const int screenHeight = 460;

int main()
{
    grid fgGrid;
    initGrid(fgGrid);


    jsonToGrid(fgGrid, "test.json");
    
    InitWindow(screenHeight, screenHeight, "wawawawa");

    struct hashmap* textureMap = hashmap_new(sizeof(int), 0, 0, 0, int_hash, int_compare, NULL, NULL);

    buildTextureMap();

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("test textures", 190, 200, 20, LIGHTGRAY);
        renderGrid(fgGrid);

        EndDrawing();
    }
    hashmap_free(textureMap);
    CloseWindow();
    printf("Hello !\n");
    return 0;
}

