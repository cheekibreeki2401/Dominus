#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "headers/sharedStructs.h"
#include "headers/sharedMacros.h"
#include "headers/dialogue.h"

WINDOW *w;
char previousDialogue[STR_MAX][10];
int next_empty_line = 0;

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
