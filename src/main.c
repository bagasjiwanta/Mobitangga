#include "./adt/mesinkata/mesinkata.h"
#include "./adt/map/map.h"
#include "./functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Map* map = CreateEmptyMap();
    initGame(map);
    printf("%s", map->mapConfig);
    DeallocMap(map);
    return 0;
}