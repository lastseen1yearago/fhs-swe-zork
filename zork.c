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
    printf("You take a look at your wrist, carrying a small screen displaying a map of the spaceship you are currently traveling on - the Marksman. Right now you are in the Medbay room.\n\n");
}

// Neuen Baumknoten anlegen:
TreeNode* create_new_node(const char* message) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->currmessage = strdup(message);                     //strdup (string duplicate) sonst pointer target type error
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hauptfunktion fuers "Gameplay":
void gameplay(TreeNode* root) {
    if (root == NULL) {
        return; }

    // Ausgabe der aktuellen Mission und dazugehoerigen Optionen

                            // Das gehoert auf jeden Fall noch ausgegruebelt, ist noch sehr fehleranfaellig und unfertig!!!!!!!!!!!!!!!!!
                            
    printf("%s\n", root->currmessage);
    printf("1.) %s\n", root->left->currmessage);
    printf("2.) %s\n", root->right->currmessage);

    // gibt es weder links noch rechts einen weiteren Knoten, so endet das Spiel (Game Over Status)
    if (root->left == NULL && root->right == NULL) {
        return;
    }

    int input;
    do {
        printf("Pick your Option: ");
        scanf("%d", &input);
        getchar();
        // getchar wegen einem Zeilenumbruch
        // Input solange abfragen bis player 1 / 2 eingibt (ansonsten wird auf dem derzeitigen Auswahlknoten verharrt)
    } while (input != 1 && input != 2);

    // userinput verarbeiten (1 = left | 2 = right)
    if (input == 1) {
        gameplay(root->left);
    } else if (input == 2) {
        gameplay(root->right);
    }
    else {
        // allgemeiner Fehler, Spielabbruch
        return;
    }
}

                    // Ueberlegung: soll es eine go-Back-Funktion geben? Macht das Sinn?

// nach dem Spielen soll der allokierte Speicher auch wieder freigegeben werden koennen:
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return; }
    else {
        freeTree(root->left);
        freeTree(root->right);
        free(root->currmessage);
        free(root); }
}