#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "headers/fileManagement.h"
#include "headers/sharedMacros.h"
#include "headers/dialogue.h"
#include "headers/display.h"

int main(){
	getDocumentsFolder();
	initializeDialogueStructs();
	startTUI();
	printf("%s\n", plainScriptsFilePath);
	speakDialogue("welcome", 1);
	return 0;
}
