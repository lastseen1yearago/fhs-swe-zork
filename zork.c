#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zorklib.h"

#define NUMOFMSG 6

// alle noetigen Funktionen fuer das fertige Spiel
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

// Funktion fuer die random Ausgabe der Messages in der Zusammenfassung:
int randnum (int val) {
    int num;
    num = (rand() % ((val + 12) / 4 ));

    return num;
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
    
    // 2x strdup() um messages zu befuellen (string duplicate) -> sonst pointer target type error
    newNode->taskmessage = strdup(task);                     
    newNode->prntmessage = strdup(print);

    // failsafe falls strdup() die messages nicht befuellen kann
    // es wird dann der gesamte Tree ausgehend der newNode deleted                  ->                  *** Ueberlegen: ist das smart so? Reicht es nicht die newNode freizugeben? der Tree wird dann am Ende der main geloescht...***
    if (newNode->taskmessage == NULL || newNode->prntmessage == NULL)
    {
        printf("Error while trying to copy string into story node.\n");
        delete_tree(newNode);
        return NULL;
    }
    
    // links und rechts NULL setzen
    newNode->left = NULL;
    newNode->right = NULL;

    // flag standardmaessig 0 setzen (0 = nicht in linked list | 1 = in die linked list)
    // geht inzwischen auch ohne flag aber lass ich mal drin - schadet sicher nicht
    newNode->flag = 0;

    return newNode;
}

// Linked-List erstellen und befuellen:
ListNode* tree_to_llist(ListNode* head, TreeNode* currentNode) {
    if (currentNode == NULL) {
        return NULL;
    }

    // neue ListNode allokieren 
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

    // failsafe malloc (falls ein Fehler bei der Allokierung auftreten sollte)
    if (newNode == NULL)
    {
        printf("Error while trying to allocate memory for linked list node.\n");
        return NULL;
    }

    // erstellte ListNode mit Inhalt der uebergebenen TreeNode befuellen
    newNode->curr_node = currentNode;
    newNode->next = NULL;

    // ist die Liste leer (= neue Liste) dann wird die erstellte neue ListNode zum head der Liste
    if (head == NULL) {
        head = newNode;
    } 
    
    else {
        // gibt es bereits einen head soll an diesen bzw. an die letzte ListNode angehaengt werden
        ListNode* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    return head;
}

// erstellte Linked-List anzeigen: 
void print_llist(ListNode* head) {
    // Titel fuer die Entscheidungsliste und ein paar gameplay messages
    printf("\n - - - Your choices - - - \n");

    const char* msgs[NUMOFMSG] = {"Good choice: ", "Excellent choice: ", "Great choice: ", "Well chosen: ", "Good thinking: ", "Trusty feeling: "};
    
    // uebergebenen head als current Node setzen
    ListNode* current = head;
    int shwmsg = 0;

    // printen der gewaehlten Nodes in einer Entscheidungsliste (flag = 1)
    while (current != NULL) {
        if (current->curr_node->flag) {
            // wenn die letzte Node der Liste erreicht wurde wird die critical Message (win / lose) geprintet
            if (current->next == NULL) {
                printf("Critical choice: %s\n", current->curr_node->taskmessage);
            }

            // gibt es noch eine ->next Node dann wird eine random Message geprintet und es geht weiter
            else {
                shwmsg = randnum(NUMOFMSG);
                printf("%s",msgs[shwmsg]);
                printf("%s\n", current->curr_node->taskmessage);
            }
        }
        // anschliessend wird die ->next Node zur aktuellen Node gesetzt
        current = current->next;
    }
}

// Hauptfunktion fuers "Gameplay":
void gameplay(TreeNode* root, ListNode* select) {
    if (root == NULL) {
        return ; }

    if (root->left != NULL && root->right != NULL) {
        printf("1.) %s\n", root->left->taskmessage);
        printf("2.) %s\n", root->right->taskmessage);

        int input;

        // Input solange abfragen bis player 1 / 2 eingibt (ansonsten wird auf dem derzeitigen Auswahlknoten verharrt)
        // do-while weil beim Ersten Aufruf noch kein input vorhanden ist (normale while greift dann nie!)
        do {
            printf("Pick your Option: ");
            scanf("%d", &input);
            // getchar weil sonst funktioniert die Abfrage nicht richtig (???)
            getchar();
        } while (input != 1 && input != 2);

        // userinput verarbeiten (1 = left | 2 = right)
        if (input == 1) {
            // flag auf gewaehlte Node setzen (1)
            // funktioniert nach der Korrektur in der tree_to_llist() Funktion auch ohne Flag aber doppelt haelt besser und ich werf die Idee jetzt nicht mehr ueber Board
            root->left->flag = 1;
            select = tree_to_llist(select, root->left);
            printf("%s\n", root->left->prntmessage);
            gameplay(root->left, select);

        } else if (input == 2) {
            // flag auf gewaehlte Node setzen (1)
            // funktioniert nach der Korrektur in der tree_to_llist() Funktion auch ohne Flag aber doppelt haelt besser und ich werf die Idee jetzt nicht mehr ueber Board
            root->right->flag = 1;
            select = tree_to_llist(select, root->right);
            printf("%s\n", root->right->prntmessage);
            gameplay(root->right, select);
        }
    }

    // gibt es weder links noch rechts einen weiteren Knoten, so endet das Spiel (Game Over Status)
    else if (root->left == NULL && root->right == NULL) {
        // Linked List befuellen und printen
        print_llist(select);

        // end game message
        printf("\nPress any key to end game.\n");
        getchar();
        return; 
    }
}

// aufraeumen Memory des Trees:
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
    
    // erst links, dann rechts loeschen
    else {
        delete_tree(root->left);
        delete_tree(root->right);
    }
}

// aufraeumen Memory der List:
void delete_linked_list(ListNode* head) {
    // checken ob ueberhaupt etwas zu loeschen vorhanden ist
    if (head == NULL) {
        return;
    }

    // head als current Variable deklarieren
    ListNode* current = head;

    // solange die current Variable nicht NULL ist kann nun per anlegen einer temp Variable Schritt fuer Schritt durch die Liste gegangen und geloescht werden
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}
