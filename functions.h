typedef struct node
{
    char data[20]; // store the data
    struct node* left; // pointer to left sub Tree
    struct node* right; // pointer to right sub tree
    int height; // keeps the record of height of node
} node;

node* insert(node *root,char *data);
node* deleteNode(node *root,char *data);
void display(node *root);
void deleteTree(node* root);
