#include "date.h"

struct agenda
{
    char name[30];
    Date birth; 
    char email[40];
    char phone[15];
};

struct agendaNode
{
    struct agenda info;
    struct agendaNode *left, *right;
};

typedef struct agenda Agenda;
typedef struct agendaNode AgendaNode;

void breaking();
int comparesNames(char nameNode[30], char nameInsert[30]);
int checksIfEmpty(AgendaNode *root);
AgendaNode *freeMemory(AgendaNode *root);
void listContacts(AgendaNode *root);
void queryContact(AgendaNode *root);
AgendaNode *rrRotation(AgendaNode *root);
AgendaNode *llRotation(AgendaNode *root);
AgendaNode *lrRotation(AgendaNode *root);
AgendaNode *rlRotation(AgendaNode *root);
int leftHeight(AgendaNode *root);
int rightHeight(AgendaNode *root);
int height(AgendaNode *root);
int checksBalance(AgendaNode *root);
AgendaNode *sideToBalance(AgendaNode *root);
AgendaNode *searching(AgendaNode *root, char name[30]);
AgendaNode *modifyEmail(AgendaNode *aux, AgendaNode *root);
AgendaNode *modifyPhone(AgendaNode *aux, AgendaNode *root);
AgendaNode *modifyName(AgendaNode *aux, AgendaNode *root);
AgendaNode *modifyBirthday(AgendaNode *aux, AgendaNode *root);
AgendaNode *upContact(AgendaNode *root);
int checksBirthday(int day, int month, int year);
int checksEmail(char email[40]);
AgendaNode *newOne(AgendaNode *root);
AgendaNode *insContact (AgendaNode *newly, AgendaNode *root);
AgendaNode *minNode(AgendaNode *root);
AgendaNode *delContact (AgendaNode *root, char name[30]);
AgendaNode *mainDelete(AgendaNode *root);
void menuPage();
