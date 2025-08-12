#include "sharedMacros.h"
#ifndef _shared_Structs
#define _shared_Structs

typedef enum dialogueType{
	TYPE_PLAIN = 1,
	TYPE_CHOICE,
	TYPE_SPEAKER,
	TYPE_ITEM_ACQUIRED,
	TYPE_MENU,
	TYPE_COMBAT,
	TYPE_QUIT
} dialogueType;

typedef struct plainDialogue{
	int scriptId;
	char scriptName[STR_MAX];
	char text[STR_MAX];
	char nextDialogue[STR_MAX];
	dialogueType nextDialogueType;
	int displayTimeOfDialogue; //In seconds
} plainDialogue;

typedef struct choice{
	int isAChoice;
	int choiceId;
	char choiceName[STR_MAX];
	char choiceText[STR_MAX];
	int requiresFlag;
	char requiredFlagName[STR_MAX];
	char nextDialogue[STR_MAX];
	dialogueType nextDialogueType;
	int changesFlag;
	char changedFlag[STR_MAX];
	int flagValue;

} choice;

typedef struct choiceDialogue{
	int scriptId;
	char scriptName[STR_MAX];
	char text[STR_MAX];
	char availableChoices[10][STR_MAX];
} choiceDialogue;

typedef struct speakerDialogue{
	int scriptId;
	char scriptName[STR_MAX];
	char speakerName[STR_MAX];
	char colour[STR_MAX];
	char text[STR_MAX];
	int displayTimeOfDialogue;
	char nextScriptName[STR_MAX];
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


typedef struct itemAcquiredDialogue{
	int acquired_id;
	char item_acquired[STR_MAX];
	int quantity;
} itemAcquiredDialogue;

typedef enum effect_target{
	SELF,
	PARTY,
	ENEMY
} effect_target;

typedef enum effects{
	HEAL
}effects;

typedef struct gmItem{
	int item_id;
	char int_item_name[STR_MAX];
	char item_name[STR_MAX];
	effect_target item_target;
	int item_num_targets;
	effects item_effect;
	int effect_value;
} gmItem;
#endif
