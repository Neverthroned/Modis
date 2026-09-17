#ifndef TERRAIN_H
#define TERRAIN_H

#include "tile.h"

class Terrain
{
public:
    void Generate();

    Tile &GetTile(int x, int y);

private:
    Tile m_Tiles[32][32];
};

#endif