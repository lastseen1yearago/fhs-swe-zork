#include "zorklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Main File fuer das richtige spielen des zork clons

int main() {
    // Intro:
    intro();

    // Story (=Entscheidungsbaum) erstellen
    
                        // Drei Gedankenpunkte dazu:
                        // 1.) wie weit kann man das automatisieren oder wenigstens in einer Funktion verstecken, damit es nicht in der Main stehen muss
                        // 2.) das gehoert natuerlich noch um Faktor X erweitert
                        // 3.) die Texte bzw. die Knoten gehoeren auch so geschrieben, dass sie fuer die Auswahl im Spiel Sinn machen bzw. jeweils an richtiger Stelle stehen / auch klar ist was zu tun ist
    
    TreeNode* root = create_new_node("Task: Find your and everyone elses ID cards.");
    root->left = create_new_node("Go to cafeteria.");
    root->right = create_new_node("Go to engine-room.");
    root->left->left = create_new_node("Go to storage.");
    root->left->right = create_new_node("Go to administration.");

    // Spiel starten und laufen lassen:
    gameplay(root);

    // nach Spielende (Break-Condition der gameplay Funktion) muss memory wieder gefreed werden:
    freeTree(root);

    return 0;
}