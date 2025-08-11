#ifndef _shared_Structs
#define _shared_Structs

typedef enum dialogueType{
	TYPE_PLAIN = 1,
	TYPE_CHOICE,
	TYPE_SPEAKER,
	TYPE_MENU,
	TYPE_COMBAT,
	TYPE_QUIT
} dialogueType;

typedef struct plainDialogue{
	int scriptId;
	char scriptName[256];
	char text[256];
	char nextDialogue[256];
	dialogueType nextDialogueType;
	int displayTimeOfDialogue; //In seconds
} plainDialogue;

typedef struct choice{
	int isAChoice;
	int choiceId;
	char choiceName[256];
	char choiceText[256];
	int requiresFlag;
	char requiredFlagName[256];
	char nextDialogue[256];
	dialogueType nextDialogueType;
	int changesFlag;
	char changedFlag[256];
	int flagValue;

} choice;

typedef struct choiceDialogue{
	int scriptId;
	char scriptName[256];
	char text[256];
	char availableChoices[10][256];
} choiceDialogue;

typedef struct speakerDialogue{
	int scriptId;
	char scriptName[256];
	char speakerName[256];
	char colour[256];
	char text[256];
	int displayTimeOfDialogue;
	char nextScriptName[256];
	dialogueType nextScriptType;
} speakerDialogue;

typedef enum gameState{
	GM_ZERO,
	GM_MENU,
	GM_COMBAT,
	GM_OVERWORLD,
	GM_CONVERSATION,
	GM_ERROR,
	GM_FINISH
} gameState;

#endif
