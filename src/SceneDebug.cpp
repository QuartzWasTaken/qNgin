#include <string>
#include <iostream>
#include "SceneDebug.h"
#include "TextureManager.h"
#include <raylib.h>
#include "raymath.h"
#include "tileUtils.h"
#include "Scene.h"
#include "raygui.h"
#include "consts.h"

const int cameraMovementSpeed = 10;
bool canDraw = true;

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

    int mouseGridX = static_cast<int>(mouseWorldPos.x) / TILE_SIZE; // Nombres magiques mais c'est du debug donc blc
    int mouseGridY = static_cast<int>(mouseWorldPos.y) / TILE_SIZE;
    
    if(GuiButton((Rectangle){WINDOW_WIDTH - 120 - PADDING_LEFT_RIGHT, WINDOW_HEIGHT - 30 - PADDING_TOP_BOTTOM, 120, 30}, "#2#Save"))
    {
        std::string strGrid = gridToJson(*fgGrid);
    
        writeStringToFile(strGrid, "ecrituretest.json");
        canDraw = false;
        return;
    }

    if(!canDraw == IsMouseButtonReleased(0))
    {
        canDraw = true;
    }

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

    if(IsMouseButtonDown(0) &&
    canDraw &&
    (mouseGridX) < MAX_MAP_WIDTH &&
    (mouseGridY) < MAX_MAP_HEIGHT &&
    (mouseGridX) >= 0 &&
    (mouseGridY) >= 0)
    {
        fgGrid->getListe()[mouseGridY][mouseGridX].setType(paintType); 
        fgGrid->getListe()[mouseGridY][mouseGridX].setTexture(textureManager->getTexture(paintType));
    }

    if(IsMouseButtonDown(1) &&
    canDraw &&
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

    cameraGridX = camera->target.x / TILE_SIZE;
    cameraGridY = camera->target.y / TILE_SIZE;

    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);

    int mouseGridX = static_cast<int>(mouseWorldPos.x) / TILE_SIZE;
    int mouseGridY = static_cast<int>(mouseWorldPos.y) / TILE_SIZE;

    DrawText(TextFormat("MousePos : %d %d", mouseX, mouseY), 0, WINDOW_WIDTH - 130, 20, LIGHTGRAY);
    DrawText(TextFormat("MouseGridPos : %d %d", mouseGridX, mouseGridY), 0, WINDOW_WIDTH - 100, 20, LIGHTGRAY);
    DrawText(TextFormat("CameraGridPos : %d %d", cameraGridX, cameraGridY), 0, WINDOW_WIDTH - 70, 20, LIGHTGRAY);
    DrawText(TextFormat("CamPos : %.0f %.0f", camera->target.x, camera->target.y), 0, WINDOW_WIDTH - 30, 20, LIGHTGRAY);
    DrawText("PLAYING", 0, WINDOW_WIDTH, 10, LIGHTGRAY);

    DrawPaintGUI();
}

void SceneDebug::setPaintType(int i)
{
    paintType = i;
}

int SceneDebug::getPaintType()
{
    return paintType;
}

void SceneDebug::DrawPaintGUI()
{
    if(GuiButton((Rectangle){WINDOW_WIDTH, WINDOW_HEIGHT - 50, 50, 50}, "#2#GRASS"))
    {

    }
}