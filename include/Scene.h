#pragma once
#include <string>

#include "TextureManager.h"
#include "Tilemap.h"

class Scene
{
private:

    std::string name;

    TextureManager* textureManager;
    Camera2D* camera;
    Tilemap* tilemap;

public:
    Scene(Camera2D& cam, TextureManager& texMan, Tilemap& tMap);

    Camera2D* getCamera();
    TextureManager* getTextureManager();
    Tilemap* getTilemap();

    virtual void Draw() = 0;
    virtual void DrawFixed() = 0;
};