#include <stdlib.h>
#include <string.h>
#include "file.h"

//Functions related to AVL were inspired by Denio's code

void breaking()
{
    printf("--------------------------------\n");
}

int checksIfEmpty(AgendaNode *root)
{
    if (root == NULL) return 1;
    return 0;
}

AgendaNode *freeMemory(AgendaNode *root)
{ //posOrder
    if (!checksIfEmpty(root))
    {
        freeMemory(root->left);
        freeMemory(root->right);
        free(root);
    }
    return NULL;
}

int comparesNames(char nameNode[30], char nameInsert[30])
{
    if (strcmp(nameNode, nameInsert) == 0) return -1;
    for (int i = 0; i < 29; i++)
    {
        if (nameNode[i] > nameInsert[i]) return 1;
        else if (nameInsert[i] > nameNode[i]) return 2;
    }
    return 1;
}

void listContacts(AgendaNode *root)
{ //prints in order
    if (checksIfEmpty(root)) return;
    listContacts(root->left);
    printf("Name: %s\n", root->info.name);
    printf("Birthday: %d/%d/%d\n", root->info.birth.day, root->info.birth.month, root->info.birth.year);
    printf("Email: %s\n", root->info.email);
    printf("Phone Number: %s\n", root->info.phone);
    breaking();
    listContacts(root->right);
}

void queryContact(AgendaNode *root)
{
    char name[30];
    AgendaNode *person;
    printf("Name: ");
    scanf("%s", name);
    person = searching(root, name);
    breaking();
    if (checksIfEmpty(person))
        printf("This person does not exist!\n");
    else
    {
        printf("Name: %s\n", person->info.name);
        printf("Birthday: %d/%d/%d\n", person->info.birth.day, person->info.birth.month, person->info.birth.year);
        printf("Email: %s\n", person->info.email);
        printf("Phone Number: %s\n", person->info.phone);
    }
    return;
}

AgendaNode *rrRotation(AgendaNode *root)
{
    AgendaNode *aux = root;
    root = root->right;
    aux->right = root->left;
    root->left = aux;
    return root;
}

AgendaNode *llRotation(AgendaNode *root)
{
    AgendaNode *aux = root;
    root = root->left;
    aux->left = root->right;
    root->right = aux;
    return root;
}

AgendaNode *lrRotation(AgendaNode *root)
{
    root->left = rrRotation(root->left);
    return llRotation(root);
}

AgendaNode *rlRotation(AgendaNode *root)
{
    root->right = llRotation(root->right);
    return rrRotation(root);
}

int leftHeight(AgendaNode *root)
{
    if (checksIfEmpty(root)) return 0;
    int height = 1 + leftHeight(root->left);
    return height;
}

int rightHeight(AgendaNode *root)
{
    if (checksIfEmpty(root)) return 0;
    int height = 1 + rightHeight(root->right);
    return height;
}

int height(AgendaNode *root)
{
    if (checksIfEmpty(root)) return 0;
    int rHeight = rightHeight(root->right);
    int lHeight = leftHeight(root->left);
    if (lHeight > rHeight) return 1 + lHeight;
    return 1 + rHeight;
}

int checksBalance(AgendaNode *root)
{
    return height(root->left) - height(root->right);
}

AgendaNode *sideToBalance(AgendaNode *root)
{
    int childBalance, rootBalance = checksBalance(root);
    if (rootBalance > 1)
    {
        childBalance = height(root->left->left) - height(root->left->right);
        root = (childBalance < 0) ? lrRotation(root):llRotation(root);
    }
    else if (rootBalance < -1)
    {
        childBalance = height(root->right->left) - height(root->right->right);
        root = (childBalance < 0) ? rrRotation(root):rlRotation(root);
    }
    return root;
}

AgendaNode *searching(AgendaNode *root, char name[30])
{
    if (checksIfEmpty(root) || strcmp(name, root->info.name) == 0) return root;
    else if (comparesNames(root->info.name, name) == 1 || comparesNames(root->info.name, name) == -1) return searching(root->left, name);
    return searching(root->right, name);
}

AgendaNode *modifyEmail(AgendaNode *aux, AgendaNode *root)
{
    while (1==1)
    {
        char email[40];
        printf("New email: ");
        scanf("%s", email);
        if (checksEmail(email))
        {
            strcpy(aux->info.email, email);
            printf("Email was updated with success!\n");
            return root;
        }
        printf("This email isn't valid.\n");
        breaking();
    }
    return root;
}

AgendaNode *modifyPhone(AgendaNode *aux, AgendaNode *root)
{
    char phone[15];
    printf("New phone number: ");
    scanf("%s", phone);
    strcpy(aux->info.phone, phone);
    printf("Phone number was updated with success!\n");
    return root;
}

AgendaNode *modifyName(AgendaNode *aux, AgendaNode *root)
{
    AgendaNode *new_one = (AgendaNode*)malloc(sizeof(AgendaNode));
    new_one->info = aux->info;
    new_one->left = NULL;
    new_one->right = NULL;
    while (1==1) //makes sure the name has not been used yet
    {
        char name[30];
        printf("New name: ");
        scanf("%s", name);
        if (checksIfEmpty(searching(root, name)))
        { 
            strcpy(new_one->info.name, name);
            root = delContact(root, aux->info.name);
            root = insContact(new_one, root);
            printf("The name was updated with success!\n");
            break;
        }
        printf("This name has already been used.\n");
        breaking();
    }
    return root;
}

