#ifndef __MAP_H__
#define __MAP_H__

#include "../array/array.h"

typedef struct MapStruct {
    int mapLength;
    char* mapConfig;
    TabInt teleporters;
    int playerLocations[4];
} Map;

void CreateMap(Map *map, int mapLength, int NumOfTeleporters);
#endif // !__MAP_H__