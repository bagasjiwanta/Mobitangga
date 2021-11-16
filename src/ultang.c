#include <stdio.h>
#include <stdlib.h>
#include "./adt/queue/queue.h"
#include "functions.h"


typedef struct
{
    char nama[10];
    int letak;
    int Urutan;
    boolean Kalah;
}Pemain;

typedef struct
{
    pemain pem[5];
    int jmlpemain;
}player;

void turn(player p, int *dadu, boolean *issudahkocok, int i)
{   
    int giliran, tdadu; 
    char pilihan,majumundur;

    printf("-----Turn %d-----\n", i);
    giliran=((i-1)%p.jmlpemain)+1;
    printf("Giliran : %s\n", p.pem[giliran].nama);
    printf("Masukkan command: ");
    if(!(*issudahkocok)) 
    {   
        scanf(" %c", &pilihan); //asumsi dadu hanya 1 buah
        while(pilihan != "ROLL"){
        	printf("Command salah!");
        }
        *dadu = rand()% 6 + 1;
        *issudahkocok=true;
    }
    tdadu=*dadu;
    printf("\nDadu  : %d\n", *dadu);
    printf("%s mendapatkan angka %d. \n", p.pem[giliran].nama, tdadu);
    if(CKata.TabKata[i+tdadu] == '#' and CKata.TabKata[i-tdadu] == '#')
	{
    	printf("%s tidak dapat bergerak. \n",p.pem[giliran].nama);
	}
	else if (CKata.TabKata[i+tdadu] == '.'and CKata.TabKata[i-tdadu] == '#') 
	{
		printf("%s dapat maju. \n",p.pem[giliran].nama);
		printf("%s maju %d langkah. \n",p.pem[giliran].nama, tdadu);
		printf("%s berada di petak %d. \n",p.pem[giliran].nama, CKata.TabKata[i+tdadu]);
	}
	else if (CKata.TabKata[i-tdadu] == '.'and CKata.TabKata[i+tdadu] == '#') 
	{
		printf("%s dapat mundur. \n",p.pem[giliran].nama);
		printf("%s mundur %d langkah. \n",p.pem[giliran].nama, tdadu);
		printf("%s berada di petak %d. \n",p.pem[giliran].nama, CKata.TabKata[i-tdadu]);
	}
	else
	{
		printf("%s dapat maju dan mundur. \n",p.pem[giliran].nama);
		printf("Pilih maju/mundur \n");
		scanf(" %c", &majumundur);
		if(majumundur == "maju"){
			printf("%s maju %d langkah. \n",p.pem[giliran].nama, tdadu);
			printf("%s berada di petak %d. \n",p.pem[giliran].nama, CKata.TabKata[i+tdadu]);
		}
		else if(majumundur == "mundur"){
			printf("%s mundur %d langkah. \n",p.pem[giliran].nama, tdadu);
			printf("%s berada di petak %d. \n",p.pem[giliran].nama, CKata.TabKata[i-tdadu]);
		}
		
	}	
}
boolean F_IsPemainEmpty(T_Pemain V_Pemain)
{
    return (strcmp(V_Pemain.nama, "")==0);
}


void ChangeTurn(Queue *Q)
{
	
	infotype X;
	Del(&(*Q), &X);
	Add(&(*Q), X);
}
void statuspemain(player play) 
{
    int i;
    printf("****** STATUS PEMAIN ******\n");
    for(i=1;i<=4;i++)
    {
        if(strcmp("",play.pem[i].nama)!=0)
        {
            printf("-----%s-----\n", play.pem[i].nama);
            printf("Letak pemain di petak : %d\n", play.pem[i].letak);
        }
    }
}
void pemenang (player pl)
{
	if(pl == CKata.TabKata[CKata.Length - 1])
	{
		printf("==========SELAMAT ANDA MENJADI PEMENANG DARI GAME INI!!!==========");
	}
}

