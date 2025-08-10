#include "sharedStructs.h"
#include "sharedMacros.h"
#ifndef _dialogue_h
#define _dialogue_h
extern plainDialogue *plainTxt;
extern choiceDialogue *choiceTxt;
extern speakerDialogue *speaker;
extern choice *currDecisionChoices[10];
extern char lastLineUpTo[STR_MAX];
extern int numChoices;
extern char nextChoiceName[STR_MAX];
extern int nextChoiceType;
extern int newDialogueStart;

void initializeDialogueStructs();
void speakPlain(char dialogueName[]);
void speakChoice(char dialogueName[]);
void speakDialogue(char dialogueName[], int dialogueType);

#endif
