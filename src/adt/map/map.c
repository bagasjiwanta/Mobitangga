#include "map.h"
#include "../array/array.h"
#include <stdio.h>
#include <stdlib.h>

Map* CreateEmptyMap(){
    return (
        (Map*) malloc (sizeof(Map))
    );
}

char* AllocMapConfig(int n){
    return (char*) malloc (sizeof(char) * n + 1);
}

int* AllocTeleporters(int m){
    return (int*) malloc (sizeof(int) * m * 2);
}

void DeallocMap(Map* map){
    free(map);
}