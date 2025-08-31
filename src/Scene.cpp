#include "raylib.h"
#include "TextureManager.h"
#include "Scene.h"

Scene::Scene(Camera2D& cam, TextureManager& texMan, Tilemap& tMap)
{
    camera = &cam;
    textureManager = &texMan;
    tilemap = &tMap;
}

TextureManager* Scene::getTextureManager()
{
    return textureManager;
}

Camera2D* Scene::getCamera()
{
    return camera;
}

Tilemap* Scene::getTilemap()
{
    return tilemap;
}
