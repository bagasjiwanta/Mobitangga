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

const char* BuffNames[] = {
    "Imunitas Teleport",
    "Cermin Pengganda",
    "Senter Pembesar Hoki",
    "Senter Pengecil Hoki",
};

void initPlayers(int numberOfPlayers){
    PLAYERS.NEff = numberOfPlayers;
    int i;
    for(i=1;i<=numberOfPlayers;i++){
        CreateEmpty(&(pNo(i).skill));
    }
};


void CreatePlayer(char* name, int playerIndex){
    int i, j;
    strcpy(pNo(playerIndex).name, name);
    pNo(playerIndex).position = 1;
    for(i=0;i<4;i++){
        pNo(playerIndex).buffs[i] = 0;
    }
    CreateEmpty(&(pNo(playerIndex).skill));
    pNo(i).skillCount = 0;
    PLAYERS.NEff ++;
};

int givePlayerRandomSkill(int pIndex){
    int x = 0;
    if(!(pNo(pIndex).skillCount >= 10)){
        x = randInt(20) + 1;

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
            InsVLast(&(pNo(pIndex).skill), x);
            pNo(pIndex).skillCount ++;
        }
    }
    return x;
};
