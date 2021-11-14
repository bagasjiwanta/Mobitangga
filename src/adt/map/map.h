#ifndef __MAP_H__
#define __MAP_H__

#include "../array/array.h"

// Definisi Map
// Map berisi panjang peta, konfigurasi peta, 
// array of teleporters, dan default max roll
// Indeks genap pada teleporters menandakan petak masuk teleporter
// sedangkan index ganjil menandakan petak keluar teleporter
typedef struct MapStruct {
    int mapLength;
    char* mapConfig;
    TabInt teleporters;
    int defaultMaxRoll;
} Map;

extern Map* MAP;

// Konstruktor Map
// Mengalokasikan memori sebesar ukuran Map lalu direturn
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

#endif // !__MAP_H__