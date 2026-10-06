#include <iostream>
#include "tileRegistry.h"

namespace 
{
    const TileDefinition definitions[] =
    {
        { TileType::AIR, "Air", false, false },
        { TileType::DIRT, "Dirt", true, true },
        { TileType::GRASS, "Grass", true, true}
    };
}

void TileRegistry::Initialize()
{

}

const TileDefinition& TileRegistry::get(TileType type)
{
    return definitions[static_cast<int>(type)];
}