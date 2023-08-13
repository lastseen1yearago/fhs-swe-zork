// Library fuer die Funktionen und Baumstruktur unseres zork Nachbaus
// implemetiert in zork.c / verwendet in main_zork.c

// Definition TreeNode:
typedef struct node {
    char* taskmessage;              // Current Message, also wo man sich im Spiel gerade befindet und welche Moeglichkeiten man hat
    char* prntmessage;              // welceh Message geprintet werden soll
    struct node* left;              // Zeiger auf den linken Kindknoten (linke Wahl)
    struct node* right;             // Zeiger auf den rechten Kindknoten (rechte Wahl)
} TreeNode;

// Definition ListNode:
typedef struct linkedlistnode {
    TreeNode* curr_node;            // Zeiger auf die derzeitige Node
    struct linkedlistnode* next;    // Zeiger auf die naechste Node in der Liste
} ListNode;

// Gameplay-Funktionen:
void intro();
void gameplay(TreeNode* root, ListNode* select);

// Struktur-Funktionen:
TreeNode* create_new_node(const char* task, const char* print);
ListNode* tree_to_llist(ListNode* head, TreeNode* currentNode);
void print_llist(ListNode* head);

// Aufraeum-Funktionen:
void delete_tree(TreeNode* root);
void delete_linked_list(ListNode* head);
