#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "tileUtils.h"
#include "raylib.h"
#include "Tilemap.h"
#include "TextureManager.h"
#include "consts.h"

void renderTilemap(const Tilemap& t, TextureManager& texManager)
{
    const auto& listeTiles = t.getListe();
    for (size_t y = 0; y < listeTiles.size(); y++)
    {
        for (size_t x = 0; x < listeTiles[y].size(); x++)
        {
            const Texture2D* tex = listeTiles[y][x].getTexture();

            if (tex == nullptr || tex->id == 0)
            {
                // pas de texture valide, on saute ou on affiche un message
                std::cerr << "Texture invalide à la position (" << x << "," << y << ")" << std::endl;
                continue;
            }
            else
            {
                DrawTexture(*tex, x * TILE_SIZE, y * TILE_SIZE, Color{255, 255, 255, 255});
            }
        }
    }
}
