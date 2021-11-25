#include "./adt/player/player.h"
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "./adt/map/map.h"
#include "functions.h"
#include "boolean.h"
#include <time.h>

const char* Commands[] = {
    "SKILL",
    "MAP",
    "BUFF",
    "INSPECT", 
    "ROLL",
    "ENDTURN",
    "UNDO"
};

// mengembalikan random number dari 0 sampai maxDigit (inclusive)
int randInt(int maxDigit){
    return rand() % maxDigit;
};

// menuliskan error ke output, lalu force exit
void logErrorThenExit (const char* error, const char* location) {
    printf("Error pada %s:\n\t%s", location, error);
    exit(1);
};

void initGame () {
    time_t myTime;
    srand((unsigned) time(&myTime));
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
            for (i = 1; i <= jumlahPemain; i++){
                printf("Masukkan nama pemain ke-%d (maksimal 20 karakter): ", i);
                getchar();
                scanf("%[^\n]", baseloc);
                while(strlen(baseloc) > 20){
                    printf("Masukkan kembali nama pemain ke-%d (maksimal 20 karakter): ", i);
                    getchar();
                    scanf("%[^\n]", baseloc);
                }
                CreatePlayer(baseloc, i);
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

void commandMap(){
    char* temp = (char*) malloc (sizeof(char) * MAP->mapConfig.Neff + 2);
    strcpy(temp, MAP->mapConfig.TI);
    int i, x;
    for(i=1;i<=PLAYERS.NEff;i++){
        x = playerNo(i).position;
        temp[x] = '*';
        printf("%s\t\t: %s\n", playerNo(i).name, temp+1);
        temp[x] = MAP->mapConfig.TI[x];
    }
    free(temp);
};

void useSkill(int playerIndex, int skillIndex){
    printf("grat\n");
};

void commandSkill(int playerIndex){ 
    boolean counter[] = {0, 0, 0, 0, 0};
    int availables[] = {-1, -1, -1, -1, -1};
    boolean isGonnaUse = false;
    int i, j;
    address p;
    p = playerNo(playerIndex).skill.First;
    while(p != Nil){
        counter[p->info - 1] = true;
        p = p->next;
    }
    j = 1;
    printf("Kamu memiliki skill: \n");
    for(i=0;i<5;i++){
        if(counter[i] != 0){
            printf("  %d. %s\n", j, SkillNames[i]);
            availables[j-1] = i;
            j++;
        }
    }
    for(i=0;i<5;i++){
        printf("(%d)", availables[i]);
    }
    printf("\nTekan 0 untuk keluar. Masukkan bilangan negatif untuk membuang skill."
    "\n\nMasukkan skill: ");
    scanf("%d", &j);
    while(j < -7 && j > 7){
        printf("Masukkan skill kembali: ");
        scanf("%d", &j);
    }
    if(j == 0){
        printf("Berhasil keluar hehe\n");
        return;
    } else {
        isGonnaUse = j > 0;
        j = abs(j);
        if(availables[j-1] == -1){
            printf("Anda tidak memiliki skill ini\n");
            return;
        } else {
            printf("%s ", playerNo(playerIndex).name);
            if(isGonnaUse){ printf("memakai"); } else { printf("membuang"); }
            printf(" skill %s.\n", SkillNames[availables[j-1]]);
            if(isGonnaUse){
                useSkill(playerIndex, j);
            }
            DelP(&(playerNo(playerIndex).skill), availables[j-1] + 1);
        }
    }
};

void commandInspect(){
    int at;
    printf("Masukkan petak: ");
    scanf("%d", &at);
    if(MAP->mapConfig.TI[at] == '#'){
        printf("Petak %d merupakan petak terlarang", at);
    } else if (MAP->teleporters.TI[at] != 0) {
        printf("Petak %d memiliki teleporter menuju %d", at, MAP->teleporters.TI[at]);
    } else {
        printf("Petak %d merupakan petak kosong", at);
    }
};

void commandRoll(int playerIndex){
    int diceResult = randInt(MAP->defaultMaxRoll) + 1;
    boolean canForward = false;
    boolean canBackward = false;
    if (playerNo(playerIndex).buffs[2]) {
        diceResult = (diceResult + (MAP->defaultMaxRoll / 2)) % MAP->defaultMaxRoll;
    } else if (playerNo(playerIndex).buffs[3]) {
        diceResult = diceResult % ((MAP->defaultMaxRoll / 2) + 1);
    }
    printf("%d\n", diceResult);
};

void endGame(){
    1+1;
    return;
};

void gameLoop(){
    initGame();
    int playerIndex = 1;
    boolean isWinnerExist = false;
    boolean isCommandValid = true;
    boolean isTurnEnd = false;
    char inputCommand[15];
    
    while(!isWinnerExist){ // ronde
        giveAllPlayersRandomSkill();
        while(!isTurnEnd){ // commands
            do {
                printf("Masukkan command: ");
                scanf("%8s", inputCommand);
                if (!strcmp(inputCommand, Commands[0])) {
                    commandSkill(playerIndex);
                } else if (!strcmp(inputCommand, Commands[1])) {
                    commandMap();
                } else if (!strcmp(inputCommand, Commands[3])) {
                    commandInspect();
                } else if (!strcmp(inputCommand, Commands[4])) {
                    commandRoll(playerIndex);
                } else if (!strcmp(inputCommand, Commands[5])) {
                    isTurnEnd = true;
                } else {
                    isCommandValid = false;
                }
            } while (!isCommandValid); // validasi input
        }
    }
    endGame();
}