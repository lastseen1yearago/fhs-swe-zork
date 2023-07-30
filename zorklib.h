// Library fuer die Funktionen und Baumstruktur unseres zork Nachbaus
// implemetiert in zork.c / verwendet in main_zork.c

typedef struct node {
    char* taskmessage;              // Current Message, also wo man sich im Spiel gerade befindet und welche Moeglichkeiten man hat
    char* prntmessage;              // welceh Message geprintet werden soll
    struct node* left;              // Zeiger auf den linken Kindknoten (linke Wahl)
    struct node* right;             // Zeiger auf den rechten Kindknoten (rechte Wahl)
} TreeNode;

void intro();
void gameplay(TreeNode* root);
void delete_tree(TreeNode* root);
TreeNode* create_new_node(const char* task, const char* print);
