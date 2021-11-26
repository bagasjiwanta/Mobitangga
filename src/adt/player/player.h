#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../functions.h"
#include "../list/listlinier.h"
#include "../../boolean.h"
#include <time.h>
#include <string.h>

#define pNo(x) PLAYERS.players[x-1]
#define NumOfPlayers PLAYERS.NEff

typedef struct {
    char name[21];
    int position;
    boolean buffs[4]; // {false, false, false, false}
    List skill;
    int skillCount;
} Player;

typedef struct {
    int NEff;
    Player players[4];
} Players;

extern Players PLAYERS;
extern const char* SkillNames[];
extern const char* BuffNames[];

void initPlayers(int numberOfPlayers);

void CreatePlayer(char* name, int playerIndex);

int givePlayerRandomSkill(int pIndex);

#endif // !__PLAYER_H__