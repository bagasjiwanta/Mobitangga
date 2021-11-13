#include "mesinkar.h"
#include <stdio.h>

void logErrorThenExit(const char* error, const char* location);

char CC;
boolean EOP;
boolean MBR;

static FILE *pita;
static int retval;

/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. EOP dijadikan false */
void START(const char* fileloc)
{
    pita = fopen(fileloc, "r");
    EOP = false;
    MBR = false;
    ADV();
}

/*  Pita dimajukan satu karakter. Jika file sudah habis, 
    EOP akan bernilai true. MBR akan menyala true jika mesin diharapkan
    untuk berhenti.
    I.S. : Karakter pada jendela = CC
    F.S. : Jika pita masih memiliki karakter, CC menjadi karakter selanjutnya
    setelah CC yang sebelumnya*/
void ADV()
{
    retval = fscanf(pita, "%c", &CC);
    if (retval < 0)
    {
        if (!MBR) {
            logErrorThenExit("Argumen terlalu sedikit", "konfigurasi.txt");
        }
        EOP = true;
        fclose(pita);
    }
}