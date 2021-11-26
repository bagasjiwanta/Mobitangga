#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "boolean.h"

extern const char* Commands[];

int randInt(int maxDigit);

void logErrorThenExit (const char* error, const char* location);

void initGame();

void gameLoop();

void commandInspect();

void commandSkill(int playerIndex);

void commandMap();

void commandRoll();

void useSkill(int playerIndex, int skillIndex);

void movePlayer(int pIndex, int toWhere);

#endif // !__FUNCTIONS_H__ 