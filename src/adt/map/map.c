#include "map.h"
#include "../array/array.h"
#include "../mesinkata/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>

Map* MAP;

void initMap(){
    MAP = (Map*) malloc (sizeof(Map));
}

void allocMap(int N){
    MAP->mapConfig.TI = (char*) malloc (sizeof(char) * N + 1);
    MAP->mapConfig.Neff = N;
    MAP->teleporters.TI = (int*) malloc (sizeof(int) * N + 1);
    MAP->teleporters.Neff = N;
    int x;
    for(x=0;x<=N;x++){
        MAP->teleporters.TI[x] = 0;
    }
}

void deallocMap(){
    free(MAP);
}

void displayMapForDebugging(){
    printf("\n----Menampilkan map----\nPanjang peta: %d\n", MAP->mapConfig.Neff);
    printf("Konfigurasi peta: %s\n", MAP->mapConfig.TI);
    printf("Default Max Roll: %d\n", MAP->defaultMaxRoll);
    printf("Isi teleporters:\n");
    int x;
    for(x=1;x<=(MAP->mapConfig.Neff);x++){
        printf("Petak masuk: %d, petak keluar: %d\n", x, MAP->teleporters.TI[x]);
    }
}

void readMap (const char* fileloc) {
    // Deklarasi variabel
    int N; // panjang map
    int M; // jumlah teleporter
    int MaxRoll; // maksimum roll dadu
    int src, dest; // petak masuk dan keluar teleporter
    int i, j; // iterator
    const char* errorloc = "file konfigurasi"; // keperluan error logging

    STARTKATA(fileloc);

    N = atoi(CKata.TabKata);
    allocMap(N);

    // input dan validasi panjang (tidak dijamin di spesifikasi)
    ADVKATA();
    if (CKata.Length != N) {
        logErrorThenExit("Panjang peta harus sesuai input sebelumnya", errorloc);
    }
    
    i = 1;
    // validasi semua isi dari mapconfig kecuali ujung (tidak dijamin di spesifikasi)
    while(CKata.TabKata[i] == '#' || CKata.TabKata[i] == '.') {
        if(i == N-2){
            break;
        }
        i++;
    }
    if(i != N - 2){
        logErrorThenExit("Petak hanya boleh berisi karakter '#' atau '.'", errorloc);
    }
    strcpy((MAP->mapConfig.TI), CKata.TabKata);

    // input MaxRoll
    ADVKATA();
    MaxRoll = atoi(CKata.TabKata);
    MAP->defaultMaxRoll = MaxRoll;

    // input jumlah teleporter
    ADVKATA();
    M = atoi(CKata.TabKata);

    // input dan validasi teleporters
    for (i = 0 ; i < M ; i ++) {
        ADVKATA();
        src = atoi(CKata.TabKata);
        if (i == M - 1) {
            MBR = true;
        }
        ADVKATA();
        dest = atoi(CKata.TabKata);
        if (src == dest) {
            logErrorThenExit("Petak masuk dan keluar teleporter tidak boleh sama", errorloc);
        }
        if (src < 1 || dest < 1 || src > N || dest > N) {
            logErrorThenExit("Teleporter harus berada dalam map", errorloc);
        }
        MAP->teleporters.TI[src] = dest;
    }
};