#include "zorklib.h"
#include <stdlib.h>
#include <stdio.h>

// Main File fuer das richtige spielen des zork clons

int main() {
    //Intro:
    intro();

    const char* story_pieces[] = {
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
        ""
    }

// Entscheidungsbaum
    const int numNodes = ?????;
    int choices[][2] = {
        ???
    };

// "Gameplay", also solange Fragen bis ein Game Over Status erreicht wird
    int currentNode = 0;
    while (1) {
        printf("%s\n", story[currentNode]);

        if (choices[currentNode][0] == -1) {
            break;
        }

        int choice = getUserChoice("Was willst du tun?", &story[choices[currentNode][0]], 2);
        currentNode = choices[currentNode][choice - 1];
    }

    return 0;
}