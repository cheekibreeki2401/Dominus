#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "headers/sharedStructs.h"
#include "headers/sharedMacros.h"
#include "headers/dialogue.h"
#include "headers/stateManager.h"

WINDOW *w;
char previousDialogue[10][STR_MAX];
int next_empty_line = 0;
int currentChoice = 0;
int max_choices = 0;

void processInput(unsigned int input);

void startTUI(){
	w = initscr();
	return;
}

void endTUI(){
	endwin();
	return;
}

void printStaticContent(){
	memset(currDecisionChoices, 0, sizeof(currDecisionChoices));
	max_choices = 0;
	currentChoice = 0;
	refresh();
	currentChoice = 0;
	printf("I should be seeing %s\n", plainTxt->text);
	printw("%s\n", plainTxt->text);
	strcpy(previousDialogue[next_empty_line], plainTxt->text);
	next_empty_line++;
	printf("Does this appear?\n");
	sleep(plainTxt->displayTimeOfDialogue);
}

void printChoiceContent(){
	clear();
	max_choices = 0;
	for(int i; i<10; i++){
		if(previousDialogue[i] != NULL){
			printw("%s\n", previousDialogue[i]);
		} else {
			break;
		}
	}
	printw("%s\n\n", choiceTxt->scriptName);
	for(int i; i<sizeof(currDecisionChoices)/sizeof(choice);i++){
		max_choices++;
		if(i == currentChoice){
			printw(">%s\n", currDecisionChoices[i].choiceText);
		} else {
			printw("%s\n", currDecisionChoices[i].choiceText);
		}
	}
	unsigned int input;
	input = getch();
	processInput(input);
	return;
}

void processInput(unsigned int input){
	switch(input){
		case '\n':
		case ' ':
			//TODO: Handle flag changes from dialogue
			memset(previousDialogue, 0, sizeof(previousDialogue));
			next_empty_line = 0;
			speakDialogue(currDecisionChoices[currentChoice].nextDialogue, currDecisionChoices[currentChoice].nextDialogueType);
			break;
		case KEY_DOWN:
			if(currentChoice<max_choices-1){
				currentChoice++;
			}
			break;
		case KEY_UP:
			if(currentChoice>0){
				currentChoice--;
			}
			break;
	}
	printChoiceContent();
}
