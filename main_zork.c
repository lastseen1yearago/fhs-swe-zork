#include "zorklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Main File fuer das richtige spielen des zork clons

int main() {
    // Intro:
    intro();

    /*  - - -  - - -  - - -  - - -  - - -  - - -  - - -  - - - Braindump - - -  - - -  - - -  - - -  - - -  - - -  - - -  - - - 
	 
	Beispiel:
	
	TreeNode* root = create_new_node("Start","'Hmm... let's try going over there...'");			->			Start-Node: erster Char ist Option, zweiter Char ist der Text-Out NACHDEM eine Option gewählt wurde!!
	
	//Linker Teilbaum
    root->left = create_new_node("Go to 1","");													->			Option 1
    root->left->left = create_new_node("Go to 3","To be continued...");							->			wenn jetzt "Go to 3" gewählt wird, wird nichts geprintet (Go to 1 hat keine root->prntmessage)
    root->left->right = create_new_node("Go to 5","Game Over");									->			wenn dan "Go to 5" gewählt wird, wird die prntmessage ("tbc...") von "Go to 3" geprintet und auch ein Game Over weil letzte Node
	
	//Rechter Teilbaum
    root->right = create_new_node("Go to 2","");												->			Option 2
    root->right->left = create_new_node("Go to 4","To be continued...");						->			prinzipiell gleich wie bei "Go to 3"
    root->right->right = create_new_node("Go to 6","You Win!");									->			prinzipiell gleich wie bei "Go to 5"
	
	Soweit zur Logik des Baums, so sollte sich jetzt auch eine gscheide (und dynamische) Story aufbauen lassen
	
	    ->	ACHTUNG: hat ein Baum weder links ODER rechts eine Node so endet das spiel. Keine Node darf nur einen "Nachfolger" haben!	
        
        - - -  - - -  - - -  - - -  - - -  - - -  - - -  - - - Braindump - - -  - - -  - - -  - - -  - - -  - - -  - - -  - - - */

    // Die Story baut man in den Baum ein -> dafür gibt es jetzt in der node die Variable prntmessage!
    // So lässt sich das ganze auch dynamisch gestalten
    // Story (=Entscheidungsbaum) erstellen
    TreeNode* root = create_new_node("Start","'Hmm... let's try going over there...'");

    //so... den Baum bauen wir neu, was soll des:
    //linker Teilbaum
    root->left = create_new_node("Go to 1","");
    root->left->left = create_new_node("Go to 3","To be continued...");
    root->left->right = create_new_node("Go to 5","Game Over");

    //rechter Teilbaum
    root->right = create_new_node("Go to 2","");
    root->right->left = create_new_node("Go to 4","To be continued...");
    root->right->right = create_new_node("Go to 6","You Win!");

    // Spiel starten und laufen lassen:
    gameplay(root);

    // nach Spielende (Break-Condition der gameplay Funktion) muss memory wieder gefreed werden:
    freeTree(root);

    return 0;
}
