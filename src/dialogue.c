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
#include "headers/flagTableManage.h"
#include "headers/stateManager.h"

plainDialogue *plainTxt;
choiceDialogue *choiceTxt;
speakerDialogue *speaker;
int newDialogueStart = 0;
char previousDialogueChain[STR_MAX];
choice *currDecisionChoices[10];
int numChoices = 0;
char lastLineUpTo[STR_MAX];
char choicesToAdd[10][STR_MAX];
int potentialChoices = 0;
int nextChoiceType = 1;
char nextChoiceName[STR_MAX];

void speakDialogue(char dialogueName[], int dialogueType);

void makeChoicesStruct(char choiceName[], int position){
	FILE *choices = fopen(choicesFilePath, "r");
	if(!choices){
		strcpy(lastLineUpTo, "Didn't get any choices\n");
		return;
	}
	char line[STR_MAX*3];
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
		int requiresFlag = 0;
		int temp_token = 0;
		while(token != NULL){
			switch (token_ctr){
				case 0:
					temp_token = atoi(token);
					break;
				case 1:
					if(!strcmp(token, choiceName)){
						next_choice->choiceId = temp_token;
						strcpy(next_choice->choiceName,token);
						next_choice->isAChoice = 1;
						isChoice = 1;
					}
					break;

				case 2:
					if(isChoice){
						strcpy(next_choice->choiceText,token);
					}
					break;

				case 3:
					if(isChoice){
						next_choice->requiresFlag = atoi(token);
						requiresFlag = atoi(token);	
					}
					break;
				case 4:
					if(isChoice && requiresFlag){
						strcpy(next_choice->requiredFlagName, token);
					}
					break;
				case 5:
					if(requiresFlag && getFlagValue(next_choice->requiredFlagName) != atoi(token)) {
						isChoice = 0;
					}
					token = strtok(NULL, "#");
					if(isChoice){
						strcpy(next_choice->nextDialogue, token);
					}
					break;
				case 6:
					if(isChoice){
						next_choice->nextDialogueType = atoi(token);
					}
					break;
				case 7:
					if(isChoice){
						next_choice->changesFlag = atoi(token);
					}
					break;
				case 8:
					if(isChoice){
						strcpy(next_choice->changedFlag, token);
					}
					break;
				case 9:
					if(isChoice){
						next_choice->flagValue = atoi(token);
					}
					break;
			}
			token_ctr++;
			token= strtok(NULL, "#");
		}
		if(isChoice){
			currDecisionChoices[position] = next_choice;
			choiceAdded = 1;
			numChoices++;
		}
	}
	fclose(choices);
	return;
}

void initializeDialogueStructs(){
	plainTxt=malloc(sizeof(plainDialogue));
	choiceTxt=malloc(sizeof(choiceDialogue));
	speaker=malloc(sizeof(speakerDialogue));
	return;
}

void speakPlain(char dialogueName[]){
	if(!strcmp(dialogueName, "EXIT") && !newDialogueStart){
		returnToPreviousDialogue();
		printStaticContent(1);
		return;
	}
	FILE *plainDialogueText = fopen(plainScriptsFilePath, "r");
	if(!plainDialogueText){
		return;
	}
	char line[STR_MAX];
	int hasDialogue = 0;
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
						if(!newDialogueStart && currentEmptyDialogue > 0 && strcmp(previousDialogues[currentEmptyDialogue-1], dialogueName)){
							newDialogueStart = 1;
							addNewPrevious(token);
						} else if(currentEmptyDialogue == 0){
							addNewPrevious(token);
							newDialogueStart = 1;
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
						strcpy(nextChoiceName, token);
					}
					break;
				case 4:
					//finish struct
					if(hasDialogue){
						plainTxt->nextDialogueType = atoi(token);
						nextChoiceType = atoi(token);
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
		fclose(plainDialogueText);
		printStaticContent(0);
	} else {
		fclose(plainDialogueText);
	}
	return;
}

