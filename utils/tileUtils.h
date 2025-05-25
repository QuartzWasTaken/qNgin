#pragma once

#include "raylib.h"

#define MAX_MAP_HEIGHT 10
#define MAX_MAP_WIDTH 10

typedef enum
{
    TILE_ERROR = -1,
    TILE_AIR = 0,
    TILE_GROUND = 1
} tileType;

typedef struct
{
    tileType type;
    const char* name;
} tileTypeMapping;

typedef struct
{
    int key;
    Texture2D tex;
} textureMapEntry;

tileType stringToTileType(const char* str);
const char* tileTypeToString(tileType type);

typedef tileType grid[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

char* readFileToString(const char* filename);
int jsonToGrid(grid g, const char* s);

void initGrid(grid g);