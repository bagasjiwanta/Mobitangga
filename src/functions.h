#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

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

#endif // !__FUNCTIONS_H__ 