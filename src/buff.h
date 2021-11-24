#ifndef buff_H
#define buff_H

#include <stdio.h>
#include <stdlib.h>
#include "..list/listlinier.h"
#include "..src/ultang.c"
#include "..src/boolean.h"

typedef struct {
boolean isActive[4];
} Buff;

/* LIST BUFF
    1. Imunitas teleport
    2. Cermin pengganda
    3. Senter pembesar hoki
    4. Senter pengecil hoki */

#define BUFF(B) (B).isActive

void printBuff ();
/* Menampilkan Buff yang dimiliki player */

void resetBuff (Buff *b);
/* reset seluruh buff kecuali imunitas teleport setiap ronde */

#endif