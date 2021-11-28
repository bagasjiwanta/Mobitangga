#include "listlinier.h"
#include <stdlib.h>
#include <stdio.h>

/* 
	Nama 	: I Putu Andika Bagas Jiwanta
	NIM 	: 18220053
	Topik 	: Praktikum 5, nomor 2
*/

boolean IsListEmpty (List L){
  	return First(L) == NULL;
};

void CreateEmpty (List *L){
  	First(*L) = NULL;
};

address Alokasi (infotype X){
	address p = (address) malloc (sizeof(ElmtList));
	if(p != Nil){
		Info(p) = X;
		Next(p) = Nil;
	}
	return p;
};

void Dealokasi (address *P) { 
  	free(*P);
}

address Search (List L, infotype X){
	address p = First(L);
	while (Next(p) != Nil) {
		if((Info(p)) == X) { 
		return p;
		}
        p = Next(p);
	}
    if (Info(p) == X) {
	    return p;
    }
	return Nil;
};

void InsVFirst (List *L, infotype X){
	address p = First(*L);
	address q = Alokasi(X);
	Next(q) = p;
	First(*L) = q;
};

void InsVLast (List *L, infotype X){
	address p = Alokasi(X);
    if(p != Nil){
        InsertLast(L, p);
    }
};

void DelVFirst (List *L, infotype *X){
	address p = First(*L);
	address q = Next(p);
	First(*L) = q;
    *X = Info(p);
	Dealokasi(&p);
};

void DelVLast (List *L, infotype *X){
	address p;
    DelLast(L, &p);
    *X = Info(p);
    Dealokasi(&p);
};

void InsertFirst (List *L, address P){
	address x = First(*L);
	Next(P) = x;
	First(*L) = P;
};

void InsertAfter (List *L, address P, address Prec) {
	address x = Next(Prec);
	Next(Prec) = P;
	Next(P) = x;
};

void InsertLast (List *L, address P) {
	address x = First(*L);
    if(IsListEmpty(*L)) { 
        InsertFirst(L, P);
    } else {
	    while (Next(x) != Nil) { 
		    x = Next(x);
	    }
	    Next(x) = P;
    }
};

void DelP (List *L, infotype X){
    address P, Prec, Pdel;
    boolean found;
    P = First(*L);
    Prec = Nil;
    found = false;
    while ( P!=Nil && found==false ){
        if (Info(P)==X){
            found = true;
        }
        else {
            Prec = P;
            P = Next(P);
        }
    }
    if (found == true) {
        if (Prec == Nil) { 
            DelFirst(L, &Pdel);
            Dealokasi(&Pdel);
        }
        else {  
            DelAfter(L, &Pdel, Prec);
            Dealokasi(&Pdel);
        }
    }
}

void DelFirst (List *L, address *P){
	address x = First(*L);
	address y = Next(x);
	First(*L) = y;
	(*P) = x;
};

void DelLast (List *L, address *P){
    address last, preclast;
    last = First(*L);
    preclast = Nil;
    while (Next(last)!=Nil){
        preclast = last;
        last = Next(last);
    }
    if (preclast == Nil) {
        DelFirst(L,P);
    }
    else (DelAfter(L,P, preclast));
}

void DelAfter (List *L, address *Pdel, address Prec){
    address P;
    boolean found;
    P = First(*L);
    found = false;
    while ( P!=Nil && found==false ){
        if (P == Prec){
            found = true;
        }
        else {
            P = Next(P);
        }
    }
    *Pdel = Next(P);
    Next(P) = Next(Next(P));
    Next(*Pdel) = Nil;
}

void PrintInfo (List L){
    address P;
    printf("\n\t[");
    if (!IsListEmpty(L)) {
        P = First(L);
        do {
            printf("%d", Info(P));
            P = Next(P);
            if (P != Nil)
                printf(",");
        } 
        while (P != Nil);
    }
    printf("]\n");
}

int NbElmtList (List L){
    int count;
    address P;
    count = 0;
    P = First(L);
    while (P!=Nil){
        count = count + 1;
        P = Next(P);
    }
    return count;
}

infotype Max (List L){
    infotype nmax;
    address P;
    nmax = Info(First(L));
    P = Next(First(L));
    while (P!=Nil) {
        if (nmax < Info(P)){
            nmax = Info(P);
        }
        P = Next(P);
    }
    return nmax;
}

void Konkat1 (List *L1, List *L2, List *L3){
    CreateEmpty(L3);
    if (IsListEmpty(*L1)==false) {
        address P = First(*L1);
        First(*L3) = P;
        while (Next(P) != Nil) {
            P = Next(P);
        }
        Next(P) = First(*L2);
    } else {
        First(*L3) = First(*L2);
    }
    CreateEmpty(L1);
    CreateEmpty(L2);
       
}

void copyList(List src, List* dest){
    int temp;
    address p;
    while (dest->First != Nil) {
        DelVFirst(dest, &temp);
    }
    p = src.First;
    while (p != Nil){
        InsVFirst(dest, p->info);
        p = p->next;
    }
}