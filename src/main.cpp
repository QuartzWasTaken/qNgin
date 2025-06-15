#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION

#include "cjson/cJSON.h"
#include "tileUtils.h"
#include "tileRenderer.h"
#include "raymath.h"
#include "Tile.h"
#include "Tilemap.h"
#include "TextureManager.h"
#include "raygui.h"
#include "SceneDebug.h"

/*
    TODO :

    Changement de tiles
    Joueur
    Tilesets
*/

// banque de textures, qu'on charge une fois au démarrage (itérer (unsafe ?))
// texture id = indice dans la banque/match dans la hashmap (plus flexible)

const int screenWidth = 1280;
const int screenHeight = 720;

double roundToNearest10(double x)
{
    return std::round(x / 10.0) * 10.0;
}

int main()
{
    std::cout << "------ Début Main ------" << std::endl;

    Tilemap fgGrid;

    std::cout << "------ jsonToGrid ------" << std::endl;
    jsonToGrid(fgGrid, "ecrituretest.json");

    TextureManager textureManager;
    std::cout << "------ Initialisation de la fenêtre... ------" << std::endl;
    InitWindow(screenWidth, screenHeight, "wawawawa");

    std::cout << "------ Chargement des textures... ------" << std::endl;

    textureManager.loadTextures(tileTypeMap);

    bindTextures(fgGrid, textureManager);

    SetTargetFPS(60);

    
    Camera2D camera = { 0 };
    
    SceneDebug dbg(camera, textureManager, fgGrid);

    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    while(!WindowShouldClose())
    {
        // Draw

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        dbg.Draw();

        BeginMode2D(camera);

        renderTilemap(fgGrid, textureManager);

        EndMode2D();

        dbg.DrawFixed();

        EndDrawing();
    }

    std::cout << "------ Sortie de la boucle de rendu ------" << std::endl;
    textureManager.unloadTextures();

    CloseWindow();
    printf("Hello !\n");
    return 0;
}