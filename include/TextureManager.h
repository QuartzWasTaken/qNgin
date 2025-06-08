#pragma once

#include <unordered_map>
#include <string>
#include <raylib.h>

class TextureManager
{
    private:

    std::unordered_map<int, Texture2D> textureMap;
    std::unordered_map<int, const Texture2D*> texturePointerMap;

    public:

    TextureManager() = default;
    ~TextureManager();

    void loadTextures(const std::unordered_map<std::string, int>& typeMap);
    void unloadTextures();
    const Texture2D* getTexture(int type) const;
};
