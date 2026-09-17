#ifndef TILE_H
#define TILE_H

#include "tileType.h"

class Tile
{
public:
    Tile();
    Tile(TileType type);

    TileType GetType() const;
    void SetType(TileType type);

private:
    TileType m_Type;

};

#endif