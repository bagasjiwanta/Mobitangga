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

 int whoseTurn = 1;
 boolean isTurnEnd = false;

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

void resetBuff () {
    int i, j;
    for(i = 1;i <= PLAYERS.NEff; i++){
        for (j = 1; j < 4; j++) {
            pNo(i).buffs[j] = false;
        }
    }
}

void commandMap(){
    char* temp = (char*) malloc (sizeof(char) * MAP->mapConfig.Neff + 2);
    strcpy(temp, MAP->mapConfig.TI);
    int i, x;
    for(i=1;i<=PLAYERS.NEff;i++){
        x = pNo(i).position;
        temp[x] = '*';
        printf("%s\t\t: %s\n", pNo(i).name, temp+1);
        temp[x] = MAP->mapConfig.TI[x];
    }
    free(temp);
};

void useSkill(int playerIndex, int skillIndex){
    if(skillIndex == 1){
        pNo(playerIndex).buffs[0] = true;
        printf("Buff imunitas teleport dinyalakan.\n");
    }
};

void commandSkill(int pIndex){ 
    int counter[] = {0, 0, 0, 0, 0};
    int availables[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    boolean isGonnaUse = false;
    int i, j, k;
    address p;
    p = pNo(pIndex).skill.First;
    while(p != Nil){
        counter[p->info - 1] ++;
        p = p->next;
    }
    j = 1;
    printf("Kamu memiliki skill: \n");
    for(i=0;i<5;i++){
        for(k=counter[i];k>0;k--){
            printf("  %d. %s\n", j, SkillNames[i]);
            availables[j-1] = i;
            j++;
        }
    }
    printf("\nTekan 0 untuk keluar. Masukkan bilangan negatif untuk membuang skill."
    "\n\nMasukkan skill: ");
    scanf("%d", &k);
    while(k < -10 && k > 10){
        printf("Masukkan skill kembali: ");
        scanf("%d", &k);
    }
    if(k == 0){
        printf("Berhasil keluar hehe\n");
        return;
    } else {
        isGonnaUse = k > 0;
        k = abs(k);
        if(availables[k-1] == -1){
            printf("Anda tidak memiliki skill ini\n");
            return;
        } else {
            printf("%s ", pNo(pIndex).name);
            if(isGonnaUse){ printf("memakai"); } else { printf("membuang"); }
            printf(" skill %s.\n", SkillNames[availables[k-1]]);
            if(isGonnaUse){
                useSkill(pIndex, k);
            }
            DelP(&(pNo(pIndex).skill), availables[k-1] + 1);
        }
    }
};

void commandInspect(){
    int at;
    printf("Masukkan petak: ");
    scanf("%d", &at);
    if(MAP->mapConfig.TI[at] == '#'){
        printf("Petak %d merupakan petak terlarang.\n", at);
    } else if (MAP->teleporters.TI[at] != 0) {
        printf("Petak %d memiliki teleporter menuju %d.\n", at, MAP->teleporters.TI[at]);
    } else {
        printf("Petak %d merupakan petak kosong.\n", at);
    }
};

void commandRoll(int pIndex){
    int diceResult = randInt(MAP->defaultMaxRoll) + 1;
    int currentPost = pNo(pIndex).position;
    boolean canForward = false;
    boolean canBackward = false;

    if (pNo(pIndex).buffs[2]) { // senter pembesar hoki
        diceResult = (diceResult + (MAP->defaultMaxRoll / 2)) % MAP->defaultMaxRoll;
    } else if (pNo(pIndex).buffs[3]) { // senter pengecil hoki
        diceResult = diceResult % ((MAP->defaultMaxRoll / 2) + 1);
    }
    printf("dice: %d\n", diceResult);

    canForward = isPetakValid(diceResult + currentPost);
    canBackward = isPetakValid(currentPost - diceResult);

    // testcases
    int choice;
    int toWhere = 0;
    printf("cb: %d, cf: %d\n", canBackward, canForward);
    if(canBackward && canForward){
        printf("%s dapat maju dan mundur.", pNo(pIndex).name);
        printf("Ke mana %s mau bergerak:\n", pNo(pIndex).name);
        printf("1. %d\n", currentPost - diceResult);
        printf("2. %d\n", currentPost + diceResult);
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        choice = (choice % 3);
        if(choice==0){choice++;}
        if(choice==1){
            toWhere = currentPost - diceResult;
            printf("%s mundur %d langkah.\n", pNo(pIndex).name, diceResult);
        } else {
            toWhere = currentPost + diceResult;
            printf("%s maju %d langkah.\n", pNo(pIndex).name, diceResult);
        }
    } else if (canBackward) {
        printf("%s dapat mundur.\n", pNo(pIndex).name);
        printf("%s mundur %d langkah.\n", pNo(pIndex).name, diceResult);
        toWhere = currentPost - diceResult;
    } else if (canForward) {
        printf("%s dapat maju.\n", pNo(pIndex).name);
        printf("%s maju %d langkah.\n", pNo(pIndex).name, diceResult);
        toWhere = currentPost + diceResult;
    } else {
        printf("%s tidak dapat bergerak.\n", pNo(pIndex).name);
    }
    // printf("Masuk kesini kah\n");
    movePlayer(pIndex, toWhere);
};

void movePlayer(int pIndex, int toWhere) {
    int teleporterExit;
    char teleportChoice;
    if(toWhere == 0){
        return;
    }
    pNo(pIndex).position = toWhere;
    printf("%s berada di petak %d.\n", pNo(pIndex).name, toWhere);
    teleporterExit = checkTeleporter(toWhere);
    
    if(teleporterExit != 0){
        printf("%s menemukan teleporter.\n", pNo(pIndex).name);
        if(pNo(pIndex).buffs[0]){
            printf("%s memiliki imunitas teleporter.\n", pNo(pIndex).name);
            printf("Apakah %s ingin teleport (Y/N)? ", pNo(pIndex).name);
            scanf("%c", &teleportChoice);
            if(teleportChoice != 'Y' || teleportChoice != 'N'){teleportChoice = 'Y';}
            if(teleportChoice == 'N'){
                printf("%s tidak teleport.\n", pNo(pIndex).name);
                pNo(pIndex).buffs[0] = false;
                printf("Buff imunitas teleport hilang.\n");
            } else {
                pNo(pIndex).position = teleporterExit;
                printf("%s teleport ke petak %d,\n", pNo(pIndex).name, teleporterExit);
            }
        } else {
            pNo(pIndex).position = teleporterExit;
            printf("%s teleport ke petak %d,\n", pNo(pIndex).name, teleporterExit);
        }   
    }
};

void endGame(){
    char command[5];
    printf("Selamat kepada %s karena telah memenangkan game ini.\n", pNo(whoseTurn).name);
    getchar();
    printf("Tulis GET untuk mendapatkan hadiah anda: ");
    scanf("%s", command);
    deallocMap();
    if(strcmp(command, "GET") == 0){
        system("START https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }
    exit(0);
};

void checkForWinner(){
    if(pNo(whoseTurn).position == MAP->mapConfig.Neff){
        endGame();
    }
}

void gameLoop(){
    initGame();
    boolean isRolled = false;
    char inputCommand[15];
    int ronde = 1;

    while(1){ // game
        printf("Ronde %d\n", ronde);
        giveAllPlayersRandomSkill();
        giveAllPlayersRandomSkill();
        giveAllPlayersRandomSkill();
        while(whoseTurn <= PLAYERS.NEff){ // ronde
            printf("Giliran %s\n", pNo(whoseTurn).name);
            while(!isTurnEnd){
                printf("Masukkan command: ");
                scanf("%10s", inputCommand);
                if (!strcmp(inputCommand, Commands[0])) { // command = SKILL
                    if(!isRolled){
                        commandSkill(whoseTurn);
                    }
                } else if (!strcmp(inputCommand, Commands[1])) { // command = MAP
                    commandMap();
                } else if (!strcmp(inputCommand, Commands[3])) { // command = INSPECT
                    commandInspect();
                } else if (!strcmp(inputCommand, Commands[4])) { // command = ROLL
                    if(!isRolled){
                        commandRoll(whoseTurn);
                    }
                    isRolled = true;
                    checkForWinner();
                } else if (!strcmp(inputCommand, Commands[5])) { // command = ENDTURN
                    isTurnEnd = isRolled;
                } 
            }

            whoseTurn ++;
            isTurnEnd = false;
            isRolled = false;
        }
        whoseTurn = 1;
        ronde++;
        resetBuff();
    }
}