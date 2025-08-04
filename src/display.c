#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "headers/sharedStructs.h"
#include "headers/dialogue.h"

void printStaticContent(){
	WINDOW *w;
	char input;
	w=initscr();
	refresh();
	printw("%s\n", plainTxt->text);
	input = getch();
	endwin();
	return;
}
