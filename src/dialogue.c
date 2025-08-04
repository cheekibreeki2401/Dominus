#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "headers/fileManagement.h"
#include "headers/sharedMacros.h"
#include "headers/sharedStructs.h"
#include "headers/display.h"

plainDialogue *plainTxt;


int speakPlain(char dialogueName[]){
	FILE *plainDialogueText = fopen(plainScriptsFilePath, "r");
	plainTxt=malloc(sizeof(plainDialogue));
	if(!plainDialogueText){
		printf("No dialogue text found\n");
		return 1;
	}
	char line[STR_MAX];
	int hasDialogue = 0;
	char newDialogueLine[STR_MAX] = "";
	while(fgets(line, sizeof(line), plainDialogueText)){
		if(hasDialogue){
			break;
		}
		char *token = strtok(line, "#");
		int token_ctr = 0;
		int curr_id = 0;
		while(token!=NULL){
			switch (token_ctr){
				case 0:
					curr_id = atoi(token);
					printf("%i\n", curr_id);
					break;
				case 1:
					if(!strcmp(token, dialogueName)){
						hasDialogue = 1;
						plainTxt->scriptId = curr_id;
						strcpy(plainTxt->scriptName, token);
					}
					break;
				case 2:
					if(hasDialogue){
						strcpy(plainTxt->text, token);
					}
					break;
				case 3:
					//finish struct
					if(hasDialogue){
						strcpy(plainTxt->nextDialogue, token);
					}
					break;
				case 4:
					//finish struct
					if(hasDialogue){
						plainTxt->nextDialogueType = atoi(token);
					}
					break;
				}
			token_ctr++;
			token = strtok(NULL, "#");
		}
	}
	if(hasDialogue){
		printStaticContent();	
	}
	fclose(plainDialogueText);
}

int speakChoice(char dialogueName[]){
	//TODO: Dialogue choices
}

int speakDialogue(char dialogueName[], int dialogueType){
	if(dialogueType == 1){
		speakPlain(dialogueName);
	} else if(dialogueType == 2){
		speakChoice(dialogueName);
	}
}
