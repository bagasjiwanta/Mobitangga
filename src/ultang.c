#include <stdio.h>
#include <stdlib.h>

void turn(player p, int *dadu, boolean *issudahkocok, int i)
{   
    int giliran, tdadu; 
    char pilihan;

    printf("-----Turn %d-----\n", i);
    giliran=((i-1)%p.jmlpemain)+1;
    printf("Giliran : %s\n", p.pem[giliran].nama);
    printf("tekan untuk mengocok dadu!");
    if(!(*issudahkocok)) 
    {   
        scanf(" %c", &pilihan);
        *dadu = rand()% 6 + 1;
        *issudahkocok=true;
    }
    tdadu=*dadu
    printf("\nDadu 1 : %d\n", *dadu);
    printf("%s maju sebanyak %d langkah\n", p.pem[giliran].nama, tdadu);
}

