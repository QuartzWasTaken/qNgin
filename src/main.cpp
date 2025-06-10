#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "raylib.h"
#include "cjson/cJSON.h"
#include "tileUtils.h"
#include "tileRenderer.h"
#include "raymath.h"
#include "Tile.h"
#include "Tilemap.h"
#include "TextureManager.h"

// banque de textures, qu'on charge une fois au démarrage (itérer (unsafe ?))
// texture id = indice dans la banque/match dans la hashmap (plus flexible)


const int screenWidth = 720;
const int screenHeight = 460;
const int cameraMovementSpeed = 10;

int main()
{
    std::cout << "------ Début Main ------" << std::endl;

    Tilemap fgGrid;

    std::cout << "------ jsonToGrid ------" << std::endl;
    jsonToGrid(fgGrid, "test.json");

    TextureManager textureManager;
    std::cout << "------ Initialisation de la fenêtre... ------" << std::endl;
    InitWindow(screenHeight, screenHeight, "wawawawa");

    std::cout << "------ Chargement des textures... ------" << std::endl;


    textureManager.loadTextures(tileTypeMap);

    bindTextures(fgGrid, textureManager);

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

        if(IsMouseButtonDown(0) && mouseGridX < MAX_MAP_WIDTH && mouseGridY < MAX_MAP_HEIGHT)
        {
            fgGrid.getListe()[mouseGridY][mouseGridX].setType(1);
            fgGrid.getListe()[mouseGridY][mouseGridX].setTexture(textureManager.getTexture(1));
            std::cout << "Changé le type de la tile " << mouseGridX << ";" << mouseGridY << " vers 1" << std::endl;
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
        BeginMode2D(camera);

        renderTilemap(fgGrid, textureManager);

        EndMode2D();

        DrawText(TextFormat("CamPos : %.0f %.0f", camera.target.x, camera.target.y), 0, 30, 20, LIGHTGRAY);
        DrawText("PLAYING", 0, 0, 10, LIGHTGRAY);
        DrawText(TextFormat("MousePos : %d %d", mouseX, mouseY), 0, 130, 20, LIGHTGRAY);
        DrawText(TextFormat("MouseGridPos : %d %d", mouseGridX, mouseGridY), 0, 100, 20, LIGHTGRAY);

        EndDrawing();
    }
    std::cout << "------ Sortie de la boucle de rendu ------" << std::endl;
    textureManager.unloadTextures();
    CloseWindow();
    printf("Hello !\n");
    return 0;
}

