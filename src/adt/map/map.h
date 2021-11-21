#ifndef __MAP_H__
#define __MAP_H__

#include "../array/array.h"

// Definisi Map
// Map berisi mapConfig : konfigurasi peta;
// teleporters : array of teleporter, dan
// defaultMaxRoll : max roll yang default.
typedef struct MapStruct {
    TabChar mapConfig;
    TabInt teleporters;
    int defaultMaxRoll;
} Map;

extern Map* MAP;

// Konstruktor Map
// Mengalokasikan memori sebesar ukuran Map
void initMap();

// Inisialisasi Map
// panjang peta di set N, lalu dialokasikan mapConfig
// dan teleporters
void allocMap(int N);

// Destruktor
// Melakukan dealokasi terhadap map yang sudah dialokasi
void deallocMap();

// Menampilkan semua isi map untuk keperluan debugging
void displayMapForDebugging();

// membaca file konfigurasi
void readMap (const char* fileloc);

#endif // !__MAP_H__