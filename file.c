#include <stdlib.h>
#include "file.h"

FILE *openFile()
{
    FILE *file = fopen("data.txt", "w+");
    if (file == NULL)
    {
        printf("There was a problem opening the file!\n");
        return NULL;
    }
    return file;
}

void closeFile(FILE *file)
{
    int close = fclose(file);
    if (close != 0) printf("There was a problem closing the file!\n");
}

void writeOnFile(AgendaNode *root, FILE *file)
{   
    AgendaNode *aux = root;
    if (checksIfEmpty(root)) return;
    writeOnFile(root->left, file);
    fwrite(aux, sizeof(AgendaNode), 1, file);
    writeOnFile(root->right, file);
}

AgendaNode *readFile(AgendaNode *root)
{
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) return NULL;
    int i = 1;
    while(i)
    {
        AgendaNode *newPerson = (AgendaNode*)malloc(sizeof(AgendaNode));
        i = fread(newPerson, sizeof(AgendaNode), 1, file);
        if (!i)
        {
            closeFile(file);
            return root;
        }
        newPerson->right = NULL;
        newPerson->left = NULL;
        root = insContact(newPerson, root);
    }
    closeFile(file);
    return root;
}

