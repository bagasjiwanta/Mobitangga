#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "boolean.h"
#include "./adt/stack/stack.h"

#define Name(x) GAME->playerNames[x-1]
#define NameNow GAME->playerNames[GAME->whoseTurn - 1]
#define Round(x) GAME->GameStack->round[x]

typedef struct {
    int whoseTurn;
    int ronde;
    int numOfPlayers;
    boolean isTurnEnd;
    boolean isCerminUsed;
    boolean isSenterUsed;
    boolean isRolled;
    char inputCommand[15];
    int givenSkill;
    char** playerNames;
    Stack* GameStack;
} Game;

extern Game* GAME;
extern const char* Commands[];

int randInt(int maxDigit);

void logErrorThenExit (const char* error, const char* location);

void printPosisiTiapPemain(int round);

infotypeStack FirstRound();

void initGame();

void gameLoop();

void commandInspect();

void commandSkill(int playerIndex);

void commandMap();

void commandRoll();

void useSkill(int playerIndex, int skillIndex);

void movePlayer(int pIndex, int toWhere);

#endif // !__FUNCTIONS_H__ 