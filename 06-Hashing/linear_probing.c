#include <stdio.h>
#define SIZE 10

int hashTable[SIZE];

void initialize()
{
    for(int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

void insert(int key)
{
    int index = key % SIZE;

    for(int i = 0; i < SIZE; i++)
    {
        int pos = (index + i) % SIZE;

        if(hashTable[pos] == key)
        {
            printf("Element already exists\n");
            return;
        }

        if(hashTable[pos] == -1)
        {
            hashTable[pos] = key;
            printf("Inserted successfully\n");
            return;
        }
    }

    printf("Hash table is full\n");
}

void search(int key)
{
    int index = key % SIZE;

    for(int i = 0; i < SIZE; i++)
    {
        int pos = (index + i) % SIZE;

        if(hashTable[pos] == key)
        {
            printf("Element found at index %d\n", pos);
            return;
        }

        if(hashTable[pos] == -1)
            break;
    }

    printf("Element not found\n");
}

void display()
{
    printf("\nHash Table:\n");

    for(int i = 0; i < SIZE; i++)
    {
        printf("%d : %d\n", i, hashTable[i]);
    }
}

int main()
{
    int choice, key;

    initialize();

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
