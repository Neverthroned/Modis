#ifndef TILEREGISTRY
#define TILEREGISTRY

#include "tileDefinition.h"
#include "tileType.h"

class TileRegistry
{
    public:
    static const TileDefinition& get(TileType type);
};


#endif