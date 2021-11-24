#include <stdio.h>
#include <stdlib.h>
#include "..list/listlinier.h"
#include "..src/ultang.c"
#include "buff.h"

void printBuff (Buff B) {
    for (int i = 0; i < 4; i++) {
        if (BUFF(B)[0]) {
            printf("Anda memiliki buff imunitas teleport. Anda tidak akan kemana-mana.");
        }
        else if (BUFF(B)[1]) {
            printf("Anda memiliki buff cermin pengganda. Anda mendapatkan 2 skill baru!");
        }
        else if (BUFF(B)[2]) {
            printf("Anda memiliki buff senter pembesar hoki.");
        }
        else if (BUFF(B)[3]) {
            printf("Anda memiliki buff senter pengecil hoki.");
        }
    }
}

void resetBuff (Buff *B) {
    for (int i = 0; i < 4; i++) {
        BUFF(*B)[i] = false;
    }
}