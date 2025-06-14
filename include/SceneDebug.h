#pragma once

#include "Scene.h"

class SceneDebug : public Scene
{
//TODO: Finir ce système une bonne fois : passer une réference de cam ?
public:
    SceneDebug(Camera2D& camera, TextureManager& texManager, Tilemap& tMap);
    void Draw();
    void DrawFixed();
};