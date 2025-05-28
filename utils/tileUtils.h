#pragma once

#include "raylib.h"

#define MAX_MAP_HEIGHT 10
#define MAX_MAP_WIDTH 10
#define CHUNK_WIDTH 8

typedef enum
{
    TILE_ERROR = -1,
    TILE_AIR = 0,
    TILE_GROUND = 1
} tileType;

typedef struct
{
    tileType type;
    short attributs;
} tile;

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

typedef tile grid[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

char* readFileToString(const char* filename);
int jsonToGrid(grid g, const char* s);

void initGrid(grid g);