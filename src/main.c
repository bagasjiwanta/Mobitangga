#include "./adt/mesinkata/mesinkata.h"
#include "./adt/map/map.h"
#include "./functions.h"
#include "./adt/player/player.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    initGame();
    giveAllPlayersRandomSkill();
    giveAllPlayersRandomSkill();
    giveAllPlayersRandomSkill();
    commandMap();
    
    int temp;
    scanf("%d", &temp);
    while(temp > 0 && temp <= MAP->mapConfig.Neff){
        commandInspect(temp);
        scanf("%d", &temp);
    }

    commandSkill(1);
    commandSkill(1);
    deallocMap();
    return 0;
 }