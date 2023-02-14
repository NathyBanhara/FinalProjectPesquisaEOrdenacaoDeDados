#include <stdio.h>
#include "agenda.h"

FILE *openFile();
void closeFile(FILE *file);
void writeOnFile(AgendaNode *root, FILE *file);
AgendaNode *readFile(AgendaNode *root);