/* Nim : 18220053 */
/* Nama : I Putu Andika Bagas Jiwanta */
/* Tanggal : 2 November 2021 */
/* Topik : Prapraktikum 6 */

#include "listdp.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L){
    return (First(L)==Nil && Last(L)==Nil);
}
/* Mengirim true jika list kosong. Lihat definisi di atas. */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L){
    First(*L)=Nil;
    Last(*L)=Nil;
}

address Alokasi (infotype X){
    address P;
    P = (ElmtList *) malloc(sizeof(ElmtList));
    if (P != Nil) {
        Info (P) = X;
        Next (P) = Nil;
        Prev(P) = Nil;
        return P;    
    }
    else {
        return Nil;
    }
}

void Dealokasi (address P){
    free(P);
}

address Search (List L, infotype X){
    address P = First(L) ;
    boolean found = false ;
    if (IsEmpty(L)) {
        return Nil ;
    }
    else {
        while (P != Nil && Info(P) != X) {
                P = Next(P) ;
            }
        }
        return P ;
}

void InsVFirst (List *L, infotype X){
    address P;
    P = Alokasi(X);
    if (P != Nil) {
        InsertFirst(L, P);
    }
}

void InsVLast (List *L, infotype X){
    address P = Alokasi(X);
    if (P != Nil){
        InsertLast(L, P);
    }    
}

void DelVFirst (List *L, infotype *X){
    address P;
    DelFirst(L, &P);
    *X = Info(P);
    Dealokasi(P);
}

void DelVLast (List *L, infotype *X){
    address P;
    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(P);
}

void InsertFirst (List *L, address P){
    if (IsEmpty(*L)) {
        First(*L) = P;
        Last(*L) = P;
        Prev(P) = Nil;
        Next(P) = Nil;
    }
    else {
        Prev(P) = Nil;
        Prev(First(*L)) = P;
        Next(P) = First(*L);
        First(*L) = P;
    }    
}

void InsertLast (List *L, address P){
    if (IsEmpty(*L)) {
        InsertFirst(L, P);
    }
    else {
        Next(P) = Nil;
        Next(Last(*L)) = P;
        Prev(P) = Last(*L);
        Last(*L) = P;
    }

}

void InsertAfter (List *L, address P, address Prec){
    if (Prec == Last(*L)) {
        InsertLast(L, P) ;
    }
    else {
        Next(P) = Next(Prec) ;
        Next(Prec) = P ;
        Prev(P) = Prec ;
        Prev(Next(P)) = P ;
    }    
}

void InsertBefore (List *L, address P, address Succ){
    if (Succ == First(*L)) {
        InsertFirst(L, P) ;
    }
    else {
        Next(Prev(Succ)) = P ;
        Next(P) = Succ ;
        Prev(P) = Prev(Succ) ;
        Prev(Succ) = P ;
    }
}

void DelFirst (List *L, address *P) {
    *P = First(*L) ;
    if (Next(*P) == Nil) {
        CreateEmpty(L) ;
    }
    else {
        First(*L) = Next(*P) ;
        Prev(Next(*P)) = Nil ;
    }
}

void DelLast (List *L, address *P) {
    *P = Last(*L) ;
    if (Prev(*P) == Nil) {
        CreateEmpty(L) ;
    }
    else {
        Last(*L) = Prev(*P) ;
        Next(Prev(*P)) = Nil ;
    }
}


// void DelAfter (List *L, address *Pdel, address Prec){
//     *Pdel = Next(Prec);
//     Next(Prec) = Next(*Pdel);
//     if (Next(*Pdel)!=Nil){
//         Prev(Next(*Pdel)) = Prec;
//     }
//     else {
//         Last(*L)=Prec;
//     }
//     Next(*Pdel) = Nil;
//     Prev(*Pdel) = Nil;
// }

// void DelBefore (List *L, address *Pdel, address Succ){
//     *Pdel = Prev(Succ);
//     Prev(Succ) = Prev(*Pdel);
//     if (Prev(*Pdel)!=Nil){
//         Next(Prev(*Pdel)) = Succ;
//     }
//     else {
//         First(*L) = Succ;
//     }
//     Next(*Pdel) = Nil;
//     Prev(*Pdel) = Nil;
// }

// void DelP (List *L, infotype X){
//     address P;
//     P = Search(*L, X);
//     if (P!=Nil){
//         if (Prev(P)!=Nil) {
//             DelAfter(L, P, Prev(P));
//         }
//         else if (Next(P)!=Nil){
//             DelBefore(L, P, Next(P));
//         }
//         else {
//             Last(*L)=Nil;
//             First(*L)=Nil;
//         }
//     }
// }

void PrintForward (List L) {
    address P ; 
    P = First(L) ;
    printf("[") ;
    if (!IsEmpty(L)) {
        printf("%d", Info(P)) ;
        P = Next(P) ;
        while (P != Nil) {
            printf(",%d", Info(P)) ;
            P = Next(P) ;
        }
    }
    printf("]") ;
}

void PrintBackward (List L) {
    address P ; 
    P = Last(L) ;
    printf("[") ;
    if (!IsEmpty(L)) {
        printf("%d", Info(P)) ;
        P = Prev(P) ;
        while (P != Nil) {
            printf(",%d", Info(P)) ;
            P = Prev(P) ;
        }
    }
    printf("]") ;
}