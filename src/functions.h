#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "boolean.h"
#include "./adt/stack/stack.h"

#define Name(x) GAME->playerNames[x-1]
#define NameNow GAME->playerNames[GAME->whoseTurn - 1]
#define Round(x) GAME->GameStack->round[x]
#define PlayerNow(x) GAME->GameStack->round[GAME->GameStack->TOP].player[x-1]
#define TopGame GAME->GameStack->TOP

// deklarasi adt game
typedef struct {
    int whoseTurn;
    int ronde;
    int numOfPlayers;
    boolean isTurnEnd;
    boolean isCerminUsed;
    boolean isSenterUsed;
    boolean isRolled;
    boolean isUndoUsed;
    int undoTries;
    char inputCommand[15];
    int givenSkill;
    char** playerNames;
    Stack* GameStack;
} Game;

// nama nama command
extern const char* Commands[];

// nama nama skill
extern const char* SkillNames[];

// nama nama buff
extern const char* BuffNames[];

// konfigurasi game, berisi seluruh variable yang krusial untuk game
extern Game* GAME;

// mengalokasikan adt game
void SetupGame(int numberOfPlayers);

// mengeluarkan posisi tiap pemain untuk debugging
void printPosisiTiapPemain();

// menghasilkan gamestack awal, dimana buff tidak ada, posisi 1, dan skill empty
infotypeStack FirstRound();

// mengcopy gamestack sebelumnya dan mereturn
infotypeStack NewRound();

// mengembalikan random number dari 0 sampai maxDigit - 1 secara inklusif
int randInt(int maxDigit);

// mengeluarkan error, lalu program exit
void logErrorThenExit (const char* error, const char* location);

// memulai game, meminta nama file konfigurasi, meminta jumlah dan nama pemain
// mengeset seed untuk random number
void initGame();

// mereset semua buff kecuali buff imunitas teleport untuk tiap player
void resetBuff();

// menampilkan map dan posisi masing masing player di map itu
void commandMap();

// memakai skill
// pIndex adalah index pemain, skillIndex adalah index skill 
// misalnya useSkill(1, 2) => pemain pertama memakai skill cermin pengganda
void useSkill(int pIndex, int skillIndex);

// command skill, menampilkan skill terlebih dahulu lalu meminta input
// apakah ingin memakai skill atau membuang skill
void commandSkill(int pIndex);

// mengecek buff sendiri
void commandBuff(int pIndex);

// melakukan inspect terhadap 1 petak
void commandInspect();

// roll pemain
void commandRoll(int pIndex);

// memindahkan pemain untuk keperluan roll
void movePlayer(int pIndex, int toWhere);

// dealokasi game
void deallocGame();

// prosedur endgame dimana ditampilkan pemenang dan posisinya
void endGame();

// mengecek apakah pemain yang sedang bergerak mencapai ujung map
boolean checkForWinner();

// melakukan undo
void commandUndo();

// memberikan pemain di index pIndex sebuah skill random
// mereturn index skill
int givePlayerRandomSkill(int pIndex);

// game loop utama
void gameLoop();

#endif // !__FUNCTIONS_H__ 