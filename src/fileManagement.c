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
#include "../include/sharedMacros.h"

const int MAX_SAVES = 100;

char plainScriptsFilePath[LINUX_MAX];
char choiceScriptsFilePath[LINUX_MAX];
char choicesFilePath[LINUX_MAX];
char flagFilePath[LINUX_MAX];
char speakerScriptsFilePath[LINUX_MAX];
char acquiredItemFilePath[LINUX_MAX];
char itemNameFilePath[LINUX_MAX];
char saveFilePath[LINUX_MAX];
char menuFilePath[LINUX_MAX];
int cur_saves = 0;
int loadedSaves = 0;
char **saveFileNames;
char saveFileToLoad[LINUX_MAX];


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
		return 0;
	}
}

char *getSaveFileToLoad(int i){
	strcpy(saveFileToLoad, saveFileNames[i]);
	return saveFileToLoad;
}

char **getSaveFiles(const char* restrict directory){
	if(!isFolderCreated(directory)){
		return NULL;	
	}
	if(loadedSaves){
		return saveFileNames;
	}
	saveFileNames = (char **)malloc(MAX_SAVES * sizeof(char*));
	for(int i = 0; i < MAX_SAVES; i++){
		saveFileNames[i] = malloc(STR_MAX * sizeof(char));
	}
	DIR *dir = opendir(directory);
	struct dirent *entry;
	while((entry = readdir(dir)) != NULL){
		if(strstr(entry->d_name, ".txt") && cur_saves <= MAX_SAVES){
			strcpy(saveFileNames[cur_saves], entry->d_name);
			cur_saves += 1;
		}
	}
	if(cur_saves > 0){
		loadedSaves = 1;
		return saveFileNames;
	}
	return NULL;
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
	strcpy(speakerScriptsFilePath, fullDirectory);
	strcpy(acquiredItemFilePath, fullDirectory);
	strcpy(itemNameFilePath, fullDirectory);
	strcpy(menuFilePath, fullDirectory);
	strcpy(saveFilePath, fullDirectory);
	strcat(plainScriptsFilePath, "/story_data/en_UK/script_data/plain.txt");
	strcat(choiceScriptsFilePath,"/story_data/en_UK/script_data/choiceScripts.txt");
	strcat(choicesFilePath,"/story_data/en_UK/script_data/choices.txt");
	strcat(speakerScriptsFilePath, "/story_data/en_UK/script_data/conversations.txt");
	strcat(flagFilePath, "/game_data/FLAGS/storyFlags.txt");
	strcat(acquiredItemFilePath, "/story_data/en_UK/script_data/item_get.txt");
	strcat(itemNameFilePath, "/game_data/Items/en_UK/itemsNamesDesc.txt");
	strcat(menuFilePath, "/game_data/menu/en_UK/menu.txt");
	strcat(saveFilePath, "/saves");
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
