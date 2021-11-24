#include "player.h"
#include "../map/map.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Players PLAYERS;

const char* SkillNames[] = {
    "Pintu Ga Ke Mana Mana",
    "Cermin Pengganda",
    "Senter Pembesar Hoki",
    "Senter Pengecil Hoki",
    "Mesin Penukar Posisi",
    "Teknologi Gagal"
};

void initPlayers(int numberOfPlayers){
    PLAYERS.NEff = numberOfPlayers;
    int i;
    for(i=1;i<=numberOfPlayers;i++){
        CreateEmpty(&(playerNo(i).skill));
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
}

void commandInspect(int at){
    if(MAP->mapConfig.TI[at] == '#'){
        printf("Petak %d merupakan petak terlarang", at);
    } else if (MAP->teleporters.TI[at] != 0) {
        printf("Petak %d memiliki teleporter menuju %d", at, MAP->teleporters.TI[at]);
    } else {
        printf("Petak %d merupakan petak kosong", at);
    }
}

void CreatePlayer(char* name, int playerIndex){
    int i, j;
    strcpy(playerNo(playerIndex).name, name);
    playerNo(playerIndex).position = 1;
    for(i=0;i<4;i++){
        playerNo(playerIndex).buffs[i] = 0;
    }
    CreateEmpty(&(playerNo(playerIndex).skill));
    playerNo(i).skillCount = 0;
    PLAYERS.NEff ++;
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
        scanf("%d", j);
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
}

void giveAllPlayersRandomSkill(){
    int i, j, x;
    address p;
    for(i=1;i<=NumOfPlayers;i++){
        if(!(playerNo(i).skillCount >= 10)){
            x = random(20) + 1;
            if(x < 4){
                x = 1;
            } else if (x < 6) {
                x = 2;
            } else if (x < 9) {
                x = 3;
            } else if (x < 12) {
                x = 4;
            } else if (x < 13) {
                x = 5;
            } else {
                x = 6;
            }
            if (x != 6){
                InsVLast(&(playerNo(i).skill), x);
                playerNo(i).skillCount ++;
            }
            printf("%s mendapatkan %s\n", 
                playerNo(i).name, SkillNames[x-1]
            );
        }
    }
};
