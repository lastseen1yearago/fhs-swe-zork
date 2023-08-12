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
    printf("Your head hurts and you can barely see. You slowly open your capsules door to find that the other capsules are still closed - the others inside still asleep.\n");
    printf("Your mind clears up a little and you decide to play it safe.\n");
    printf("'Before I try to wake up anyone else, I should find out who they are, and more importantly, who I am.'\n");
    printf("You take a look at your wrist, carrying a small screen displaying a map of the spaceship you are currently traveling on - the Marksman - a military transport ship. Right now you are in the crews sleeping quarters.\n\n");
    printf("You check the traveling logs. Your ship picked up a crate of undisclosed lab equipment. Inspecting the load description you find out that you have been transporting experimental parasites.\n");
    printf("You're the only one awake... your inner voice tells you you need to stop the ship from reaching earth or find a way to make sure everyones cured. Comms are cut out, you don't know who is infected by the parasites. Be careful who you trust\n");
}

// Neuen Baumknoten anlegen:
TreeNode* create_new_node(const char* task, const char* print) {
    // neue Node allokieren
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

    // failsafe malloc (falls ein Fehler bei der Allokierung auftreten sollte)
    if (newNode == NULL)
    {
        printf("Error while trying to allocate memory for story node.\n");
        return NULL;
    }
    
    //2x strdup (string duplicate) sonst pointer target type error
    newNode->taskmessage = strdup(task);                     
    newNode->prntmessage = strdup(print);
    
    // links und rechts NULL setzen
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
            printf("%s\n", root->left->prntmessage);
            gameplay(root->left);
        } else if (input == 2) {
            printf("%s\n", root->right->prntmessage);
            gameplay(root->right);
        }
    }

    // gibt es weder links noch rechts einen weiteren Knoten, so endet das Spiel (Game Over Status)
    else if (root->left == NULL && root->right == NULL) {
        // printf("%s\n", root->prntmessage);   ->  braucht man mit der Loesung über Input-Variablen nicht mehr???
        printf("Press any key to end game.\n");
        getchar();
        return; 
    }
}

void delete_tree(TreeNode *root) {
    // checken ob ueberhaupt ein Knoten vorhanden ist
    if (root == NULL) {
        return;
    }

    // checken ob es child Nodes gibt -> wenn es keine gibt kann root inkl. tast- & prntmessage deleted werden
    else if (root->left == NULL && root->right == NULL)
    {
        free(root->taskmessage);
        free(root->prntmessage);
        free(root);
    }
    
    // erst links, dann rechts löschen
    else {
        delete_tree(root->left);
        delete_tree(root->right);
    }
}
