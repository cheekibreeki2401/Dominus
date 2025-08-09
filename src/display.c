#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "headers/sharedStructs.h"
#include "headers/sharedMacros.h"
#include "headers/dialogue.h"
#include "headers/stateManager.h"
#include "headers/fileManagement.h"

WINDOW *w;
char previousDialogue[10][STR_MAX];
int next_empty_line = 0;
int currentChoice = 0;
int max_choices = 0;
choice *notAChoice;

void processInput(char input);

void setColours(){
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
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

void printStaticContent(){
	max_choices = 0;
	wattron(w, COLOR_PAIR(0));
	currentChoice = 0;
	printw("%s\n", plainTxt->text);
	strcpy(previousDialogue[next_empty_line], plainTxt->text);
	next_empty_line++;
	refresh();	
	sleep(plainTxt->displayTimeOfDialogue);
	return;
}

void printChoiceContent(){
	clear();
	wattron(w, COLOR_PAIR(0));
	max_choices = 0;
	for(int i = 0; i<10; i++){
		if(strcmp(previousDialogue[i],"\0")){
			printw("%s\n", previousDialogue[i]);
		} else {
			break;
		}
	}
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
			//TODO: Handle flag changes from dialogue
			for(int i = 0; i < 10; i++){
				strcpy(previousDialogue[i], "\0");
			}
			next_empty_line = 0;
			strcpy(nextChoiceName, currDecisionChoices[currentChoice]->nextDialogue);
			nextChoiceType = currDecisionChoices[currentChoice]->nextDialogueType;
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
	currentChoice = 0;
	printw("%s: %s\n", speaker->speakerName, speaker->text);
//	printw("%s\n", lastLineUpTo);
	strcpy(previousDialogue[next_empty_line], speaker->text);
	next_empty_line++;
	refresh();	
	sleep(speaker->displayTimeOfDialogue);
	return;
}
