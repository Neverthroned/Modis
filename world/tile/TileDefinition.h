#ifndef TILEDEFINITION_H
#define TILEDEFINITION_H

#include "tileType.h"

struct TileDefinition
{
    TileType type;

    const char* name;
    
    bool solid;
    bool opaque;
    /* bool transparent;

    // Rendering
    int textureID;

    // Gameplay
    bool mineable;
    float hardness; */
};

#endif