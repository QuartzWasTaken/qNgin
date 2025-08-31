#include <vector>
#include <iostream>
#include "Tile.h"
#include "tileUtils.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
    liste = std::vector<std::vector<Tile>>(MAX_MAP_HEIGHT, std::vector<Tile>(MAX_MAP_WIDTH, Tile(0))); // initialiser avec que des zeros
}

const std::vector<std::vector<Tile>>& Tilemap::getListe() const { return liste; }
std::vector<std::vector<Tile>>& Tilemap::getListe()  { return liste; }
