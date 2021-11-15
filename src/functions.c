#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "./adt/map/map.h"
#include "functions.h"
#include "boolean.h"

// menuliskan error ke output, lalu force exit
void logErrorThenExit (const char* error, const char* location) {
    printf("Error pada %s:\n\t%s", location, error);
    exit(1);
};

void initGame () {
    initMap();
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
            scanf("%s", fileloc);
            strcat(baseloc, fileloc);

            // memastikan file exist sebelum di proses     
            while (!(file = fopen(baseloc, "r"))) {
                fclose(file);
                printf("Nama file tidak ditemukan\n");
                printf("Masukkan kembali nama file konfigurasi yang ingin di load (pastikan sudah ada di folder ./public/):\n> ");
                scanf("%s", fileloc);
                strcpy(baseloc, "./public/");
                strcat(baseloc, fileloc);
            } 
            fclose(file);

            readMap(baseloc);
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
                scanf("%s", baseloc);
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