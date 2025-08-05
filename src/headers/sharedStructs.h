#ifndef _shared_Structs
#define _shared_Structs

typedef struct plainDialogue{
	int scriptId;
	char scriptName[256];
	char text[256];
	char nextDialogue[256];
	int nextDialogueType;//1: plain, 2: choice, 3: characters
	int displayTimeOfDialogue; //In seconds
} plainDialogue;

typedef struct choice{
	int choiceId;
	char choiceName[256];
	char choiceText[256];
	int requiresFlag;
	char requiredFlagName[256];
	char nextDialogue[256];
	int nextDialogueType;
} choice;

typedef struct choiceDialogue{
	int scriptId;
	char scriptName[256];
	char text[256];
	char availableChoices[10][256];
} choiceDialogue;

enum gameState{
	GM_ZERO;
	GM_MENU;
	GM_COMBAT;
	GM_OVERWORLD;
	GM_CONVERSATION;
	GM_ERROR;
} gameState;

#endif
