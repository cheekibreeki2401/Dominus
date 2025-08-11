#include "sharedStructs.h"
#include "sharedMacros.h"
#ifndef _stateManager_h
#define _stateManager_h

extern gameState curr_state;
extern char previousDialogues[20][STR_MAX];
extern int currentEmptyDialogue;

void changedGameState(gameState newState);
void assignGameFlags();

void popDialogue(int startingPop);
void returnToPreviousDialogue();
void addNewPrevious(char dialogueName[]);

#endif
