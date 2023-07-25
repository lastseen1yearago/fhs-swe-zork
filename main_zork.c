#include "zorklib.h"
#include <stdlib.h>
#include <stdio.h>

// Main File fuer das richtige spielen des zork clons

int main() {
    //Intro:
    intro();

    const char* story_pieces[] = {                      //To Do: Baum mit storypieces in der Main erstellen oder eine eigene Funktion dafuer, das Array faellt dann weg!!
        "Task: Find your and everyone elses ID cards.",
        "Go to cafeteria.",
        "Go to engine-room.",
        "Go to storage.",
        "Go to administration.",
        "Pick up ID",
        "Check crewmates IDs",
        "Wake up Aaron.",
        "Wake up Sterling.",
        "Wake up Laura.",
        "Wake up Malory.",
        "Wake up Randy.",
    };

// Entscheidungsbaum -> soll lieber doch Binary Tree werden, Main muss dementsprechend umgebaut werden...
// BSP: TreeNode* root = createNode("Task: Find your and everyone elses ID cards.");

    // Spiel starten und laufen lassen:
    gameplay(root);

    // nach Spielende (Break-Condition der gameplay Funktion) muss memory wieder gefreed werden:
    freeTree(root);

    return 0;
}