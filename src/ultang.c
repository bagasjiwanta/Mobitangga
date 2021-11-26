#include <stdio.h>
#include <stdlib.h>
#include "./adt/queue/queue.h"
#include "./adt/array/array.h"
#include "./adt/list/listlinier.h"
#include "./adt/map/map.h"
#include "functions.h"
#include <string.h>


typedef struct
{
    char nama[10];
    int letak;
    int Urutan;
    boolean Kalah;
    List skill;
}T_Pemain;

typedef struct
{
    T_Pemain T[5];
    int jmlpemain;
}T_TabPemain;


void turn(T_TabPemain p, int *dadu, boolean *issudahkocok, int i)
{   
    int giliran, tdadu; 
    char pilihan,majumundur;

    printf("-----Turn %d-----\n", i);
    giliran=((i-1)%p.jmlpemain)+1;
    printf("Giliran : %s\n", p.T[giliran].nama);
    printf("Masukkan command: ");
    if(!(*issudahkocok)) 
    {   
        *dadu = rand()% 6 + 1;  //asumsi dadu hanya 1 buah
        *issudahkocok=true;
    }
    tdadu=*dadu;
    printf("\nDadu  : %d\n", *dadu);
    printf("%s mendapatkan angka %d. \n", p.T[giliran].nama, tdadu);
    if(MAP->mapConfig.TI[i+tdadu] == '#') && (MAP->mapConfig.TI[i-tdadu] == '#')
	{
    	printf("%s tidak dapat bergerak. \n",p.T[giliran].nama);
	}
	else if (MAP->mapConfig.TI[i+tdadu] == '.') && (MAP->mapConfig.TI[i-tdadu] == '#')
	{
		printf("%s dapat maju. \n",p.T[giliran].nama);
		printf("%s maju %d langkah. \n",p.T[giliran].nama, tdadu);
		printf("%s berada di petak %d. \n",p.T[giliran].nama, MAP->mapConfig.TI[i+tdadu]);
	}
	else if (MAP->mapConfig.TI[i-tdadu]== '.') && (MAP->mapConfig.TI[i+tdadu] == '#') 
	{
		printf("%s dapat mundur. \n",p.T[giliran].nama);
		printf("%s mundur %d langkah. \n",p.T[giliran].nama, tdadu);
		printf("%s berada di petak %d. \n",p.T[giliran].nama, MAP->mapConfig.TI[i-tdadu]);
	}
	else
	{
		printf("%s dapat maju dan mundur. \n",p.T[giliran].nama);
		printf("Pilih maju/mundur \n");
		scanf(" %c", &majumundur);
		if(majumundur == "maju"){
			printf("%s maju %d langkah. \n",p.T[giliran].nama, tdadu);
			printf("%s berada di petak %d. \n",p.T[giliran].nama, MAP->mapConfig.TI[i+tdadu]);
		}
		else if(majumundur == "mundur"){
			printf("%s mundur %d langkah. \n",p.T[giliran].nama, tdadu);
			printf("%s berada di petak %d. \n",p.T[giliran].nama, MAP->mapConfig.TI[i-tdadu]);
		}
		
	}	
}
boolean F_IsPemainEmpty(T_Pemain V_Pemain)
{
    return (strcmp(V_Pemain.nama, "")==0);
}

int jumlahpemain(T_TabPemain p)
{ 
	int i;
    if (F_IsPemainEmpty) {
	  printf("0");
    }
    else {
	  return p.jmlpemain;
    }
}

void ChangeTurn(Queue *Q)
{
	infotype X;
	Del(&(*Q), &X);
	Add(&(*Q), X);
}

void statuspemain(T_TabPemain play) 
{
    int i;
    printf("****** STATUS PEMAIN ******\n");
    for(i=1;i<=4;i++)
    {
        if(strcmp("",play.T[i].nama)!=0)
        {
            printf("-----%s-----\n", play.T[i].nama);
            printf("Letak pemain di petak : %d\n", play.T[i].letak);
        }
    }
}
void pemenang (T_TabPemain play)
{
	int i;
	if(play.T[i].letak == MAP->mapConfig.Neff)//ujung map
	{
		printf("==========SELAMAT ANDA MENJADI PEMENANG DARI GAME INI!!!==========");
	}
}

