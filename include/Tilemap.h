#pragma once

#include <vector>
#include "Tile.h"

class Tilemap
{
    private:
    std::vector<std::vector<Tile>> liste;

    public:
    Tilemap();

    const std::vector<std::vector<Tile>>& getListe() const;
    std::vector<std::vector<Tile>>& getListe();
};