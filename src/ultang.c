#include <stdio.h>
#include <stdlib.h>
#include "./adt/queue/queue.h"
#include "./adt/mesinkata/mesinkata.h"
#include "./adt/list/listlinier.h"
#include "./adt/map/map.h"
#include "functions.h"


typedef struct
{
    char nama[10];
    int letak;
    int Urutan;
    boolean Kalah;
    List skill;
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
        *dadu = rand()% 6 + 1;  //asumsi dadu hanya 1 buah
        *issudahkocok=true;
    }
    tdadu=*dadu;
    printf("\nDadu  : %d\n", *dadu);
    printf("%s mendapatkan angka %d. \n", p.pem[giliran].nama, tdadu);
    if(MAP->mapConfig.TI[x+tdadu] == '#' and MAP->mapConfig.TI[x-tdadu] == '#')
	{
    	printf("%s tidak dapat bergerak. \n",p.pem[giliran].nama);
	}
	else if (MAP->mapConfig.TI[x+tdadu] == '.'and MAP->mapConfig.TI[x-tdadu] == '#') 
	{
		printf("%s dapat maju. \n",p.pem[giliran].nama);
		printf("%s maju %d langkah. \n",p.pem[giliran].nama, tdadu);
		printf("%s berada di petak %d. \n",p.pem[giliran].nama, MAP->mapConfig.TI[x+tdadu]);
	}
	else if (MAP->mapConfig.TI[x-tdadu] == '.'and MAP->mapConfig.TI[x+tdadu] == '#') 
	{
		printf("%s dapat mundur. \n",p.pem[giliran].nama);
		printf("%s mundur %d langkah. \n",p.pem[giliran].nama, tdadu);
		printf("%s berada di petak %d. \n",p.pem[giliran].nama, MAP->mapConfig.TI[x-tdadu]);
	}
	else
	{
		printf("%s dapat maju dan mundur. \n",p.pem[giliran].nama);
		printf("Pilih maju/mundur \n");
		scanf(" %c", &majumundur);
		if(majumundur == "maju"){
			printf("%s maju %d langkah. \n",p.pem[giliran].nama, tdadu);
			printf("%s berada di petak %d. \n",p.pem[giliran].nama, MAP->mapConfig.TI[x+tdadu]);
		}
		else if(majumundur == "mundur"){
			printf("%s mundur %d langkah. \n",p.pem[giliran].nama, tdadu);
			printf("%s berada di petak %d. \n",p.pem[giliran].nama, MAP->mapConfig.TI[x-tdadu]);
		}
		
	}	
}
boolean F_IsPemainEmpty(T_Pemain V_Pemain)
{
    return (strcmp(V_Pemain.nama, "")==0);
}

int jumlahpemain(player p)
{
    if (F_IsPemainEmpty) {
	  printf("0");
    }
    else {
	  return jmlpemain;
    }
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
	if(pl == MAP->mapConfig.neff)//ujung map
	{
		printf("==========SELAMAT ANDA MENJADI PEMENANG DARI GAME INI!!!==========");
	}
}

