#ifndef TILETYPE_H
#define TILETYPE_H

#include <cstdint>

enum class TileType : std::uint16_t
{
    AIR = 0,
    DIRT = 1,
    GRASS = 2
};

#endif