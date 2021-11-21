#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../functions.h"
#include "../list/listlinier.h"
#include <time.h>
#include <string.h>

#define playerNo(x) PLAYERS.players[x-1]
#define NumOfPlayers PLAYERS.NEff


typedef struct {
    char name[21];
    int position;
    int buffs[4];
    List skills;
    int skillCount;
} Player;

typedef struct {
    int NEff;
    Player players[4];
} Players;

extern Players PLAYERS;
extern char** SkillNames;

void initPlayers(int numberOfPlayers);

void initSkillNames();

void deallocSkillNames();

void CreatePlayer(char* name, int playerIndex);

int getSkills(int playerIndex);

void givePlayersRandomSkill();

#endif // !__PLAYER_H__