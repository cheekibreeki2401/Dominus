#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "headers/fileManagement.h"
#include "headers/sharedMacros.h"
#include "headers/dialogue.h"
#include "headers/display.h"
#include "headers/stateManager.h"

int main(){
	getDocumentsFolder();
	initializeDialogueStructs();
	startTUI();
	strcpy(nextChoiceName, "welcome");
	gameState initState = GM_MENU;
	changedGameState(initState);
	while(curr_state != GM_FINISH){
		speakDialogue(nextChoiceName, nextChoiceType);
	}
	endTUI();
	return 0;
}
