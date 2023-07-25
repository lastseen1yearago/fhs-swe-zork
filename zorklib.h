// Library fuer die Funktionen und Baumstruktur unseres zork Nachbaus
// implemetiert in zork.c / verwendet in main_zork.c

typedef struct node {
    char* message;              // Current Message, also wo man sich im Spiel gerade befindet und welche Moeglichkeiten man hat
    struct node* left;          // Zeiger auf den linken Kindknoten (linke Wahl)
    struct node* right;         // Zeiger auf den rechten Kindknoten (rechte Wahl)
} TreeNode;