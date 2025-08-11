#include "sharedMacros.h"
#ifndef _flagTableManage_h
#define _flagTableManage_h

extern int size;
extern char keys[WIN_MAX][STR_MAX];
extern int flags[WIN_MAX];

int getKeyIndex(char key[]);
void newFlagValue(char key[], int value);
int getFlagValue(char key[]);

#endif
