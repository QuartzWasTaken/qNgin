#include <string>
#include <iostream>
#include "SceneDebug.h"
#include "TextureManager.h"
#include <raylib.h>
#include "raymath.h"
#include "tileUtils.h"
#include "Scene.h"
#include "raygui.h"

const int cameraMovementSpeed = 10;
const int screenWidth = 1280;
const int screenHeight = 720;

SceneDebug::SceneDebug(Camera2D& cam, TextureManager& texMan, Tilemap& tMap) : Scene::Scene(cam, texMan, tMap)
{

}

void SceneDebug::Draw()
{
    TextureManager* textureManager = getTextureManager();
    Camera2D* camera = getCamera();
    Tilemap* fgGrid = getTilemap();
    
    Vector2 movementVector = Vector2Zero();

    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);

    int mouseGridX = static_cast<int>(mouseWorldPos.x) / 16;
    int mouseGridY = static_cast<int>(mouseWorldPos.y) / 16;

    if(IsKeyDown(KEY_SPACE))
    {
        for(size_t y = 0; y < fgGrid->getListe().size(); y++)
        {
            for(size_t x = 0; x < fgGrid->getListe().size(); x++)
            {
                fgGrid->getListe()[y][x].setType(0); 
                fgGrid->getListe()[y][x].setTexture(textureManager->getTexture(0));
            }
        }
    }

    if(IsMouseButtonDown(0) && !IsKeyDown(KEY_A) &&
    (mouseGridX) < MAX_MAP_WIDTH &&
    (mouseGridY) < MAX_MAP_HEIGHT &&
    (mouseGridX) >= 0 &&
    (mouseGridY) >= 0)
    {
        fgGrid->getListe()[mouseGridY][mouseGridX].setType(1); 
        fgGrid->getListe()[mouseGridY][mouseGridX].setTexture(textureManager->getTexture(1));
    }

    if(IsMouseButtonDown(1) &&
    (mouseGridX) < MAX_MAP_WIDTH &&
    (mouseGridY) < MAX_MAP_HEIGHT &&
    (mouseGridX) >= 0 &&
    (mouseGridY) >= 0)
    {
        fgGrid->getListe()[mouseGridY][mouseGridX].setType(0); 
        fgGrid->getListe()[mouseGridY][mouseGridX].setTexture(textureManager->getTexture(0));
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

    camera->target = Vector2Add(camera->target, Vector2Scale(Vector2Normalize(movementVector), (float)cameraMovementSpeed));

    movementVector = Vector2Zero();

    if(GuiButton((Rectangle){screenWidth - 140, screenHeight - 50, 120, 30}, "#191#Test !"))
    {
        std::string strGrid = gridToJson(*fgGrid);
        std::cout << gridToJson(*fgGrid) << std::endl;

        writeStringToFile(strGrid, "ecrituretest.json");
    }
}

void SceneDebug::DrawFixed()
{
    int mouseX;
    int mouseY;

    int cameraGridX;
    int cameraGridY;
    
    Camera2D* camera = getCamera();

    mouseX = GetMouseX();
    mouseY = GetMouseY();

    cameraGridX = camera->target.x / 16;
    cameraGridY = camera->target.y / 16;

    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);

    int mouseGridX = static_cast<int>(mouseWorldPos.x) / 16;
    int mouseGridY = static_cast<int>(mouseWorldPos.y) / 16;

    DrawText(TextFormat("MousePos : %d %d", mouseX, mouseY), 0, screenHeight - 130, 20, LIGHTGRAY);
    DrawText(TextFormat("MouseGridPos : %d %d", mouseGridX, mouseGridY), 0, screenHeight - 100, 20, LIGHTGRAY);
    DrawText(TextFormat("CameraGridPos : %d %d", cameraGridX, cameraGridY), 0, screenHeight - 70, 20, LIGHTGRAY);
    DrawText(TextFormat("CamPos : %.0f %.0f", camera->target.x, camera->target.y), 0, screenHeight - 30, 20, LIGHTGRAY);
    DrawText("PLAYING", 0, screenHeight - 0, 10, LIGHTGRAY);
}