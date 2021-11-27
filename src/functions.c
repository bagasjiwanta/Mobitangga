#include "./adt/player/player.h"
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "./adt/map/map.h"
#include "functions.h"
#include "boolean.h"
#include <time.h>
#include "./adt/stack/stack.h"

const char* Commands[] = {
    "SKILL",
    "MAP",
    "BUFF",
    "INSPECT", 
    "ROLL",
    "ENDTURN",
    "UNDO"
};

Game* GAME;

void SetupGame(int numberOfPlayers){
    GAME = (Game*) malloc (sizeof(Game));
    GAME->whoseTurn = 1;
    GAME->ronde = 1;
    GAME->isRolled = false;
    GAME->isSenterUsed = false;
    GAME->isTurnEnd = false;
    GAME->isCerminUsed = false;
    GAME->givenSkill = 0;
    GAME->playerNames = (char**) malloc (sizeof(char*) * numberOfPlayers);
    for(int i=0;i<numberOfPlayers;i++){
        GAME->playerNames[i] = (char*) malloc (sizeof(char) * 21);
    }
    GAME->GameStack = (Stack*) malloc (sizeof(Stack));
    GAME->GameStack->round = (infotypeStack*) malloc (sizeof(infotypeStack) * 10);
}

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
            char fileloc[50];
            char baseloc[75] = "./public/";
            char tempName[21];

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
            SetupGame(jumlahPemain);    

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
                strcpy(tempName, baseloc);
                strcpy(GAME->playerNames[i-1], tempName);
                // printf("Telah dibuat pemain bernama %s\n", (GAME->playerNames[i-1]));
                CreatePlayer(baseloc, i);
            }
            endOperation = true;
        } else if (choice == 'e') {
            // prosedur exit
            printf("~Good Bye~");
            exit(0);
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
        printf("%s\t\t: %s\n", Name(i), temp+1);
        temp[x] = MAP->mapConfig.TI[x];
    }
    free(temp);
};

void useSkill(int pIndex, int skillIndex){
    int firstSkill, secondSkill, j, i, tempPosition;
    int tempArr[4] = {0, 0, 0, 0};
    switch(skillIndex){
        case 1:
            pNo(pIndex).buffs[0] = true;
            printf("Buff imunitas teleport dinyalakan.\n");
            break;
        case 2:
            if(GAME->isCerminUsed){ return; }
            if(pNo(pIndex).skillCount > 9){ return; }
            firstSkill = givePlayerRandomSkill(pIndex);
            secondSkill = givePlayerRandomSkill(pIndex);
            printf("%s mendapatkan 2 skill baru:\n1. %s\n2. %s\n",
                Name(pIndex), SkillNames[firstSkill-1], SkillNames[secondSkill-1]
            );
            GAME->isCerminUsed = true;
            break;
        case 3:
            if(GAME->isSenterUsed){ return; }
            pNo(pIndex).buffs[2] = true;
            printf("Buff senter pembesar hoki milik %s dinyalakan.\n", Name(pIndex));
            GAME->isSenterUsed = true;
            break;
        case 4:
            if(GAME->isSenterUsed){ return; }
            pNo(pIndex).buffs[3] = true;
            printf("Buff senter pengecil hoki milik %s dinyalakan.\n", Name(pIndex));
            GAME->isSenterUsed = true;
            break;
        case 5:
            j = 1;
            printf("Saat ini kamu berada di petak ke-%d.\n", pNo(pIndex).position);
            printf("Posisi pemain lain saat ini:\n");
            for(i=1;i<=PLAYERS.NEff;i++){
                if(i != pIndex){
                    printf("%d. %s %d.\n", j, Name(i), pNo(i).position);
                    tempArr[j-1] = i;
                    j++;
                }
            }
            printf("Dengan pemain ke berapakah kamu ingin menukar posisi (misal : 1): ");
            scanf("%d", &j);
            if(j > PLAYERS.NEff - 1){ printf("Tidak valid.\n"); return; }
            j = tempArr[j-1];
            tempPosition = pNo(pIndex).position;
            pNo(pIndex).position = pNo(j).position;
            pNo(j).position = tempPosition;
            printf("%s berhasil menukar posisinya dengan %s", Name(pIndex), Name(j));
            break;
        default:
            return;
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
        return;
    } else {
        isGonnaUse = k > 0;
        k = abs(k);
        if(availables[k-1] == -1){
            printf("Kamu tidak memiliki skill ini\n");
            return;
        } else {
            printf("%s ", Name(pIndex));
            if(isGonnaUse){ printf("memakai"); } else { printf("membuang"); }
            printf(" skill %s.\n", SkillNames[availables[k-1]]);
            if(isGonnaUse){
                useSkill(pIndex, availables[k-1] + 1);
            }
            DelP(&(pNo(pIndex).skill), availables[k-1] + 1);
        }
    }
};

