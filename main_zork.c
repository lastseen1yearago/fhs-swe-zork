#include "zorklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Main File fuer das richtige spielen des zork clons

int main() {
    // Intro:
    intro();
    
    // Story (=Entscheidungsbaum) erstellen -> alle Nodes außer End-Nodes müssen left- & right-Knoten haben
    TreeNode* root = create_new_node("Start","'Hmm... let's try going over there...'");

    // linker Teilbaum (Story mit possibilities A)
        // der is moi soweit fertig
    root->left = create_new_node("Go to cafeteria.","'This seems like the way to go...'");
    
    root->left->left = create_new_node("Go to navigation.","Navigation is locked!\nTrying to enter it with your key-card locked you in the hallway.\nYou lose."); // game over
    root->left->right = create_new_node("Go to weapons.","'Maybe I should arm myself before taking any actions");
    
    root->left->right->left = create_new_node("Pick up gun.","'Can't go wrong with this one can I?");
    root->left->right->right = create_new_node("Pick up knife.","'not really a gun person anyways.'");

    root->left->right->left->left = create_new_node("Go to medbay.","In medbay you encounter someone. He introduces himself as Sterling, caption of the ship.\nSomething seems off. Is he infected or just worried? Why does he have intact memory?");
    root->left->right->left->right = create_new_node("Go to navigation","Navigation is locked!\nTrying to enter it with your key-card locked you in the hallway.\nYou lose."); // game over

    root->left->right->right->left = create_new_node("Go to medbay.","On your way to medbay you trip and fall, stabbing yourself.\nYou lose."); // game over 
    root->left->right->right->right = create_new_node("Go to navigation","Navigation is locked!\nTrying to enter it with your key-card locked you in the hallway.\nYou lose."); // game over

    root->left->right->left->left->left = create_new_node("Trust Sterling.","You trusted your captian. Tragically he was the first to be infected.\nHe overpowers and kills you, you die."); // game over
    root->left->right->left->left->right = create_new_node("Shoot Sterling.","The captain was infected. Shooting him ensures your survival.\nYou pick up his key-card, giving you access to the navigation room.");

    root->left->right->left->left->right->left = create_new_node("Go to navigation","'I really hope this ship is easy to control.'");
    root->left->right->left->left->right->right = create_new_node("Go back to the sleeping quarters.","'I should wake someone up who can actually fly this thing.'");

    root->left->right->left->left->right->left->left = create_new_node("Shut off power.","Shutting off power stops the ship, but also the life support outside the sleeping quarters. You suffocate."); // game over
    root->left->right->left->left->right->left->right = create_new_node("Take control of ship.","You try stopping the ship manually. Auto-Pilot shuts off after you take over, yet you have no flight experience.\nYou don't manage to avoid the oncoming asteroid. You lose."); //game over

    root->left->right->left->left->right->right->left = create_new_node("Go to administration","'I should probably check out who these people are before deciding who to wake up. Not enough oxygen for everyone anyways.'");
    root->left->right->left->left->right->right->right = create_new_node("Open sleeping capsules by hand.","Bad idea not checking who you woke up.\nSome of your crewmates are acting... off. Oxygen is also running low.\nYou lose."); // game over

    root->left->right->left->left->right->right->left->left = create_new_node("Pick up and inspect IDs","'My name's Randy... huh, interesting... let's see who else is with us and take a guess on who to wake up.'");
    root->left->right->left->left->right->right->left->right = create_new_node("Access ships mainframe.","Your login data denies, you don't have the security clearence. Administration is locked down. You lose."); // game over

    root->left->right->left->left->right->right->left->left->left = create_new_node("Wake up Paul (Engineer)","'Maybe the crew engineer can help me find a way to stop this thing.'\n You wake up Paul. He asks whats going on and you briefly explain the situation.\n He offers two ideas on how to stop the ship from reaching eath.");
    root->left->right->left->left->right->right->left->left->right = create_new_node("Wake up Laura (Doctor)","'Maybe she can find a way to contain the parasites before everyone is doomed. We could go home...'\nYou open the sleeping capsule and wake Laura up.\nBefore you can even say anything she starts screaming and attacking you - she's infected already. You lose."); // infected, game over

    root->left->right->left->left->right->right->left->left->left->left = create_new_node("Go to engine room.","'We can try the mechanical way... but either of you are unsure what to shut off.'");
    root->left->right->left->left->right->right->left->left->left->right = create_new_node("Go to electrical.","'We can try the electrical way... but you cant shut off all of the elctrical systems... you need to cut a wire.'");

    root->left->right->left->left->right->right->left->left->left->left->left = create_new_node("Shut off main engines","Shutting off the main engines leaves the oxygen supply in tact - the ship will not reach earth.\nEven if it cost your and your crews life, you prevented millions from being infected back home... you win."); // win yay
    root->left->right->left->left->right->right->left->left->left->left->right = create_new_node("Shut off generator","Shutting off the generator also shuts off the fuel pumps - the ship stops. But so does the oxygen supply. You lose"); // game over

    root->left->right->left->left->right->right->left->left->left->right->left = create_new_node("Cut blue wire.","Cutting the blue wire cuts power to the main generator. No generator means no life support systems. You lose."); // game over
    root->left->right->left->left->right->right->left->left->left->right->right = create_new_node("Cut green wire.","Cutting the green wire stops the current to the fuel pumps - the ship will not reach earth.\nEven if it cost your and your crews life, you prevented millions from being infected back home... you win."); // win yippie

    // rechter Teilbaum (Story mit possibilities B)
    root->right = create_new_node("Go to engine-room.","'This seems like the way to go...'");
    
    root->right->left = create_new_node("Go to storage.","");
    root->right->right = create_new_node("Go to administration.","");
    
    root->right->left->right = create_new_node("Go to navigation","Navigation is locked!\nTrying to enter it with your key-card locked you in the hallway.\nYou lose."); // game over
    root->right->left->left = create_new_node("Inspect cargo.","");
    
    root->right->right->left = create_new_node("Pick up and inspect IDs.","");
    root->right->right->right = create_new_node("Use central computer to shut off sleeping capsules.","Bad idea not checking who you woke up.\nSome of your crewmates are acting... off. Oxygen is also running low.\nYou lose."); // game over

    // Spiel starten und laufen lassen:
    gameplay(root);

    // nach Spielende (Break-Condition der gameplay Funktion) muss memory wieder gefreed werden:
    delete_tree(root);

    return 0;
}
