#include "utils/tileUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"
#include "utils/hashmap.h"
#include "raylib.h"

struct hashmap* textureMap = NULL; // Global ou dans un contexte accessible

void buildTextureMap()
{
    textureMap = hashmap_new(sizeof(textureMapEntry), 0, 0, 0, int_hash, int_compare, NULL, NULL);

    textureMapEntry entry = {
        .key = 1,
        .tex = LoadTexture("assets/tile_ground.png")
    };
    // Ajout autres textures
    hashmap_set(textureMap, &entry);

}

void renderGrid(grid g)
{
    for(int y = 0; y < MAX_MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAX_MAP_WIDTH; x++)
        {
            int lookupKey = g[y][x];

            textureMapEntry* found = hashmap_get(textureMap, &lookupKey);

            if(found)
            {
                DrawTexture(found->tex, x*16, y*16, WHITE);
            }
        }
    }
}