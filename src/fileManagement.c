#include <stdio.h>
#ifdef __linux__
	#include <pwd.h>
#elif _WIN32
	#include <windows.h>
#endif
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <curl/curl.h>
#include <zip.h>
#include <string.h>
#include "headers/sharedMacros.h"

char plainScriptsFilePath[LINUX_MAX];
char choiceScriptsFilePath[LINUX_MAX];
char choicesFilePath[LINUX_MAX];
char flagFilePath[LINUX_MAX];

const char *getUserName(){
	#ifdef __linux__
		uid_t uid = geteuid();
		struct passwd *pw = getpwuid(uid);
		if(pw){
			return pw->pw_name;
		} else {
			return "ERR_NO_NAME";
		}
	#elif _WIN32
		return getenv("USERNAME");
	#endif
}

int isFolderCreated(const char* restrict directory){
	DIR *dir = opendir(directory);
	if(dir){
		closedir(dir);
		return 1;
	} else {
		closedir(dir);
		return ERR_NA;
	}
}

int getDocumentsFolder(){
	#ifdef __linux__
		char fullDirectory[LINUX_MAX]="";
		strcat(fullDirectory, "/home/");
	#elif _WIN32
		char fullDirectory[WIN_MAX];
		strcat(fullDirectory, "C:/User/");
	#endif
	char userName[STR_MAX]="";
	if(strcmp(getUserName(),"ERR_NO_NAME")!=0){
		strcat(userName, getUserName());
		strcat(fullDirectory, userName);
		strcat(fullDirectory, "/Documents/Dominus/data");
	} else {
		return 1;
	}
	strcpy(plainScriptsFilePath, fullDirectory);
	strcpy(choiceScriptsFilePath, fullDirectory);
	strcpy(choicesFilePath, fullDirectory);
	strcpy(flagFilePath, fullDirectory);
	strcat(plainScriptsFilePath, "/story_data/en_UK/script_data/plain.txt");
	strcat(choiceScriptsFilePath,"/story_data/en_UK/script_data/choiceScripts.txt");
	strcat(choicesFilePath,"/story_data/en_UK/script_data/choices.txt");
	strcat(flagFilePath, "/game_data/FLAGS/storyFlags.txt");
	return 0;
}

int installFiles(){
	//TODO: Create game data files, zipped on GitHub in a release and have them install on first launch of the program.
	return 1;
}

int isFileCreated(const char* restrict filepath){
	FILE *file = fopen(filepath, "rb");
	if(file == NULL){
		return 0;
	} else {
		fclose(file);
		return 1;
	}
}
