#include<stdio.h>
#include<stdlib.h>
#include "functions.h"
#include<string.h>

// function which returns max
int max(int a,int b){
    return (a > b) ? a : b;
}

// function which returns height
int height(node *root){
    if (root == NULL )
    {
        return 0;
    }
    return 1+max(height(root->left),height(root->right));
}

// function which makes new node
node* newNode(char *data){
    node* nn = (node*) malloc(sizeof(node));
    strcpy(nn->data,data);
    nn->left = NULL;
    nn->right = NULL;
    nn->height = 0;
    return nn;
}

// function for right rotating
node* rightRotate(node* root){
    // get all subtrees
    node *x = root->left;
    node *t2 = x->right;

    //      y                                x
    //     / \     Right Rotation          /  \
    //    x   T3   - - - - - - - >        T1   y 
    //   / \       < - - - - - - -            / \
    //  T1  T2     Left Rotation            T2  T3
    
    // x become parent of y
    x->right = root;

    //T2 becomes left child of y
    root->left = t2;

    // update the heights of both x & root
    x->height = height(x);
    root->height = height(root);
    
    // return new root
    return x;
}

// function for left rotating
node* leftRotate(node* root){
    // get all subtrees
    node *x = root->right;
    node *t2 = x->left;

    //      y                                x
    //     / \     Right Rotation          /  \
    //    x   T3   - - - - - - - >        T1   y 
    //   / \       < - - - - - - -            / \
    //  T1  T2     Left Rotation            T2  T3
    
    // x become parent of y
    x->left = root;

    //T2 becomes left child of y
    root->right = t2;

    // update the heights of both x & root
    x->height = height(x);
    root->height = height(root);
    
    // return new root
    return x;
}

//function which gets balance
int getBalance(node *root){
    if (root == NULL)
    {
        return 0;
    }
    return height(root->left)-height(root->right);
}

node* insert(node *root,char *data){

    if (root == NULL)
    {
        return newNode(data);
    }
    
    // perform normal bst insertion
    if (strcmp(data,root->data) < 0)
    {
        root->left = insert(root->left,data);
    }

    else if (strcmp(data,root->data)>0)
    {
        root->right = insert(root->right,data);
    }
    
    root->height = height(root); // update the height
    
    int balance = getBalance(root); // get the balance of node

    // left left rotation
    if (balance > 1 && (strcmp(data,root->left->data)<0))
    {
        return rightRotate(root);
    }
    
    // right right rotaton
    if (balance < -1 && (strcmp(data,root->right->data)>0))
    {
        return leftRotate(root);
    }

    // left right rotation
    if (balance > 1 && (strcmp(data,root->left->data)>0))
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // right left rotation
    if (balance < -1 && (strcmp(data,root->right->data)<0) )
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    printf("\n%d inserted\n");
    return root;
}

node * minValueNode(node* root)
{
    node* current = root;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

node* deleteNode(node *root,char *data){
    printf("\nDeleting ...\n");
    // perform standard bst deletion
    if (root == NULL) // if tree is empty
    {
        return root;
    }
    
    // if key to be deleted is in left subtree
    if (strcmp(data,root->data))
    {
        root->left = deleteNode(root->left,data);
    }

    // if key to be deleted is in right subtree
    else if (strcmp(data,root->data) > 0)
    {
        root->right = deleteNode(root->right,data);
    }

    // if we found the key
    else{
        // if node to be deleted has one child or zero child
        if (root->left == NULL || root->right == NULL)
        {
            node* temp = root->left ? root->left:root->right;

            // no child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
                free(temp);
            }
        }else{
            // node with two children then get inorder successor
            node *temp = minValueNode(root->right);

            // copy the conten
            strcpy(root->data,temp->data);

            // delete the inorder successor
            root->right = deleteNode(root->right,temp->data);
        }
    }
    
    if (root == NULL)
    {
        return root;
    }
    
    
    // check for balance and balance it

    // update the height
    root->height = 1 + max(height(root->left),height(root->right));
    int balance  = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

void postOrderTraversal(node *root){
    if (root != NULL)
    {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf(" %s ",root->data);
    }
}

void preOrderTraversal(node *root){
    if (root != NULL)
    {   
        printf(" %s ",root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void inorderTraversal(node *root){
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf(" %s ",root->data);
        inorderTraversal(root->right);
    }
}

void display(node *root){
    printf("\nDisplaying ...\n");

    printf("\nPostorder traversal => ");
    postOrderTraversal(root);
    printf("\n");

    printf("\nPreorder traversal => ");
    preOrderTraversal(root);
    printf("\n");

    printf("\nInorder traversal => ");
    inorderTraversal(root);
    printf("\n");
}

void deleteTree(node* root)
{
    if (root == NULL) return;
 
    /* first delete both subtrees */
    deleteTree(root->left);
    deleteTree(root->right);
   
    /* then delete the node */
    printf("\n Deleting node: %s", root->data);
    free(root);
}