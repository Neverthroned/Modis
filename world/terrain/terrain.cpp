#include <iostream>
#include "terrain.h"

void Terrain::Generate()
{
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 32; x++)
        {
            m_Tiles[y][x] = TileType::GRASS;
        }
    }

}

TileType Terrain::GetTile(int x, int y) const
{
    if (x < 0 || x >= 32 || y < 0 || y >= 32)
        return TileType::AIR;

    return m_Tiles[y][x];
}