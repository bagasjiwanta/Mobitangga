#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "./adt/mesinkata/mesinkata.h"

void logErrorThenExit (const char* error, const char* location) {
    printf("Error pada %s:\n\t%s", location, error);
    exit(1);
}

void readConfig (int* mapLength, char* mapConfig, int* defaultMaxRoll, int* teleporters) {
    int N, M, MaxRoll, src, dest;
    Kata map;
    STARTKATA();
    N = atoi(CKata.TabKata);
    if(N < 2 || N > 100) {
        logErrorThenExit("Panjang peta harus diantara 2 dan 100", "konfigurasi.txt");
    } 
    *mapLength = N;

    ADVKATA();
    if (CKata.Length != N) {
        logErrorThenExit("Panjang peta harus sesuai input sebelumnya", "konfigurasi.txt");
    }
    if (CKata.TabKata[0] == '#' || CKata.TabKata[CKata.Length - 1] == '#') {
        logErrorThenExit("Petak awal dan akhir tidak boleh dijadikan petak terlarang", "konfigurasi.txt");
    }
    strcpy(mapConfig, CKata.TabKata);

    ADVKATA();
    MaxRoll = atoi(CKata.TabKata);
    if (MaxRoll < 1 || MaxRoll > N - 1){
        logErrorThenExit("MaxRoll harus diantara 1 dan N - 1", "konfigurasi.txt");
    }
    *defaultMaxRoll = MaxRoll;

    ADVKATA();
    M = atoi(CKata.TabKata);
    if (M < 1 || M > N - 2) {
        logErrorThenExit("Jumlah teleporter harus diantara 1 dan N - 2", "konfigurasi.txt");
    }
    // array teleportersnya belom jadi
    
    int i, j;
    for (i = 0 ; i < M ; i ++) {
        ADVKATA();
        src = atoi(CKata.TabKata);
        if (i == M - 1) {
            MBR = true;
        }
        ADVKATA();
        dest = atoi(CKata.TabKata);
        if (src == dest) {
            logErrorThenExit("Petak masuk dan keluar teleporter tidak boleh sama", "konfigurasi.txt");
        }
        if (src < 1 || dest < 1 || src > N || dest > N) {
            logErrorThenExit("Teleporter harus berada dalam map", "konfigurasi.txt");
        }
    }

    printf("Berhasil membaca tanpa error :)");
}