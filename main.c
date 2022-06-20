#include<stdio.h>
#include<stdlib.h>
#include "functions.h"
#include<string.h>

int main()
{
    printf("\n -------------------------- Welcome to Record Keeper ------------------------------\n");
    
    // initialize root to NULL
    node* root = NULL;

    while (1)
    {
        printf("\n1.For inserting name\n2.For deleteing name\n3.For displaying\n4.Delete tree()\n5.exit()\n");
    
        // take the key input
        int key;
        printf("\nEnter the key : ");
        scanf("%d",&key);

        // perform the operations according to key
        if (key == 1)
        {   
            char data[20];
            printf("\nEnter the name to be inserted : ");
            scanf("%s",&data);
            root = insert(root,data);
        }

        else if (key == 2)
        {   
            char data[20];
            printf("\nEnter the name to be deleted : ");
            scanf("%s",&data);
            root = deleteNode(root,data);
        }

        else if (key == 3)
        {     
            display(root);
        }

        else if (key == 4)
        {   
            deleteTree(root);
            return 0;
        }
        else if (key == 5)
        {   
            printf("\nThank you !!!\n");
            return 0;
        }
    }
    
    
    
    return 0;
}
