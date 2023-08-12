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
    
    root->right->left = create_new_node("Go to storage.","'Let's see what we are actually hauling...'");
    root->right->right = create_new_node("Go to administration.","'Let's try to find out who we are...'");
    
    root->right->left->left = create_new_node("Inspect cargo.","'Maybe I can find something usefull throughout this lab stuff?'");
    root->right->left->right = create_new_node("Go to navigation","Navigation is locked!\nTrying to enter it with your key-card locked you in the hallway.\nYou lose."); // game over

    root->right->right->left = create_new_node("Pick up and inspect IDs.","'My name's Randy... huh, interesting... let's see who else is with us and take a guess on who to wake up.'");
    root->right->right->right = create_new_node("Use central computer to shut off sleeping capsules.","Bad idea not checking who you woke up.\nSome of your crewmates are acting... off. Oxygen is also running low.\nYou lose."); // game over

    root->right->left->left->left = create_new_node("Open crates.","Opening the crate you release the rest of the parasites onto the ship and get infected. You lose."); // game over
    root->right->left->left->right = create_new_node("Pick up and inspect syringes.","'Antidode - use if lab partner get's infected... can't hurt to take a few of those with me.'");

    root->right->right->left->left = create_new_node("Wake up Lyn (Scientist)","'Maybe the crazy science guy knows a way to solve this situation.");
    root->right->right->left->right = create_new_node("Wake up Aaron (Weapons Specialist)","You wake up Aaron. Although he claims to be on your side at first, things seem off quite quickly.");

    root->right->left->left->right->left = create_new_node("Go to medbay.","'Maybe I can find someone over there who can help me.'\nIn medbay you encounter some of the medical caretakers.");
    root->right->left->left->right->right = create_new_node("Go to lab.","On your way to the lab you hear someone approaching from behind. It's Lyn, the scientist. She was sleeping before... odd.");

    root->right->right->left->left->left = create_new_node("Ask Lyn to go to Lab.","The two of you make your way to the lab.");
    root->right->right->left->left->right = create_new_node("Go to Medbay with Lyn.","Trusting the scientist to go to the medical staff first seems like a fine idea.\nHowever the medical staff has long been infected. You stand no chance."); // game over

    root->right->right->left->right->left = create_new_node("Trust Aaron regardless.","Trusting someone in this situation makes you good hearted, but not smart.\nEven though Aaron was not infected, he distrusts and shoots you. You lose."); // game over
    root->right->right->left->right->right = create_new_node("Fight Aaron.","Yeah... he had a gun. You lose."); // game over

    root->right->left->left->right->left->left = create_new_node("Hand syringes to medical staff.","Medbay was infected by the parasites while you were out an about. You cannot escape. You lose."); // game over
    root->right->left->left->right->left->right = create_new_node("Inject caretaker with antidode.","Your intentions were right, the caretakes are infected. But the antidode takes a few minutes to kick in.\nThey overpower you while fighting. You lose."); //game over

    root->right->left->left->right->right->left = create_new_node("Trust Lyn.","You trust Lyn to help you. You make it to the Lab and put it into lockdown.\nThe antidodes you collected before can be brought into a gas like state and pumped through through the ventilation system.\nYou win!"); // early win (sppedrun)
    root->right->left->left->right->right->right = create_new_node("Distrust Lyn.","Your instincts tell you Lyn is infected, you start fighting with her and manage to take her out, which leaves you without any help whatsoever. The parasites are getting closer and closer."); //early end (sppedrun fail)

    root->right->right->left->left->left->left = create_new_node("Go to storage first.","'We should see what we can find in storage.");
    root->right->right->left->left->left->right = create_new_node("Go straight to lab.","'No time to lose!'");

    root->right->right->left->left->left->left->left = create_new_node("Pick up and inspect syringes.","Lyn explains she can use the antidodes to save everyone!");
    root->right->right->left->left->left->left->right = create_new_node("Open crates.","You open a crate and try to get a hold of one of the parasites for Lyn to study.\nWhile fighting for your own safety you lose Lyn. You are alone... well, the parasites are with you."); // game over

    root->right->right->left->left->left->right->left = create_new_node("Go back to storage.","'Lyn, stay in the lab. I will try to find something useful to work with!'");
    root->right->right->left->left->left->right->right = create_new_node("Lock down lab.","Without any starting point it takes the two of you too long to create an antidode yourselves. You starve in the lab."); // game over

    root->right->right->left->left->left->left->left->left = create_new_node("Go to Lab","You make it to the Lab and put it into lockdown.\nThe antidodes you collected before can be brought into a gas like state and pumped through through the ventilation system.\nYou win!"); // win yahoo
    root->right->right->left->left->left->left->left->right = create_new_node("Go back to sleeping quarters.","You make it back to the sleeping quarters and inject everyone before waking them up.\nWith the combined power of the crew you manage to put medbay and storage into lockdown and make it back safely to earth.\nYou win!"); // win

    root->right->right->left->left->left->right->left->left = create_new_node("Search medipacks.","You find the antidodes, but on your way back you notice yourself getting dizzy... you were infected back there!\nYou hand the antidodes to Lyn and lock yourself in storage. Lyn manages to pump antidodes through the air vents. You win!"); // win
    root->right->right->left->left->left->right->left->right = create_new_node("Search crates.","Searching the crates gets you infected. Your mindless body makes its way back to the lab to stop Lyn. You lose."); // game over

    // Spiel starten und laufen lassen:
    gameplay(root);

    // nach Spielende (Break-Condition der gameplay Funktion) muss memory wieder gefreed werden:
    delete_tree(root);

    return 0;
}
