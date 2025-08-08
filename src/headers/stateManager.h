#include "sharedStructs.h"
#ifndef _stateManager_h
#define _stateManager_h

extern gameState curr_state;

void changedGameState(gameState newState);
void assignGameFlags();

#endif
