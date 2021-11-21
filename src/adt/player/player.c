#include "player.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*
#include "listdp.h"
#include <stdio.h>

address addressAt(List L, int x){
    address p = First(L);
    int i = 1;
    while(i < x){
        p = Next(p);
        i++;
    }
    return p;
}

int main() {
    int a, b, i, j;
    List L;
    address p;
    scanf("%d", &a);
    CreateEmpty(&L);
    int sum = 0;
    int count = 0;

    for(i=0;i<6;i++){
        InsVLast(&L, 0);
    }

    for(i=0;i<a;i++){
        scanf("%d", &b);
        if(b>0) {
            if(count != 10){
                sum += b;
                count ++;
                p = addressAt(L, b);
                Info(p) ++;
                printf("%d %d\n", count, sum);
            } else {
                printf("Skill penuh\n");
            }
        } else {
            b = b * (-1);
            p = addressAt(L, b);
            if(Info(p) == 0){
                printf("Tidak ada skill\n");
            } else {
                p = addressAt(L, b);
                Info(p) --;
                count--;
                sum -= b;
                printf("%d %d\n", count, sum);
            }
        }
    }
}
*/

Players PLAYERS;

char** SkillNames;


void initPlayers(int numberOfPlayers){
    PLAYERS.NEff = numberOfPlayers;
    int i;
    for(i=1;i<=numberOfPlayers;i++){
        CreateEmpty(&(playerNo(i).skills));
    }
}

void initSkillNames(){
    SkillNames = (char**) malloc (sizeof(char*) * 6); 

    SkillNames[0] = (char*) malloc (sizeof(char) * 22);
    strcpy(SkillNames[0], "Pintu Ga Ke Mana Mana");
    SkillNames[1] = (char*) malloc (sizeof(char) * 22);
    strcpy(SkillNames[1], "Cermin Pengganda");
    SkillNames[2] = (char*) malloc (sizeof(char) * 22);
    strcpy(SkillNames[2], "Senter Pembesar Hoki");
    SkillNames[3] = (char*) malloc (sizeof(char) * 22);
    strcpy(SkillNames[3], "Senter Pengecil Hoki");
    SkillNames[4] = (char*) malloc (sizeof(char) * 22);
    strcpy(SkillNames[4], "Mesin Penukar Posisi");
    SkillNames[5] = (char*) malloc (sizeof(char) * 22);
    strcpy(SkillNames[5], "Teknologi Gagal");
}

void deallocSkillNames(){
    free(SkillNames);
}

void CreatePlayer(char* name, int playerIndex){
    int i, j;
    strcpy(playerNo(playerIndex).name, name);
    playerNo(playerIndex).position = 1;
    for(i=0;i<4;i++){
        playerNo(playerIndex).buffs[i] = 0;
    }
    
    for(j=0;j<6;j++){
        InsVFirst(&(playerNo(playerIndex).skills), 0);
    }
    playerNo(i).skillCount = 0;

    PLAYERS.NEff ++;
}

int getSkills(int playerIndex){
    int skillArray = 1000000;
    int i;
    address p = playerNo(playerIndex).skills.First;
    for(i=0;i<6;i++){
        skillArray += (p->info) * ((int) powf(10, 6-i-1));
        p = p->next;
    }
    return skillArray;
}

void givePlayersRandomSkill(){
    int i, j, x;
    address p;
    for(i=1;i<=NumOfPlayers;i++){
        if(!(playerNo(i).skillCount >= 10)){
            x = random(5) + 1;
            p = playerNo(i).skills.First;
            for(j=1;j<x;j++){
                p = p->next;
            }
            p->info ++;
            playerNo(i).skillCount ++;
        }
    }
}

