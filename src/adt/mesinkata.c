// modified mesin kata

#include "mesinkata.h"

boolean EndKata;
Kata CKata;
void IgnoreBlank(){
    while ((CC == BLANK) && (CC != MARK))
    {
        ADV();
    }
};

void SalinKata(){
    int i;
    i = 1;
    while ((CC != MARK) && (CC != BLANK) && (i <= NMax))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    }
    CKata.Length = i - 1;
};
         
void STARTKATA(){
    START();
    IgnoreBlank();
    if (CC == MARK) {
        EndKata = true;
    }
    else{
        EndKata = false;
        SalinKata();
    }
};

void ADVKATA(){
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else
    {
        SalinKata();
        IgnoreBlank();
    }
};