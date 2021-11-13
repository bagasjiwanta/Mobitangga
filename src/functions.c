#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "./adt/mesinkata/mesinkata.h"
#include "functions.h"

void logErrorThenExit (const char* error, const char* location) {
    printf("Error pada %s:\n\t%s", location, error);
    exit(1);
};

void initGame (int* mapLength, char* mapConfig, int* defaultMaxRoll, int* teleporters) {
    char choice;

    // print header
    printf(
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣴⣶⣶⣶⣶⣶⠶⣶⣤⣤⣀\n"
    "⠀⠀⠀⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⠁⠀⢀⠈⢿⢀⣀⠀⠹⣿⣿⣿⣦⣄\n" 
    "⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⠿⠀⠀⣟⡇⢘⣾⣽⠀⠀⡏⠉⠙⢛⣿⣷⡖\n" 
    "⠀⠀⠀⠀⠀⣾⣿⣿⡿⠿⠷⠶⠤⠙⠒⠀⠒⢻⣿⣿⡷⠋⠀⠴⠞⠋⠁⢙⣿⣄\n" 
    "⠀⠀⠀⠀⢸⣿⣿⣯⣤⣤⣤⣤⣤⡄⠀⠀⠀⠀⠉⢹⡄⠀⠀⠀⠛⠛⠋⠉⠹⡇\n" 
    "⠀⠀⠀⠀⢸⣿⣿⠀⠀⠀⣀⣠⣤⣤⣤⣤⣤⣤⣤⣼⣇⣀⣀⣀⣛⣛⣒⣲⢾⡷\n" 
    "⢀⠤⠒⠒⢼⣿⣿⠶⠞⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⣼⠃\n" 
    "⢮⠀⠀⠀⠀⣿⣿⣆⠀⠀⠻⣿⡿⠛⠉⠉⠁⠀⠉⠉⠛⠿⣿⣿⠟⠁⠀⣼⠃\n" 
    "⠈⠓⠶⣶⣾⣿⣿⣿⣧⡀⠀⠈⠒⢤⣀⣀⡀⠀⠀⣀⣀⡠⠚⠁⠀⢀⡼⠃\n" 
    "⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣷⣤⣤⣤⣤⣭⣭⣭⣭⣭⣥⣤⣤⣤⣴⣟⠁\n"
    );
    printf("Selamat datang di Game Ular Tangga Doraemonangis !!\n");
    printf("Anda memiliki 2 pilihan untuk sekarang, New Game dan Exit\n");
    printf("Masukkan pilihan anda [n/e]:\n");

    // validasi input menggunakan while loop
    while(1) {
        scanf("%c", &choice);
        if (choice == 'n') {
            // deklarasi variabel
            FILE* file;
            char fileloc[25];
            char baseloc[75] = "./public/";

            // menerima input file konfigurasi untuk yang pertama kali
            printf("Masukkan nama file konfigurasi yang ingin di load (pastikan sudah ada di folder ./public/):\n");
            scanf("%s", &fileloc);
            strcat(baseloc, fileloc);

            // memastikan file exist sebelum di proses     
            while (!(file = fopen(baseloc, "r"))) {
                fclose(file);
                printf("Masukkan nama file konfigurasi yang ingin di load (pastikan sudah ada di folder ./public/):\n");
                scanf("%s", &fileloc);
                strcpy(baseloc, "./public/");
                strcat(baseloc, fileloc);
            } 
            fclose(file);

            readConfig(mapLength, mapConfig, defaultMaxRoll, teleporters, baseloc);
            // mengambil input jumlah pemain
            int jumlahPemain;
            printf("Masukkan jumlah pemain (2-4):\n");
            scanf("%d", &jumlahPemain);

            // validasi input
            while (jumlahPemain > 4 || jumlahPemain < 2) {
                printf("Jumlah pemain tidak valid, masukkan lagi :\n");
                scanf("%d", &jumlahPemain);
            }

            int i;
            for (i = 0; i < jumlahPemain; i++){
                printf("Masukkan nama pemain ke-%d:\n", i);
                scanf("%s", &baseloc);
                printf("Telah dibuat pemain bernama %s\n", baseloc);
                // CreateEmptyPlayer(baseloc);
            }
        } else if (choice == 'e') {
            // prosedur exit
            printf("~Good Bye~");
            exit(0);
        } else {
            // pesan untuk validasi
            printf("Command yang diterima hanya (N/n/E/e), ulangi lagi:\n");
        }
    }
};

void readConfig (int* mapLength, char* mapConfig, int* defaultMaxRoll, int* teleporters, const char* fileloc) {
    int N, M, MaxRoll, src, dest;
    Kata map;
    STARTKATA(fileloc);
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
    for(;;){break;}
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
        // masukin src dan dest ke array
    }
    printf("Berhasil membaca tanpa error :)");
};