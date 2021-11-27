#ifndef stackt_H
#define stackt_H

#include "../../boolean.h"
#include "../list/listlinier.h"

#define NilStack 0
/* Nil adalah stack dengan elemen kosong . */
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

typedef struct {
  int position;
  int buffs[4];
  List skills;
} playerState;

typedef struct {
  playerState* player;
} infotypeStack;

typedef int addressStack;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[1]..T[MaxEl] */
/* Jika S adalah Stack maka akses elemen : */
/* InfoTop(S) untuk mengakses elemen TOP */
/* Top(S) adalah alamat elemen TOP */
typedef struct {
  infotypeStack* round; /* tabel penyimpan elemen */
  addressStack TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).round[(S).TOP]

/* Membuat stack kosong */
/* I.S. sembarang; */
/* F.S. S stack yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
void CreateEmptyStack (Stack *S);

/* Mengirim true jika Stack kosong*/
boolean IsStackEmpty (Stack S);

/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
void Push (Stack * S, infotypeStack X);

/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
void Pop (Stack * S, infotypeStack* X);

#endif
