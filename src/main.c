#include "./adt/mesinkata/mesinkata.h"
#include "./adt/map/map.h"
#include "./functions.h"
#include "./adt/player/player.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    initGame();
    /*

        Game Loop disini

    */
    // displayMapForDebugging();
    initSkillNames();
    int i;
    for(i=0;i<6;i++){
        printf("%s\n", SkillNames[i]);
    }
    printf("%s", PLAYERS.players[0].name);
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    givePlayersRandomSkill();
    i = getSkills(1);
    printf("\n(%d)", i);
    deallocSkillNames();
    deallocMap();
    return 0;
}