#ifndef SaveAndLoadCSV_H
#define SaveAndLoadCSV_H

#include<stdlib.h>
#include "globalHeaders.h"
#include "LinkedList.h"

#define MAX_LINE_LENGTH 4096

int saveToCSV(char *fileName, struct Node *head);
void loadCSV(const char *filename);

#endif // SaveAndLoadCSV_H

