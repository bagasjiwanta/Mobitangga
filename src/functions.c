#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "./adt/mesinkata/mesinkata.h"
#include "./adt/map/map.h"
#include "./adt/array/array.h"
#include "functions.h"
#include "boolean.h"

// menuliskan error ke output, lalu force exit
void logErrorThenExit (const char* error, const char* location) {
    printf("Error pada %s:\n\t%s", location, error);
    exit(1);
};

void initGame () {
    char choice;
    boolean endOperation = false;
    printf("\nSelamat datang di Game Ular Tangga Doraemonangis !!\n\n");
    printf("Anda memiliki 2 pilihan untuk sekarang, New Game dan Exit\n");
    printf("Masukkan pilihan anda [n/e]:\n> ");

    // validasi input menggunakan while loop
    while(!endOperation) {
        scanf("%c", &choice);
        if (choice == 'n') {
            // deklarasi variabel
            FILE* file;
            char fileloc[25];
            char baseloc[75] = "./public/";

            // menerima input file konfigurasi untuk yang pertama kali
            printf("Masukkan nama file konfigurasi yang ingin di load (pastikan sudah ada di folder ./public/):\n> ");
            scanf("%s", &fileloc);
            strcat(baseloc, fileloc);

            // memastikan file exist sebelum di proses     
            while (!(file = fopen(baseloc, "r"))) {
                fclose(file);
                printf("Nama file tidak ditemukan\n");
                printf("Masukkan kembali nama file konfigurasi yang ingin di load (pastikan sudah ada di folder ./public/):\n> ");
                scanf("%s", &fileloc);
                strcpy(baseloc, "./public/");
                strcat(baseloc, fileloc);
            } 
            fclose(file);

            readConfig(baseloc);
            // mengambil input jumlah pemain
            int jumlahPemain;
            printf("Masukkan jumlah pemain (2-4):\n> ");
            scanf("%d", &jumlahPemain);

            // validasi input
            int tries = 3;
            while (jumlahPemain > 4 || jumlahPemain < 2) {
                printf("Jumlah pemain tidak valid, masukkan lagi :\n> ");
                scanf("%d", &jumlahPemain);
                tries --;
                if(tries == 0){
                    logErrorThenExit("\nJumlah pemain tidak valid", "initGame");
                }
            }

            int i;
            for (i = 0; i < jumlahPemain; i++){
                printf("Masukkan nama pemain ke-%d:\n> ", i+1);
                scanf("%s", &baseloc);
                printf("Telah dibuat pemain bernama %s\n", baseloc);
                // CreateEmptyPlayer(baseloc);
            }
            endOperation = true;
        } else if (choice == 'e') {
            // prosedur exit
            printf("~Good Bye~");
            exit(0);
        } else {
            // pesan untuk validasi
            printf("Command yang diterima hanya (N/n/E/e), ulangi lagi:\n> ");
        }
    }
};

void readConfig (const char* fileloc) {
    int N; // panjang map
    int M; // jumlah teleporter
    int MaxRoll; // maksimum roll dadu
    int src, dest; // petak masuk dan keluar teleporter
    int i, j; // iterator
    const char* errorloc = "file konfigurasi"; // keperluan error logging

    // mulai membaca file
    STARTKATA(fileloc);

    // validasi N
    N = atoi(CKata.TabKata);
    if(N < 2 || N > 100) {
        logErrorThenExit("Panjang peta harus diantara 2 dan 100", errorloc);
    } 

    allocMap(N);

    // input dan validasi mapConfig
    ADVKATA();
    if (CKata.Length != N) {
        logErrorThenExit("Panjang peta harus sesuai input sebelumnya", errorloc);
    }
    if (CKata.TabKata[0] == '#' || CKata.TabKata[CKata.Length - 1] == '#') {
        logErrorThenExit("Petak awal dan akhir tidak boleh dijadikan petak terlarang", errorloc);
    }
    i = 1;
    while(CKata.TabKata[i] == '#' || CKata.TabKata[i] == '.') {
        if(i==N-2){
            break;
        }
        i++;
    }
    if(i!=N-2){
        logErrorThenExit("Petak hanya boleh berisi karakter '#' atau '.'", errorloc);
    }
    strcpy((MAP->mapConfig), CKata.TabKata);

    // input dan validasi MaxRoll
    ADVKATA();
    MaxRoll = atoi(CKata.TabKata);
    if (MaxRoll < 1 || MaxRoll > N - 1){
        logErrorThenExit("MaxRoll harus diantara 1 dan N - 1", errorloc);
    }
    MAP->defaultMaxRoll = MaxRoll;

    // input dan validasi jumlah teleporter
    ADVKATA();
    M = atoi(CKata.TabKata);
    if (M < 1 || M > N - 2) {
        logErrorThenExit("Jumlah teleporter harus diantara 1 dan N - 2", errorloc);
    }

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