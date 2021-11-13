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
        scanf(" %c", &pilihan); //asumsi dadu hanya 1 buah
        *dadu = rand()% 6 + 1;
        *issudahkocok=true;
    }
    tdadu=*dadu
    printf("\nDadu 1 : %d\n", *dadu);
    printf("%s maju sebanyak %d langkah\n", p.pem[giliran].nama, tdadu);
    //perlu kondisi dari map yang # bakal diam.
}

boolean ispemainempty(pemain p)
{
    return (strcmp(p.nama, "")==0);
}

void insertjumlahpemain(player *p, Queue *Q)
{
    int i;
    printf("Jumlah pemain : ");
    scanf("%d", &(*p).jmlpemain);
    CreateEmpty(&(*Q), (*p).jmlpemain);
    for(i=1;i<=(*p).jmlpemain;i++)
    {
        printf("Nama Pemain %d : ", i);
        scanf("%s", &(*p).pem[i].nama);
        Add(&(*Q), i);
    }
}

void ChangeTurn(Queue *Q)
{
	
	infotype X;
	Del(&(*Q), &X);
	Add(&(*Q), X);
}
