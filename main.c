#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "cjson/cJSON.h"
#include "utils/utils.h"
#include "utils/tileUtils.h"
#include "tileRenderer.h"
#include "raymath.h"

const int screenWidth = 720;
const int screenHeight = 460;
const int cameraMovementSpeed = 10;
int main()
{
    grid fgGrid;
    initGrid(fgGrid);

    jsonToGrid(fgGrid, "test.json");
    
    InitWindow(screenHeight, screenHeight, "wawawawa");

    struct hashmap* textureMap = hashmap_new(sizeof(int), 0, 0, 0, int_hash, int_compare, NULL, NULL);

    buildTextureMap();

    SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    int mouseX;
    int mouseY;

    int mouseGridX;
    int mouseGridY;

    while(!WindowShouldClose())
    {
        Vector2 movementVector = Vector2Zero();

        mouseX = GetMouseX();
        mouseY = GetMouseY();

        mouseGridX = mouseX / 16;
        mouseGridY = mouseY / 16;

        if(IsMouseButtonDown(0))
        {
            fgGrid[mouseGridY][mouseGridX] = TILE_GROUND;
        }

        // Update
        if(IsKeyDown(KEY_S))
        {
            movementVector = Vector2Subtract(movementVector, (Vector2){0, 10});
        }

        if(IsKeyDown(KEY_W))
        {
            movementVector = Vector2Add(movementVector, (Vector2){0, 10});
        }

        if(IsKeyDown(KEY_A))
        {
            movementVector = Vector2Add(movementVector, (Vector2){10, 0});
        }

        if(IsKeyDown(KEY_D))
        {
            movementVector = Vector2Subtract(movementVector, (Vector2){10, 0});
        }

        camera.target = Vector2Add(camera.target, Vector2Scale(Vector2Normalize(movementVector), (float)cameraMovementSpeed));

        movementVector = Vector2Zero();
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("test textures", 190, 200, 10, LIGHTGRAY);
        DrawText(TextFormat("CamPos : %.0f %.0f", camera.target.x, camera.target.y), 0, 30, 20, LIGHTGRAY);
        DrawText("PLAYING", 0, 0, 10, LIGHTGRAY);
        DrawText(TextFormat("MousePos : %d %d", mouseX, mouseY), 0, 130, 20, LIGHTGRAY);
        DrawText(TextFormat("MouseGridPos : %d %d", mouseGridX, mouseGridY), 0, 100, 20, LIGHTGRAY);

        BeginMode2D(camera);

        renderGrid(fgGrid);

        EndMode2D();
        


        EndDrawing();
    }
    hashmap_free(textureMap);
    CloseWindow();
    printf("Hello !\n");
    return 0;
}

