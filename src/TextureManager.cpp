#include "TextureManager.h"
#include <iostream>
#include <cctype>

typedef std::unordered_map<std::string, int> t_tileTypeMap;

TextureManager::~TextureManager()
{
    for (auto& pair : textureMap)
    {
        UnloadTexture(pair.second);
    }
}

void TextureManager::loadTextures(const t_tileTypeMap& typeMap)
{

    for (const auto& [name, id] : typeMap)
    {
        std::string lowerName = name;
        for (char& c : lowerName)
        {
            c = std::tolower(static_cast<unsigned char>(c)); // what the hayyylll oh my gawd no wayyayyayyyy
        }
        
        std::string path = "assets/" + lowerName + ".png";
        Texture2D texture = LoadTexture(path.c_str());

        if (texture.id == 0)
        {
            std::cerr << "Erreur de chargement de la texture : " << path << std::endl;
            continue;
        }

        textureMap[id] = texture;
        texturePointerMap[id] = &textureMap[id];
    }
}

const Texture2D* TextureManager::getTexture(int type) const
{
    auto it = texturePointerMap.find(type);
    if (it != texturePointerMap.end())
    {
        return it->second;
    }

    return nullptr;
}

void TextureManager::unloadTextures()
{
    for (auto& [id, texture] : textureMap)
    {
        UnloadTexture(texture);
    }
    textureMap.clear();
    texturePointerMap.clear();
}