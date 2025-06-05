#pragma once

#include <stdio.h>
#include <raylib.h>
#include <ostream>

class Tile
{
    private:

    int type;
    const Texture2D* texture;

    public:

    Tile();
    Tile(int t);

    int getType() const;
    void setType(int t);

    const Texture2D* getTexture() const;
    void setTexture(const Texture2D* tex);

    bool operator==(const Tile& other) const;
    bool operator==(int t) const;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);
