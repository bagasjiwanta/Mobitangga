#ifndef skill_H
#define skill_H

#include <stdio.h>
#include <stdlib.h>
#include "../list/listlinier.h"
#include "../src/ultang.c"

boolean PintuGaKemanaMana;

boolean CerminPengganda;

boolean SenterPembesarHoki;

boolean SenterPengecilHoki;

boolean MesinPenukarPosisi;

int RandomNumber (int start, int end, int amount);
/* Menghasilkan angka random */


int Skills ();
/* Mengirimkan hasil skill yang didapat menggunakan randomizer */
/*     1 : Pintu Ga Ke Mana Mana
       2 : Cermin Pengganda
       3 : Senter Pembesar Hoki
       4 : Senter Pengecil Hoki
       5 : Mesin Penukar Posisi
       6 : Teknologi Gagal       */

void insSkill (Pemain P);
/* Memasukkan skill ke dalam profil player */


void PrintSkills (Pemain P);
/* Mengeluarkan list skill yang dimiliki player */


int CommandSkills (Player P);
/* Mengeluarkan perintah meminta masukkan skill yang ingin dipakai */

#endif