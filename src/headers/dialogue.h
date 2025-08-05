#include "sharedStructs.h"
#ifndef _dialogue_h
#define _dialogue_h
extern plainDialogue *plainTxt;
extern choiceDialogue *choiceTxt;
extern choice currDecisionChoices[10];
void initializeDialogueStructs();
int speakPlain(char dialogueName[]);
int speakChoice(char dialogueName[]);
int speakDialogue(char dialogueName[], int dialogueType);

#endif
