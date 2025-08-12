#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "../include/fileManagement.h"
#include "../include/sharedMacros.h"
#include "../include/flagTableManage.h"
#include "../include/sharedStructs.h"
#include "../include/display.h"
#include "../include/dialogue.h"


gameState curr_state = GM_ZERO;
char previousDialogues[20][STR_MAX];
int currentEmptyDialogue = 0;

void changedGameState(gameState newState){
	curr_state = newState;
	return;
}

void assignGameFlags(){
	FILE *flagsFile = fopen(flagFilePath, "r");
	if(!flagsFile){
		return;
	}
	char line[STR_MAX];
	while(fgets(line, sizeof(line), flagsFile)){
		char *token = strtok(line, "#");
		if(token!=NULL){
			char key[STR_MAX];
			strcpy(key, token);
			token = strtok(NULL, "#");
			int value = atoi(token);
			newFlagValue(key, value);	
		}		
	}
	fclose(flagsFile);
	return;
}

void popDialogue(int startingPop){
	for(int i = startingPop; i < 19; i++){
		strcpy(previousDialogues[i], previousDialogues[i+1]);
	}
	return;
}

void returnToPreviousDialogue(){
	if(currentEmptyDialogue == 0){
		endTUI();
		exit(1);//Gives a clear sign when hitting outside of boundaries
	}
	strcpy(nextChoiceName, previousDialogues[currentEmptyDialogue-1]);
	nextChoiceType = 1;
	newDialogueStart = 0;
	currentEmptyDialogue--;
	popDialogue(currentEmptyDialogue);
	if(currentEmptyDialogue == 0){
		endTUI();
		exit(1);
	}
	return;
}

void addNewPrevious(char dialogueName[]){
	if(currentEmptyDialogue == 19){
		popDialogue(0);	
		currentEmptyDialogue--;
	}
	strcpy(previousDialogues[currentEmptyDialogue], dialogueName);
	currentEmptyDialogue++;
	return;
}
