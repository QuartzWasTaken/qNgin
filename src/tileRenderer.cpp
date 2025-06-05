#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "tileUtils.h"
#include "raylib.h"
#include "Tilemap.h"

void renderTilemap(const Tilemap& t)
{
    const auto& listeTiles = t.getListe();  // read-only access to tiles
    for (size_t y = 0; y < listeTiles.size(); y++)
        for (size_t x = 0; x < listeTiles[y].size(); x++)
            DrawTexture(*listeTiles[y][x].getTexture(), x*16, y*16, WHITE);
}
