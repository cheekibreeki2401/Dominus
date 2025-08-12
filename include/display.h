#ifndef _display_h
#define _display_h

extern choice *notAChoice;

void startTUI();
void endTUI();
void printStaticContent(int clear);
void printChoiceContent();
void printSpeakerContent();
void printItemGet();

#endif