AgendaNode *modifyBirthday(AgendaNode *aux, AgendaNode *root)
{
    while (1==1)
    {
        printf("New birthday: ");
        scanf("%d/%d/%d", &aux->info.birth.day, &aux->info.birth.month, &aux->info.birth.year);
        if (checksBirthday(aux->info.birth.day, aux->info.birth.month, aux->info.birth.year))
        {
            printf("The birth day was updated with success!\n");
            return root;
        }
        printf("This date isn't valid!\n");
        breaking();
    }
    return root;
}

AgendaNode *upContact(AgendaNode *root)
{
    char name[30];
    int option;
    printf("Name: ");
    scanf("%s", name);
    AgendaNode *aux = searching(root, name);
    if (aux == NULL) printf("This person is not on the list!\n");
    else
    {
        while(1==1)
        {
            printf("Select what you want to modify:\n1- Email\n2- Phone\n3- Name\n4- Birthday\n5- Exit\n->");
            scanf("%d", &option);
            if (option == 5) return root;
            else if (option == 1)
                root = modifyEmail(aux, root);
            else if (option == 2)
                root = modifyPhone(aux, root);
            else if (option == 3)
                root = modifyName(aux, root);
            else if (option == 4)
                root = modifyBirthday(aux, root);
            else
            {
                printf("This option isn't valid!");
                breaking();
            }
        }
    }
    return root;
}

int checksBirthday(int day, int month, int year)
{
    if (day < 1 || day > 31) return 0;
    else if (month < 1 || month > 12) return 0;
    else if (year < 1900 || year > 2022) return 0;
    return 1;
}

int checksEmail(char email[40])
{
    for (int i = 0; i < 39; i++)
        if (email[i] == 64) return 1;
    return 0;
}

AgendaNode *newOne(AgendaNode *root)
{
    AgendaNode *new_one = (AgendaNode*)malloc(sizeof(AgendaNode));
    while (1==1) //makes sure the name has not been used yet
    {
        char name[30];
        printf("Name: ");
        scanf("%s", name);
        if (checksIfEmpty(searching(root, name)))
        { 
            strcpy(new_one->info.name, name);
            break;
        }
        printf("This name has already been used.\n");
        breaking();
    }
    while (1==1)
    {
        printf("Birthday: ");
        scanf("%d/%d/%d", &new_one->info.birth.day, &new_one->info.birth.month, &new_one->info.birth.year);
        if (checksBirthday(new_one->info.birth.day, new_one->info.birth.month, new_one->info.birth.year))
            break;
        printf("This date isn't valid!\n");
        breaking();
    }
    while (1==1)
    {
        char email[40];
        printf("Email: ");
        scanf("%s", email);
        if (checksEmail(email))
        {
            strcpy(new_one->info.email, email);
            break;
        }
        printf("This email isn't valid.\n");
        breaking();
    }
    printf("Phone: ");
    scanf("%s", new_one->info.phone);
    return new_one;
}

AgendaNode *insContact (AgendaNode *newly, AgendaNode *root)
{
    if (checksIfEmpty(root)) return newly;
    else if (comparesNames(root->info.name, newly->info.name) == 1 || comparesNames(root->info.name, newly->info.name) == -1)
        root->left = insContact(newly, root->left);
    else
        root->right = insContact(newly, root->right);
    root = sideToBalance(root);
    return root;
}

AgendaNode *minNode(AgendaNode *root)
{
    AgendaNode *aux = root;
    /* loop down to find the leftmost leaf */
    while (aux->left != NULL)
        aux = aux->left;
    return aux;
}

AgendaNode *delContact (AgendaNode *root, char name[30])
{ //GEEKSFORGEEKS
   
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if (comparesNames(root->info.name, name) == 1)
        root->left = delContact(root->left, name);
 
    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if(comparesNames(root->info.name, name) == 2)
        root->right = delContact(root->right, name);
 
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            AgendaNode *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AgendaNode *temp = minNode(root->right);
 
            // Copy the inorder successor's
            // data to this node
            root->info = temp->info;
 
            // Delete the inorder successor
            root->right = delContact(root->right, temp->info.name);
        }
    }
    if (!checksIfEmpty(root)) root = sideToBalance(root);
    return root;
}

AgendaNode *mainDelete(AgendaNode *root)
{
    char name[30];
    AgendaNode *toRemove;
    printf("Name: ");
    scanf("%s", name);
    toRemove = searching(root, name);
    if (checksIfEmpty(toRemove))
        printf("This person is not on the list!\n");
    else
    {
        root = delContact(root, name);
        printf("The person was removed with success!\n");
    }
    return root;
}

void menuPage()
{
    AgendaNode *root = NULL;
    root = readFile(root);
    int option;
    while (1==1)
    {
        printf("1-Insert someone\n2-List every one\n3-Search for someone\n4-Remove someone\n5-Update data\n0-Leave\n-> ");
        scanf("%d", &option);
        breaking();
        if (option == 0)
        {
            printf("Leaving current page.\n");
            breaking();
            writeOnFile(root, openFile());
            freeMemory(root);
            return;
        }
        else if (option == 1)
        {
            root = insContact(newOne(root), root);
            printf("The name was inserted with success!\n");
            breaking();
        }
        else if (option == 2)
        {
            if (checksIfEmpty(root))
                printf("There is no one on the list.\n");
            else listContacts(root);
            breaking();
        }
        else if (option == 3)
        {
            queryContact(root);
            breaking();
        }
        else if (option == 4)
        {
            root = mainDelete(root);
            breaking();
        }
        else if (option == 5)
        {
            root = upContact(root);
            breaking();
        }
        else
        {
            printf("This option is not available.\n");
            breaking();
        }
    }

}




