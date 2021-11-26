#include <stdio.h>
#include <stdlib.h>
#include "./adt/list/listlinier.h"
#include "skill.h"
#include "ultang.c"

int RandomNumber (int start, int end, int amount){

    srand(time(0));

    int i;

    for (i = 0; i < amount; i++) {
        int number = (rand() % (end - start + 1)) + start ;
        printf("%d ", number);
    }
}

int Skills (){

    int TabSkill[80];
    int i, Container, Skill;

    for (i=1; i<80; i++){
        if (1 <= i <= 10){
            TabSkill[i] = 1 ;
        }
        else if (11 <= i <= 16){
            TabSkill[i] = 2 ;
        }
        else if (17 <= i <= 31){
            TabSkill[i] = 3 ;
        }
        else if (32 <= i <= 46){
            TabSkill[i] = 4 ;
        }
        else if (47 <= i <= 50){
            TabSkill[i] = 5 ;
        }
        else if (51 <= i <= 80){
            TabSkill[i] = 6 ;
        }
    }
 
    Container = RandomNumber(1, 80, 1);
    Skill = TabSkill[Container];

    return Skill;
}

void insSkill (Pemain P){

    int temp ;

    temp = Skills() ;

    if (temp == 6){

    }
    else{
        InsVLast (&(P).skill, temp);
    }
}

void PrintSkills (Pemain P){

    int i;
    address p;

    p = First((P).skill);

    while (i < NbElmt((P).skill)){
        if (Info(p) == 1){
            printf("Pintu Ga Ke Mana Mana");
        }
        else if (Info(p) == 2){
            printf("Cermin Pengganda");
        }
        else if (Info(p) == 3){
            printf("Senter Pembesar Hoki");
        }
        else if (Info(p) == 4){
            printf("Senter Pengecil Hoki");
        }
        else if (Info(p) == 5){
            printf("Mesin Penukar Posisi");
        }

        p = Next(p);
        i = i + 1;
    }
}


int CommandSkills (Pemain P){

    int idSkill ;

    printf("Masukkan skill : ");
    scanf("%d", idSkill);

    if (idSkill == 1){
        printf(INFOPLAYER(P), "memakai Pintu Ga Ke Mana Mana. Anda akan mendapatkan imunitas terhadap Teleport!");
        PintuGaKemanaMana = true ;
    }
    else if (idSkill == 2){
        printf(INFOPLAYER(P), "memakai Cermin Pengganda. Skill ini akan dibuang dan digantikan dengan 2 skill baru.");
        CerminPengganda = true ;
    }
    else if (idSkill == 3){
        printf(INFOPLAYER(P), "memakai Senter Pembesar Hoki. Dadu hanya akan menghasilkan angka antara setengah dari MaxRoll dan MaxRoll.");
        SenterPembesarHoki = true ;
    }
    else if (idSkill == 4){
        printf(INFOPLAYER(P), "memakai Senter Pengecil Hoki. Dadu hanya akan menghasilkan angka antara 0 dan setengah dari MaxRoll.");
        SenterPengecilHoki = true ;
    }
    else if (idSkill == 5){
        printf(INFOPLAYER(P), "memakai Mesin Penukar Posisi. Pilih pemain yang ingin ditukar posisinya : ");
        MesinPenukarPosisi = true ;
    }

    DelP (&(P).skill, idSkill) ;

    return idSkill;
}

void CerminPengganda(Pemain *P){
    
    List X;
    int i;

    X =(*P).skill;

    if (NbElmt(X) < 9){
        DelP(&X, 2);

        for (i=1; i=2; i++){
            insSkill(P);
        }
    }
    else{
        printf("Cermin Pengganda telah dipakai, tetapi tidak menghasilkan skill apapun.\n");
    }
}