void commandBuff(int pIndex){
    printf("Buff milik %s:\n", Name(pIndex));
    for(int i=0;i<4;i++){
        printf("%d. %s: ", i+1, BuffNames[i]);
        if(pNo(pIndex).buffs[i]) { printf("nyala.\n"); } else { printf("mati.\n"); }
    }
}

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

    printf("Before: %d\n", diceResult);
    if (pNo(pIndex).buffs[2]) { // senter pembesar hoki
        printf("Yey pembesar hokinya dinotice\n");
        diceResult = (diceResult % (MAP->defaultMaxRoll / 2)) + (MAP->defaultMaxRoll / 2);
    } else if (pNo(pIndex).buffs[3]) { // senter pengecil hoki
        printf("Yey pengecil hokinya dinotice\n");
        diceResult = diceResult % ((MAP->defaultMaxRoll / 2) + 1);
    }
    printf("%s mendapatkan dadu: %d\n", NameNow, diceResult);

    canForward = isPetakValid(diceResult + currentPost);
    canBackward = isPetakValid(currentPost - diceResult);

    // testcases
    int choice;
    int toWhere = 0;
    // printf("cb: %d, cf: %d\n", canBackward, canForward);
    if(canBackward && canForward){
        printf("%s dapat maju dan mundur.", Name(pIndex));
        printf("Ke mana %s mau bergerak:\n", Name(pIndex));
        printf("1. %d\n", currentPost - diceResult);
        printf("2. %d\n", currentPost + diceResult);
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        choice = (choice % 3);
        if(choice==0){choice++;}
        if(choice==1){
            toWhere = currentPost - diceResult;
            printf("%s mundur %d langkah.\n", Name(pIndex), diceResult);
        } else {
            toWhere = currentPost + diceResult;
            printf("%s maju %d langkah.\n", Name(pIndex), diceResult);
        }
    } else if (canBackward) {
        printf("%s dapat mundur.\n", Name(pIndex));
        printf("%s mundur %d langkah.\n", Name(pIndex), diceResult);
        toWhere = currentPost - diceResult;
    } else if (canForward) {
        printf("%s dapat maju.\n", Name(pIndex));
        printf("%s maju %d langkah.\n", Name(pIndex), diceResult);
        toWhere = currentPost + diceResult;
    } else {
        printf("%s tidak dapat bergerak.\n", Name(pIndex));
    }
    // printf("Masuk kesini kah\n");
    movePlayer(pIndex, toWhere);
};

void movePlayer(int pIndex, int toWhere) {
    int teleporterExit;
    char teleportChoice[2];
    if(toWhere == 0){
        return;
    }
    pNo(pIndex).position = toWhere;
    printf("%s berada di petak %d.\n", Name(pIndex), toWhere);
    teleporterExit = checkTeleporter(toWhere);
    
    if(teleporterExit != 0){
        printf("%s menemukan teleporter.\n", Name(pIndex));
        if(pNo(pIndex).buffs[0]){
            printf("%s memiliki imunitas teleporter.\n", Name(pIndex));
            printf("Apakah %s ingin teleport (Y/N)? ", Name(pIndex));
            scanf("%1s", teleportChoice);
            if( strcmp(teleportChoice, "Y") != 0 
                &&
                strcmp(teleportChoice, "N") != 0){strcpy(teleportChoice, "Y");}

            if(strcmp(teleportChoice, "N") == 0){
                printf("%s tidak teleport.\n", Name(pIndex));
                pNo(pIndex).buffs[0] = false;
                printf("Buff imunitas teleport hilang.\n");
            } else {
                pNo(pIndex).position = teleporterExit;
                printf("%s teleport ke petak %d,\n", Name(pIndex), teleporterExit);
            }
        } else {
            pNo(pIndex).position = teleporterExit;
            printf("%s teleport ke petak %d,\n", Name(pIndex), teleporterExit);
        }   
    }
};

