#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "../include/sharedStructs.h"
#include "../include/sharedMacros.h"
#include "../include/dialogue.h"
#include "../include/stateManager.h"
#include "../include/fileManagement.h"
#include "../include/flagTableManage.h"

WINDOW *w;
char previousDialogue[20][STR_MAX];
char previousColors[20][STR_MAX];
int next_empty_line = 0;
int currentChoice = 0;
int max_choices = 0;
choice *notAChoice;

void processInput(char input);

void setColours(){
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	return;
}

void startTUI(){
	w = initscr();
	start_color();
	notAChoice=malloc(sizeof(choice));
	notAChoice->isAChoice = 0;
	notAChoice->choiceId = 0;
	strcpy(notAChoice->choiceName,"ERROR");
	strcpy(notAChoice->choiceText,"ERROR");
	notAChoice->requiresFlag = 0;
	strcpy(notAChoice->requiredFlagName,"Error");
	strcpy(notAChoice->nextDialogue,"Error");
	notAChoice->nextDialogueType = 0;
	notAChoice->changesFlag = 0;
	strcpy(notAChoice->changedFlag,"Error");
	notAChoice->flagValue = 0;
	for(int i = 0; i < 10; i++){
		strcpy(previousDialogue[i], "\0");
	}
	setColours();
	return;
}

void endTUI(){
	endwin();
	return;
}

void printStaticContent(int clear){
	if(clear){
		clear();
		return;
	}
	max_choices = 0;
	wattron(w, COLOR_PAIR(4));
	currentChoice = 0;
	printw("%s\n", plainTxt->text);
	strcpy(previousDialogue[next_empty_line], plainTxt->text);
	strcpy(previousColors[next_empty_line], "WHITE");
	next_empty_line++;
	refresh();	
	sleep(plainTxt->displayTimeOfDialogue);
	return;
}

void printChoiceContent(){
	clear();
	max_choices = 0;
	for(int i = 0; i<10; i++){
		if(strcmp(previousDialogue[i],"\0")){
			if(!strcmp(previousColors[i],"GREEN")){
				wattron(w, COLOR_PAIR(1));
			} else if (!strcmp(previousColors[i], "RED")){
				wattron(w, COLOR_PAIR(2));
			} else if(!strcmp(previousColors[i], "BLUE")){
				wattron(w, COLOR_PAIR(3));
			} else {
				wattron(w, COLOR_PAIR(4));
			}
			printw("%s\n", previousDialogue[i]);
		} else {
			break;
		}
	}
	wattron(w, COLOR_PAIR(4));
	printw("\n\n%s\n\n", choiceTxt->text);
	for(int i = 0; i<10;i++){
		if(i == currentChoice && currDecisionChoices[i]->isAChoice){
			printw(">%s\n", currDecisionChoices[i]->choiceText);
			max_choices++;
		} else if (currDecisionChoices[i]->isAChoice){
			max_choices++;
			printw("%s\n", currDecisionChoices[i]->choiceText);
		}
	}
	char input;
	refresh();
	input = getch();
	processInput(input);
	return;
}

void processInput(char input){
	switch(input){
		case '\n':
		case ' ':
			clear();
			for(int i = 0; i < 20; i++){
				strcpy(previousDialogue[i], "\0");
				strcpy(previousColors[i], "\0");
			}
			next_empty_line = 0;
			strcpy(nextChoiceName, currDecisionChoices[currentChoice]->nextDialogue);
			nextChoiceType = currDecisionChoices[currentChoice]->nextDialogueType;
			newDialogueStart = 0;
			if(currDecisionChoices[currentChoice]->changesFlag){
				newFlagValue(currDecisionChoices[currentChoice]->changedFlag, currDecisionChoices[currentChoice]->flagValue);	
			}
			return;
			break;
		case 's':
			if(currentChoice<max_choices-1){
				currentChoice++;
			}
			break;
		case 'w':
			if(currentChoice>0){
				currentChoice--;
			}
			break;
	}
	printChoiceContent();
}

void printSpeakerContent(){
	max_choices = 0;
	if(!strcmp(speaker->colour,"GREEN")){
		wattron(w, COLOR_PAIR(1));
	} else if(!strcmp(speaker->colour,"RED")){
		wattron(w, COLOR_PAIR(2));
	} else if(!strcmp(speaker->colour, "BLUE")){
		wattron(w, COLOR_PAIR(3));
	} else {
		wattron(w, COLOR_PAIR(0));
	}
	char fullLine[STR_MAX];
	strcpy(fullLine, speaker->speakerName);
	strcat(fullLine, ": ");
	strcat(fullLine, speaker->text);
	currentChoice = 0;
	printw("%s\n", fullLine);
	strcpy(previousDialogue[next_empty_line], fullLine);
	strcpy(previousColors[next_empty_line], speaker->colour);
	next_empty_line++;
	strcpy(nextChoiceName, speaker->nextScriptName);
	nextChoiceType = speaker->nextScriptType;
	newDialogueStart = 0;
	refresh();	
	sleep(speaker->displayTimeOfDialogue);
	return;
}

void printItemGet(){
	clear();
	max_choices = 0;
	wattron(w, COLOR_PAIR(0));
	char fullLine[STR_MAX];
	strcpy(fullLine, "You have found ");
	FILE *itemNameFile = fopen(itemNameFilePath, "r");
	char itemName[STR_MAX];
	if(!itemNameFile){
		return;
	}
	char line[STR_MAX*2];
	int foundItemName = 0;
	while(fgets(line, sizeof(line), itemNameFile)){
		if(foundItemName){
			break;
		}
		char line_cpy[STR_MAX*2];
		strcpy(line_cpy, line);
		char *token = strtok(line_cpy, "#");
		while(token!=NULL){
			if(!strcmp(itemAcq->item_acquired, token)){
				token = strtok(NULL, "#");
				strcpy(itemName, token);
				foundItemName = 1;
			} else {
				break;
			}
		}
	}
	fclose(itemNameFile);
	if(foundItemName){
		strcat(fullLine, itemName);
		strcat(fullLine, "x");
		char quantStr[10];
		sprintf(quantStr, "%d", itemAcq->quantity);
		strcat(fullLine, quantStr);
		printw("%s\n\n\n>OK\n", fullLine);
		refresh();
		getch();
		strcpy(nextChoiceName, "EXIT");
		nextChoiceType = 1;
		newDialogueStart = 0;
		//TODO: Add the new item to our inventory
		return;
	} else {
		exit(1);
		return;
	}
}
