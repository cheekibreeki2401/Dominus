#include "sharedMacros.h"
#ifndef _fileManagement_h
#define _fileManagement_h
extern char plainScriptsFilePath[LINUX_MAX];
extern char choiceScriptsFilePath[LINUX_MAX];
extern char choicesFilePath[LINUX_MAX];
extern char flagFilePath[LINUX_MAX];
extern char speakerScriptsFilePath[LINUX_MAX];
extern char acquiredItemFilePath[LINUX_MAX];
extern char itemNameFilePath[LINUX_MAX];
char *getUserName();
int isFolderCreated(char filepath[]);
int *getDocumentsFolder();
int installFiles();

#endif
