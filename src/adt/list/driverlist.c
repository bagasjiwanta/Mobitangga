#include "listlinier.h"
#include <stdio.h>

int main(){
    List L;
    CreateEmpty(&L);
    if(IsListEmpty(L)){
        printf("Yey list sudah kosong\n");
    }
    // address p = ;
    InsVFirst(&L, 2);
    InsVLast(&L, 4);
    InsertFirst(&L, Alokasi(1));
    InsertLast(&L, Alokasi(5));
    address p = First(L);
    p = p->next;
    InsertAfter(&L, Alokasi(3), p);
    printf("Hasil insert:\n\texpected: [1,2,3,4,5]\n\tTested: ");
    PrintInfo(L); printf("\n");
    DelP(&L, 5);
    DelFirst(&L, &p);
    printf("Hasil delete pertama:\n\tExpected : 1, Tested : %d\n", p->info);
    DelLast(&L, &p);
    printf("Hasil delete terakhir:\n\tExpected : 4, Tested : %d\n", p->info);
    address prec = First(L);
    DelAfter(&L, &p, prec);
    printf("Hasil delete setelah elemen 1:\n\tExpected : 3, Tested : %d\n", p->info);
    printf("Jumlah list:\n\texpected : 1, Tested: %d\n", NbElmtList(L));
    for(int i=0;i<5;i++){
        InsVFirst(&L, i);
    }
    printf("Max:\n\tExpected: 4, Tested: %d\n", Max(L));
    List K;
    CreateEmpty(&K);
    copyList(L, &K);
    printf("Hasil copy:\n\tExpected: [2,0,1,2,3,4], Tested: ");
    PrintInfo(K);
    char c[5];
    scanf("[^\n]", c);
}