void deallocGame(){
    free(GAME);
}

void endGame(){
    char command[5];
    int tempPos, tempRank;
    int positions[4] = {0, 0, 0, 0};
    int ranks[4] = {1, 2, 3, 4};
    printf("Selamat kepada %s karena telah memenangkan game ini.\n", NameNow);
    for(int i=1;i<=PLAYERS.NEff;i++){
        positions[i-1] = pNo(i).position;
    }
    for(int k=0;k<3;k++){
        for(int j=0;j<PLAYERS.NEff-1;j++){
            if(positions[j] > positions[j+1]){
                tempPos = positions[j];
                positions[j] = positions[j+1];
                positions[j+1] = tempPos;

                tempRank = ranks[j];
                ranks[j] = ranks[j+1];
                ranks[j+1] = tempRank;
            }
        }
    }
    printf("Peringkat akhir :\n");
    for(int l=PLAYERS.NEff;l>0;l--){
        printf("Rank %d : %s.\n", PLAYERS.NEff - l + 1, Name(ranks[l-1]));
    }

    getchar();
    printf("Tulis GET untuk mendapatkan hadiah anda: ");
    scanf("%s", command);
    deallocMap();
    deallocGame();
    if(strcmp(command, "GET") == 0){
        system("START https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    }
    exit(0);
};

void checkForWinner(){
    if(pNo(GAME->whoseTurn).position == MAP->mapConfig.Neff){
        endGame();
    }
}

void gameLoop(){
    initGame();

    while(1){ // game
        // printf("Ronde %d\n", ronde);
        while(GAME->whoseTurn <= PLAYERS.NEff){ // ronde

            printf("Giliran kamu %s\n", NameNow);
            GAME->givenSkill = givePlayerRandomSkill(GAME->whoseTurn);

            if(GAME->givenSkill == 0){
                printf("Skill kamu sudah penuh, kamu tidak bisa mendapatkan skill lagi :(.\n");
            } else if(GAME->givenSkill == 6){
                printf("Yah . . . kamu tidak mendapatkan skill karena kurang beruntung.\n");
            } else {
                printf("Kamu mendapat skill %s.\n", SkillNames[GAME->givenSkill - 1]);
            }
            while(!(GAME->isTurnEnd)){
                printf("\nMasukkan command: ");
                scanf("%10s", GAME->inputCommand);
                if (!strcmp(GAME->inputCommand, Commands[0])) { // command = SKILL
                    if(!(GAME->isRolled)){
                        commandSkill(GAME->whoseTurn);
                    }
                } else if (!strcmp(GAME->inputCommand, Commands[1])) { // command = MAP
                    commandMap();
                } else if (!strcmp(GAME->inputCommand, Commands[2])) { // command = BUFF
                    commandBuff(GAME->whoseTurn);
                }
                else if (!strcmp(GAME->inputCommand, Commands[3])) { // command = INSPECT
                    commandInspect();
                } else if (!strcmp(GAME->inputCommand, Commands[4])) { // command = ROLL
                    if(!GAME->isRolled){
                        commandRoll(GAME->whoseTurn);
                    }
                    GAME->isRolled = true;
                    checkForWinner();
                } else if (!strcmp(GAME->inputCommand, Commands[5])) { // command = ENDTURN
                    GAME->isTurnEnd = GAME->isRolled;
                } 
            }
            GAME->whoseTurn ++;
            GAME->isTurnEnd = false;
            GAME->isRolled = false;
            GAME->isSenterUsed = false;
            GAME->isCerminUsed = false;
        }
        GAME->whoseTurn = 1;
        GAME->ronde++;
        resetBuff();
    }
}
