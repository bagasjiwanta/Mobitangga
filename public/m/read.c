#include <stdio.h>

void read(){
    FILE *fp;
    int c;
    fp = fopen("./konfigurasi.txt","r");
    while(1) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         break ;
      }
      printf("%c", c);
    }
    fclose(fp);
   
}

