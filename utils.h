#pragma once

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

tileType tile_type_from_string(const char* str);
const char* tile_type_to_string(tileType type);

typedef tileType grid[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

char* read_file_to_string(const char* filename);
int jsonToGrid(grid g, const char* s);