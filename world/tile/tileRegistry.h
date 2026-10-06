#ifndef TILEREGISTRY
#define TILEREGISTRY

#include "tileDefinition.h"
#include "tileType.h"

class TileRegistry
{
    public:
    static void Initialize();
    static const TileDefinition& get(TileType type);
    
};


#endif