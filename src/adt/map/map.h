#ifndef __MAP_H__
#define __MAP_H__

#include "../array/array.h"

// Definisi Map
// Map berisi panjang peta, konfigurasi peta, 
// array of teleporters, dan default max roll
typedef struct MapStruct {
    int mapLength;
    char* mapConfig;
    TabInt teleporters;
    int defaultMaxRoll;
} Map;

// Konstruktor Map
// Mengalokasikan memori sebesar ukuran Map lalu direturn
Map* CreateEmptyMap();

// Konstruktor properti map : mapConfig
// Mengalokasikan memori sebesar panjang peta + 1 lalu di return
char* AllocMapConfig(int n);

// Konstruktor properti map : teleporters
// Mengalokasikan memori sebesar jumlah petak masuk + petak keluar
// Yaitu sebesar 2 * m
int* AllocTeleporters(int m);

// Destruktor
// Melakukan dealokasi terhadap map yang sudah dialokasi
void DeallocMap(Map* map);
#endif // !__MAP_H__