#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/fileManagement.h"
#include "../include/sharedMacros.h"
#include "../include/dialogue.h"
#include "../include/display.h"
#include "../include/stateManager.h"

int main(){
	getDocumentsFolder();
	initializeDialogueStructs();
	startTUI();
	assignGameFlags();
	strcpy(nextChoiceName, "welcome");
	gameState initState = GM_MENU;
	changedGameState(initState);
	while(curr_state != GM_FINISH){
		speakDialogue(nextChoiceName, nextChoiceType);
	}
	endTUI();
	return 0;
}
