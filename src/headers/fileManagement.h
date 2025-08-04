#include "sharedMacros.h"
#ifndef _fileManagement_h
#define _fileManagement_h
extern char plainScriptsFilePath[LINUX_MAX];
char *getUserName();
int isFolderCreated(char filepath[]);
int *getDocumentsFolder();
int installFiles();

#endif
