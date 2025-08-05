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

void startTUI(){
	w = initscr();
	return;
}

void endTUI(){
	endwin();
	return;
}

void printStaticContent(){
	refresh();
	printw("%s\n", plainTxt->text);
	strcpy(previousDialogue[next_empty_line], plainTxt->text);
	sleep(plainTxt->displayTimeOfDialogue);
	return;
}

void printChoiceContet(){
	clear();
	for(int i; i<10; i++){
		if(previousDialogue[i] != NULL){
			printw("%s\n", previousDialogue[i]);
		} else {
			break;
		}
	}
	printw("%s\n\n", choiceTxt->text);
}
