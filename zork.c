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
    printf("Task: Find your and everyone elses ID cards.\n");
}

// Neuen Baumknoten anlegen:
TreeNode* create_new_node(const char* task, const char* print) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->taskmessage = strdup(task);                     
    newNode->prntmessage = strdup(print);
    //2x strdup (string duplicate) sonst pointer target type error
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hauptfunktion fuers "Gameplay":
void gameplay(TreeNode* root) {
    if (root == NULL) {
        return ; }

    if (root->left != NULL && root->right != NULL) {
        printf("1.) %s\n", root->left->taskmessage);
        printf("2.) %s\n", root->right->taskmessage);

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
            printf("%s\n", root->prntmessage);
            gameplay(root->left);
        } else if (input == 2) {
            printf("%s\n", root->prntmessage);
            gameplay(root->right);
        }
    }

    // gibt es weder links noch rechts einen weiteren Knoten, so endet das Spiel (Game Over Status)
    else if (root->left == NULL && root->right == NULL) {
        printf("%s\n", root->prntmessage);
        printf("Press any key to end game.\n");
        getchar();
        return; 
    }
}

// nach dem Spielen soll der allokierte Speicher auch wieder freigegeben werden koennen:
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return; }
    else {
        freeTree(root->left);
        freeTree(root->right);
        free(root->prntmessage);
        free(root->taskmessage);
        free(root); 
    }
}
