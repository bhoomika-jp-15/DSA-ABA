#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

struct Node
{
    int data;
    struct Node *next;
};

struct Node *hashTable[SIZE] = {NULL};

void insert(int key)
{
    int index = key % SIZE;

    struct Node *temp = hashTable[index];

    while(temp != NULL)
    {
        if(temp->data == key)
        {
            printf("Element already exists\n");
            return;
        }
        temp = temp->next;
    }

    struct Node *newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("Inserted successfully\n");
}

void search(int key)
{
    int index = key % SIZE;

    struct Node *temp = hashTable[index];

    while(temp != NULL)
    {
        if(temp->data == key)
        {
            printf("Element found\n");
            return;
        }

        temp = temp->next;
    }

    printf("Element not found\n");
}

void display()
{
    printf("\nHash Table:\n");

    for(int i = 0; i < SIZE; i++)
    {
        struct Node *temp = hashTable[i];

        printf("%d : ", i);

        while(temp != NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

int main()
{
    int choice, key;

    while(1)
    {
        printf("\n1.Insert\n2.Search\n3.Display\n4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
