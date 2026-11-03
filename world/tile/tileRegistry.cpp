#include <iterator>
#include "tileRegistry.h"

namespace 
{
    const TileDefinition definitions[] =
    {
        { TileType::AIR, "Air", false, false, 0 },
        { TileType::DIRT, "Dirt", true, true, 2 },
        { TileType::GRASS, "Grass", true, true, 3 }
    };

    const TileDefinition MissingDefinition =
    {
        TileType::GRASS, "Missing", true, true, 1 
    };
}




const TileDefinition& TileRegistry::get(TileType type)
{
    const auto index = static_cast<std::size_t>(type);

    if (index >= std::size(definitions))
        return MissingDefinition;

    return definitions[index];
}