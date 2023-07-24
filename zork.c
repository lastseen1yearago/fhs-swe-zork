#include "zorklib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// alle noetigen Funktionen fuer den zork Nachbau

void intro() {
    printf("You wake up in your sleeping capsule in a cold sweat. \n 
    What happened? \n
    Who are you? \n
    And what is this place around you? \n
    Your head hurts and you can barely see. You slowly open your capsules door to find that 5 other capsules are still closed -  the others inside still asleep. \n
    Your mind clears up a little and you decide to play it safe. \n
    'Before I try to wake up anyone else, I should find out who they are, and more importantly, who I am.' \n
    You take a look at your wrist, carrying a small screen displaying a map of the spaceship you are currently traveling on - the Marksman. Right now you are in the Medbay-Room. \n\n
    Task: \n
    Find your and everyone elses ID cards."):
}

// int getuserchoice(???????) {
    //returncodes:
    // >=  1 ->   Option 1
    //     0 ->   Option 2
    // <= -1 ->   Option 3
//}

int getUserChoice(const char* prompt, const char* choices[], int numChoices) {
    int choice;
    do {
        printf("%s\n", prompt);
        for (int i = 0; i < numChoices; i++) {
            printf("%d. %s\n", i + 1, choices[i]);
        }
        printf("Deine Wahl: ");
        scanf("%d", &choice);
        getchar();
    } while (choice < 1 || choice > numChoices);

    return choice;
}