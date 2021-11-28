#include <stdio.h>
#include "array.h"
#include <stdlib.h>

int main(){
    TabInt I;
    TabChar C;
    I.TI = malloc(sizeof(int) * 50);
    I.Neff = 50;
    C.TI = malloc(sizeof(char) * 50);

    I.TI [0] = 1;
    I.TI [1] = 2;
    printf("I: \nindex 0 : Expected 1, Tested %d\nindex 1 : Expected 2, Tested %d\n", I.TI[0], I.TI[1]);
    C.TI[0] = 'a';
    C.TI[1] = 'b';
    C.TI[2] = 'c';
    C.TI[3] = '\0';
    printf("C: \nExpected: abc, Tested: %s", C.TI);

    free(I.TI);
    free(C.TI);
    printf("\nPress enter to exit");
    char c[5];
    scanf("[^\n]", c);
}