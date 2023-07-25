#include "zorklib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// alle noetigen Funktionen fuer den zork Nachbau
// Intro, Spielstart:
void intro() {
    printf("You wake up in your sleeping capsule in a cold sweat.\n");
    printf("What happened?\n");
    printf("Who are you?\n");
    printf("And what is this place around you?\n");
    printf("Your head hurts and you can barely see. You slowly open your capsules door to find that 5 other capsules are still closed -  the others inside still asleep.\n");
    printf("Your mind clears up a little and you decide to play it safe.\n");
    printf("'Before I try to wake up anyone else, I should find out who they are, and more importantly, who I am.'\n");
    printf("You take a look at your wrist, carrying a small screen displaying a map of the spaceship you are currently traveling on - the Marksman. Right now you are in the Medbay-Room.\n\n");
}

// Neuen Baumknoten anlegen:
TreeNode* create_new_node(const char* message) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->currmessage = message
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hauptfunktion fuers "Gameplay":
void gameplay(TreeNode* root) {
    if (root == NULL) {
        return; }

    ???
    ???
    ???
}

// nach dem Spielen soll der allokierte Speicher auch wieder freigegeben werden koennen:
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return; }
    else {
        freeTree(root->left);
        freeTree(root->right);
        free(root->message);
        free(root); }
}