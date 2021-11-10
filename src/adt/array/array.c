// Nama : I Putu Andika Bagas Jiwanta
// NIM : 18220053
// Topik Praktikum : Pra-Praktikum 2
// Deskripsi : array.h

#include "array.h"
#include <stdio.h>

void MakeEmpty (TabInt *T) {
    (*T).Neff = 0 ;
}

int NbElmt (TabInt T) {
    return T.Neff ;
}

int MaxNbEl (TabInt T) {
    return (IdxMax - IdxMin + 1) ;
}

IdxType GetFirstIdx (TabInt T) {
    return IdxMin ;
}

IdxType GetLastIdx (TabInt T) {
    return T.Neff ;
}

ElType GetElmt (TabInt T, IdxType i) {
    return (T.TI[i]) ;
}

void SetTab (TabInt Tin, TabInt *Tout) {
    *Tout = Tin ;
}

void SetEl (TabInt *T, IdxType i, ElType v) {
    (*T).TI[i] = v ;
}

void SetNeff (TabInt *T, IdxType N) {
    (*T).Neff = N ;
}

boolean IsIdxValid (TabInt T, IdxType i) {
    return ((IdxMin <= i) && (IdxMax >= i)) ;
}

boolean IsIdxEff (TabInt T, IdxType i) {
    return ((GetFirstIdx(T) <= i) && (GetLastIdx(T) >= i)) ;
}

boolean IsEmpty (TabInt T) {
    return (T.Neff == 0) ;
}

boolean IsFull (TabInt T) {
    return (T.Neff == (IdxMax - IdxMin + 1)) ;
}