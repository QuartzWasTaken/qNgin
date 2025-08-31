#pragma once

#include "Scene.h"
#include "raylib.h"
#include "consts.h"

class SceneDebug : public Scene
{
private:
    int paintType = 2;
    Rectangle UIRect();

public:
    SceneDebug(Camera2D& camera, TextureManager& texManager, Tilemap& tMap);
    void setPaintType(int i);
    int getPaintType();
    void Draw();
    void DrawFixed();
    void DrawPaintGUI();
};