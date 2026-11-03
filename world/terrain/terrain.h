#ifndef TERRAIN_H
#define TERRAIN_H

#include "tileType.h"

class Terrain
{
public:
    void Generate();

    TileType GetTile(int x, int y) const;

private:
    TileType m_Tiles[32][32];
};

#endif