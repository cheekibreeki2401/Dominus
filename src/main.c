#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "headers/fileManagement.h"
#include "headers/sharedMacros.h"

int main(){
	char filePath[LINUX_MAX];
	strcpy(filePath, getDocumentsFolder());
	if(filePath == "ERROR: NO VALID USER"){
		printf("%s\n", filePath);
		return 1;
	}
	printf("%s\n", filePath);
	if(isFolderCreated(filePath) == 1){
		printf("Glad that you have a documents folder\n");
	}
	strcat(filePath, "Dominus_Legends");
	if(isFolderCreated(filePath) == ERR_NA){
		printf("This folder is still under construction for game data\nExiting\n");
	}	
	return 0;
}
