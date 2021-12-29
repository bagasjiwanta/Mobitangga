/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */

#include "../../boolean.h"

#ifndef ARRAY_H 
#define ARRAY_H

/* Kamus Umum */

#define IdxMax 100
#define IdxMin 1
#define IdxUndef -999 /* indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType;

typedef struct 
{
	int* TI; /* memori tempat penyimpan elemen (container) */
	int Neff; /* banyaknya elemen efektif */
} TabInt;

typedef struct 
{
	char* TI;
	int Neff;
} TabChar;

#endif