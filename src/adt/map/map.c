#include "boolean.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

void printMap(Map map) {
    printf("%s", map.mapConfig);
}

/* Konstruktor, membuat map baru.
I.S. map berisi sembarang value (garbage)
F.S. panjang peta terisi, bentuk peta dialokasi, nilai efektif
teleporter diset, dan lokasi semua player diset di petak 1*/
void CreateMap(Map *map, int mapLength, int NumOfTeleporters){
    int x;
    map->mapLength = mapLength;
    map->mapConfig = (char*) malloc (sizeof(char) * mapLength + 1);
    map->teleporters.Neff = NumOfTeleporters*2;
    for (x=0;x<4;x++) {
        map->playerLocations[x] = 1;
    }
};