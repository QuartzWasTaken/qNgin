#include <raylib.h>
#include <ostream>
#include <iostream>
#include "Tile.h"


Tile::Tile()
{
    type = 0;
}

Tile::Tile(int t)
{
    type = t;
}

const Texture2D* Tile::getTexture() const { return texture; }
int Tile::getType() const { return type; }

void Tile::setTexture(const Texture2D* tex) { if(tex == nullptr) { std::cout << "Essai d'assignation de tex Nullptr !" << std::endl; } texture = tex; }
void Tile::setType(int t) { type = t; }

bool Tile::operator==(const Tile& other) const
{
    return(type == other.type); // deja un pointer : pas de ->
}

bool Tile::operator==(int t) const
{
    return(type == t);
}

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
    os << tile.getType();
    return os;
}