#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"
#include "Tilemap.h"

#define MAX_MAP_HEIGHT 10
#define MAX_MAP_WIDTH 10

// hashmap str int se lie avec
// hahsmap int tex pour donner le couple str-tex

typedef std::unordered_map<std::string, int> t_tileTypeMap;
typedef std::unordered_map<int, Texture2D> t_textureMap;

extern t_tileTypeMap tileTypeMap;

extern t_textureMap textureMap;

void buildTextureMap(t_textureMap* texMap, t_tileTypeMap typeMap);
void bindTextures(Tilemap& tilemap, const t_textureMap& texMap);

std::string readFileToString(const std::string& filename);
int jsonToGrid(Tilemap t, const char* s);