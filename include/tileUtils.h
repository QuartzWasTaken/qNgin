#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"
#include "Tilemap.h"
#include "TextureManager.h"

#define MAX_MAP_HEIGHT 50
#define MAX_MAP_WIDTH 50

// hashmap str int se lie avec
// hahsmap int tex pour donner le couple str-tex

typedef std::unordered_map<std::string, int> t_tileTypeMap;
typedef std::unordered_map<int, const Texture2D> t_textureMap;

extern t_tileTypeMap tileTypeMap;

extern t_textureMap textureMap;

void loadTextures(std::unordered_map<int, Texture2D>& textureStorage, const t_tileTypeMap& typeMap);
void bindTextures(Tilemap& tilemap, const TextureManager& texManager);

std::string readFileToString(const std::string& filename);
int writeStringToFile(std::string input, const std::string& filename);
int jsonToGrid(Tilemap& t, const char* s);
std::string gridToJson(Tilemap t);