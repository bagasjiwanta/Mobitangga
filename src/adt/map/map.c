#include "map.h"
#include "../array/array.h"
#include <stdio.h>
#include <stdlib.h>

Map* MAP;

void initMap(){
    MAP = (Map*) malloc (sizeof(Map));
}

void allocMap(int N){
    MAP->mapLength = N;
    MAP->mapConfig = (char*) malloc (sizeof(char) * N + 1);
    MAP->teleporters.TI = (int*) malloc (sizeof(int) * N + 1);
    MAP->teleporters.Neff = N + 1;
    int x;
    for(x=0;x<=N;x++){
        MAP->teleporters.TI[x] = 0;
    }
}

void deallocMap(){
    free(MAP);
}

void displayMapForDebugging(){
    printf("\n----Menampilkan map----\nPanjang peta: %d\n", MAP->mapLength);
    printf("Konfigurasi peta: %s\n", MAP->mapConfig);
    printf("Default Max Roll: %d\n", MAP->defaultMaxRoll);
    printf("Isi teleporters:\n");
    int x;
    for(x=1;x<=(MAP->mapLength);x++){
        printf("Petak masuk: %d, petak keluar: %d\n", x, MAP->teleporters.TI[x]);
    }
}