void speakChoice(char dialogueName[]){
	//TODO: Dialogue choices
	FILE *choicesTextFile = fopen(choiceScriptsFilePath, "r");
	if(!choicesTextFile){
		printf("\n\nI have a choice dialogue: %s", choiceScriptsFilePath);
		return;
	}
	for(int i = 0; i < 10; i++){
		strcpy(choicesToAdd[i], "NA");
	}
	char line[STR_MAX];
	int hasDialogue = 0;
	numChoices = 0;
	potentialChoices = 0;
	while(fgets(line, sizeof(line), choicesTextFile)){	
		if(hasDialogue){
			break;
		}
		char lineToBreak[STR_MAX];
		strcpy(lineToBreak, line);
		int token_ctr = 0;
		int curr_id = 0;
		char *token = strtok(lineToBreak, "#");	
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
						strcpy(choicesToAdd[potentialChoices], token);
						potentialChoices++;
					}
			}
			token_ctr++;
			token = strtok(NULL, "#");
		}
	}
	if(hasDialogue){
		for(int i = 0; i < 10; i++){
			makeChoicesStruct(choicesToAdd[i], numChoices);
		}
		fclose(choicesTextFile);
		printChoiceContent();
	}else{		
		fclose(choicesTextFile);
	}
	return;	
}

void speakSpeaker(char dialogueName[]){
	FILE *speakerDialogueFile = fopen(speakerScriptsFilePath, "r");
	if(!speakerDialogueFile){
		strcpy(lastLineUpTo, "I have failed in getting the speaker file\n");
		return;
	}
	char line[STR_MAX*2];
	int hasDialogue = 0;
	while(fgets(line, sizeof(line), speakerDialogueFile)){
		if(hasDialogue){
			break;
		}
		char lineToBreak[STR_MAX*2];
		char flagName[STR_MAX];
		int flagValue = 0;
		int useAltText = 0;
		strcpy(lineToBreak, line);
		int token_ctr = 0;
		int curr_id = 0;
		char *token = strtok(lineToBreak, "#");
		while(token!=NULL){
			switch(token_ctr){
				case 0:
					curr_id = atoi(token);
					break;
				case 1:
					if(!strcmp(dialogueName, token)){
						hasDialogue = 1;
						strcat(lastLineUpTo, token);
						speaker->scriptId = curr_id;
						strcpy(speaker->scriptName, token);
					}
					break;
				case 2:
					if(hasDialogue){
						strcat(lastLineUpTo, token);
						strcpy(speaker->speakerName, token);
					}
					break;
				case 3:
					if(hasDialogue){
						strcpy(speaker->colour, token);
					}
					break;
				case 4:
					if(hasDialogue){
						strcpy(speaker->text, token);
					}
					break;
				case 5:
					if(hasDialogue){
						speaker->displayTimeOfDialogue = atoi(token);
					}
					break;
				case 6:
					if(hasDialogue){
						strcpy(flagName, token);
					}
					break;
				case 7:
					if(hasDialogue){
						flagValue = atoi(token);
					}
					break;
				case 8:
					if(hasDialogue && getFlagValue(flagName) == flagValue){
						useAltText = 1;
						strcpy(speaker->text, token);	
					}
					break;
				case 9:
					if(hasDialogue && !useAltText){
						strcpy(speaker->nextScriptName, token);
						strcpy(nextChoiceName, token);
					}
					break;
				case 10:
					if(hasDialogue && !useAltText){
						speaker->nextScriptType = atoi(token);
						nextChoiceType = atoi(token);
					}
					break;
				case 11:
					if(hasDialogue && useAltText){
						strcpy(speaker->nextScriptName, token);
						strcpy(nextChoiceName, token);
					}
					break;
				case 12:
					if(hasDialogue && useAltText){
						speaker->nextScriptType = atoi(token);
						nextChoiceType = atoi(token);
					}
					break;
			}
			token_ctr++;
			token = strtok(NULL, "#");
		}
	}
	if(hasDialogue){
		fclose(speakerDialogueFile);
		printSpeakerContent();
	} else {
		fclose(speakerDialogueFile);
	}
}

void speakDialogue(char dialogueName[], int dialogueType){
	if(dialogueType == 9){
		gameState finishGame = GM_FINISH;
		changedGameState(finishGame);
		return;
	}
	for(int i = 0; i < 10; i++){
		currDecisionChoices[i] = notAChoice;
	}
	currDecisionChoices[0]->isAChoice = 0;
	if(dialogueType == 1){
		speakPlain(dialogueName);
	} else if(dialogueType == 2){
		speakChoice(dialogueName);
	} else if(dialogueType == 3){
		speakSpeaker(dialogueName);
	}
	return;
}
