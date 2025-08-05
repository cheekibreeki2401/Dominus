#include <stdio.h>
#include <string.h>

int size=0;
char keys[WIN_MAX][STR_MAX];
int values[WIN_MAX];

int getKeyIndex(char key[]){
	for(int = 0; i < size; i++){
		if(!strcmp(keys[i], key)){
			return i;
		}
	}
	return -1;
}

void newFlagValue(char key[], int value){
	int flagIndex = getKeyIndex(key)
	if(flagIndex==-1){
		strcpy(keys[size],key);
		values[size] = value;
		size++;
	} else {
		values[flagIndex] = value;
	}
}

int getFlagValue(char key[]){
	int flagIndex = getKeyIndex(key)
	if(flagIndex == -1){
		return -1;
	} else {
		return values[flagIndex];
	}
}


