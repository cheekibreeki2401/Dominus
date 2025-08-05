#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "headers/fileManagement.h"
#include "headers/sharedMacros.h"
#include "headers/flagTableManage.h"
#include "headers/sharedStructs.h"


gameState curr_state = GM_ZERO;

void changeGameState(gameState newState){
	curr_state = newState;
	return;
}

void assignGameFlags(){
	FILE *flagsFile = fopen(flagFilePath, "r");
	if(!flagsFile){
		return;
	}
	char line[STR_MAX];
	int lineCounter = 0;
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
}
