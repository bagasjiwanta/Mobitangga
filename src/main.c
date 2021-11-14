#include "./adt/mesinkata/mesinkata.h"
#include "./adt/map/map.h"
#include "./functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    initMap();
    initGame();
    displayMapForDebugging();
    deallocMap();
    return 0;
}