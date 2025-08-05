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
choiceDialogue *choiceTxt;
int newDialogueStart = 0;
char previousDialogueChain[STR_MAX];
choice currDecisionChoices[10];

int speakDialogue(char dialogueName[], int dialogueType);

void makeChoicesStruct(char choiceName[], int position){
	FILE *choices = fopen(choicesFilePath);
	if(!choices){
		return;
	}
	char line[STR_MAX];
	int choiceAdded = 0;
	while(fgets(line, sizeof(line), choices)){
		if(choiceAdded){
			break;
		}
		choice *next_choice;
		next_choice = malloc(sizeof(choice));
		char *token=strtok(line, "#");
		int token_ctr = 0;
		int isChoice = 0;
		int choiceRequiresFlag = 0
		int temp_token = 0;
		while(token != NULL){
			switch token_ctr{
				case 0:
					temp_token = atoi(token);
					break;
				case 1:
					if(!strcmp(token, choiceName)){
						next_choice->choiceId = temp_token;
						next_choice->choiceName = token;
						isChoice = 1;
					}
					break;

				case 2:
					if(isChoice){
						strcpy(next_choice->choiceText,token;
					}
					break;

				case 3:
					if(isChoice){
						choiceRequiresFlag = atoi(token);
						next_choice->requiresFlag = atoi(token);	
					}
					break;
				case 4:
					if(isChoice){
						if(choiceRequiresFlag){
							if(getKeyIndex(token) != -1 && getFlagValue(token)){
								strcpy(next_choice->requiredFlagName, token);
							} else {
								isChoice==0;
							}
						}
					}
					break;
				case 5:
					if(isChoice){
						strcpy(next_choice->nextDialogue, token);
					}
					break;
				case 6:
					if(isChoice){
						next_choice->nextDialogueType = atoi(token);
					}
					break;
			}
			token_ctr++;
			token= strtok(NULL, "#");
		}
		if(isChoice){
			currDecisionChoices[position] = next_choice;
			choiceAdded = 1;
		}
	}
	fclose(choices)
}

void initializeDialogueStructs(){
	plainTxt=malloc(sizeof(plainDialogue));
	choiceTxt=malloc(sizeof(choiceDialogue));
	return;
}

int speakPlain(char dialogueName[]){
	if(!strcmp(dialogueName, "EXIT")){
		speakDialogue(previousDialogueChain, 1);
	}
	FILE *plainDialogueText = fopen(plainScriptsFilePath, "r");
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
					break;
				case 1:
					if(!strcmp(token, dialogueName)){
						hasDialogue = 1;
						if(!newDialogueStart){
							newDialogueStart = 1;
							previousDialogueChain = dialogueName;
						}
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

				case 5:
					if(hasDialogue){
						plainTxt->displayTimeOfDialogue = atoi(token);
					}
				}
			token_ctr++;
			token = strtok(NULL, "#");
		}
	}
	if(hasDialogue){
		makeChoicesStructs();
		printStaticContent();
		fclose(plainDialogueText);
		speakDialogue(plainTxt->nextDialogue, plainTxt->nextDialogueType);	
	} else {
		fclose(plainDialogueText);
		endTUI();
	}
}

int speakChoice(char dialogueName[]){
	//TODO: Dialogue choices
	FILE *choicesTextFile = fopen(choiceScriptsFilePath, "r");
	if(!choicesTxt){
		return 1;
	}		
	char line[STR_MAX];
	int hasDialogue = 0;
	char newDialogueLine[STR_MAX] = "";
	while(fgets(line, sizeof(line), choiceScriptsFilePath)){	
		if(hasDialogue){
			break;
		}
		char *token = strtok(line, "#");
		int token_ctr = 0;
		int curr_id = 0;
		while(token!=NULL){
			switch(token_ctr){
				case 0:
					curr_id = atoi(token);
					break;
				case 1:
					if(!strcmp(dialogueName, token)){
						hasDialogue = 1;
						choiceTxt->scriptId = curr_id;
						strcpy(choiceTxt->scriptName, token);
					}
					break;
				case 2: 
					if(hasDialogue){
						strcpy(choiceTxt->text, token);
					}
					break;
				default:
					if(hasDialogue){
						makeChoices(token);
					}
			}
			token_ctr++;
			token = strtok(NULL, "#");
		}
	}
	if(hasDialogue){
		printChoiceContent();
		fclose(choicesTextFile);
	}	
}

int speakDialogue(char dialogueName[], int dialogueType){
	if(dialogueType == 1){
		speakPlain(dialogueName);
	} else if(dialogueType == 2){
		speakChoice(dialogueName);
	}
}
