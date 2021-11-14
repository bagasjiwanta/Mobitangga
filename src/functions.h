#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

void logErrorThenExit (const char* error, const char* location);

void initGame (Map* map);

void readConfig (const char* fileloc, Map* map);

#endif // !__FUNCTIONS_H__ 