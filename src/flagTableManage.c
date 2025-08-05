#include <stdio.h>
#include <string.h>
#include "headers/sharedMacros.h"
int size=0;
char keys[WIN_MAX][STR_MAX];
int flags[WIN_MAX];

int getKeyIndex(char key[]){
	for(int i = 0; i < size; i++){
		if(!strcmp(keys[i], key)){
			return i;
		}
	}
	return -1;
}

void newFlagValue(char key[], int value){
	int flagIndex = getKeyIndex(key);
	if(flagIndex==-1){
		strcpy(keys[size],key);
		flags[size] = value;
		size++;
	} else {
		flags[flagIndex] = value;
	}
}

int getFlagValue(char key[]){
	int flagIndex = getKeyIndex(key);
	if(flagIndex == -1){
		return -1;
	} else {
		return flags[flagIndex];
	}
}


