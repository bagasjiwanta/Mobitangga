#include "./adt/mesinkata/mesinkata.h"
#include "./adt/map/map.h"
#include "./functions.h"

int main(){
    Map map;
    CreateEmptyMap(&map);
    int maxroll;
    // initGame(&(map.mapLength), map.mapConfig, &maxroll, .teleporters);
    printMap(map);
}