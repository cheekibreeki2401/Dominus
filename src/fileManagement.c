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

const char *getDocumentsFolder(){
	#ifdef __linux__
		char fullDirectory[LINUX_MAX];
		char *dir_ptr = fullDirectory;
		strcat(fullDirectory, "/home/");
	#elif _WIN32
		char fullDirectory[WIN_MAX];
		char *dir_ptr = fullDirectory;
		strcat(fullDirectory, "C:/User/");
	#endif
	char userName[STR_MAX];
	if(strcmp(getUserName(),"ERR_NO_NAME")!=0){
		strcat(userName, getUserName());
		strcat(fullDirectory, userName);
		strcat(fullDirectory, "/Documents");
	} else {
		return "ERROR: NO VALID USER";
	}
	return dir_ptr;
}

int installFiles(){
	//TODO: Create game data files, zipped on GitHub in a release and have them install on first launch of the program.
	return 1;
}
