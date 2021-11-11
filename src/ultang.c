void turn(player p, int *dadu, boolean *issudahkocok, int i)
{   //melakukan turn, seperti mengocok dadu
    //kamus
    int giliran, tdadu; 
    char pilihan;
    //algoritma
    printf("-----Turn %d-----\n", i);
    giliran=((i-1)%p.jmlpemain)+1; //mencari giliran siapa
    printf("Giliran : %s\n", p.pem[giliran].nama);
    printf("tekan untuk mengocok dadu!");
    if(!(*issudahkocok)) //jika belum ngocok
    {   // melakukan pengocokan dadu
        scanf(" %c", &pilihan);
        *dadu = rand()% 6 + 1;
        //(*p).pem[giliran].lokasi=((*p).pem[giliran].lokasi+*tdadu)%20;
        *issudahkocok=true;
    }
    tdadu=*dadu
    //menampilkan dadu
    printf("\nDadu 1 : %d\n", *dadu);
    printf("%s maju sebanyak %d langkah\n", p.pem[giliran].nama, tdadu);
}

