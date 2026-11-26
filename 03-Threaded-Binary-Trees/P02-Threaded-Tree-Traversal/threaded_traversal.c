
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;
};

struct Node *head;

void initialize() {
    head = (struct Node *)malloc(sizeof(struct Node));
    head->lthread = 1;
    head->rthread = 0;
    head->left = head;
    head->right = head;
}

void insert(int key) {
    struct Node *ptr = head->left;
    struct Node *temp;

    if (head->lthread == 1) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = key;
        temp->left = head;
        temp->right = head;
        temp->lthread = 1;
        temp->rthread = 1;

        head->left = temp;
        head->lthread = 0;
        return;
    }

    while (1) {
        if (key == ptr->data)
            return;

        if (key < ptr->data) {
            if (ptr->lthread == 1) {
                temp = (struct Node *)malloc(sizeof(struct Node));
                temp->data = key;
                temp->left = ptr->left;
                temp->right = ptr;
                temp->lthread = 1;
                temp->rthread = 1;

                ptr->left = temp;
                ptr->lthread = 0;
                return;
            }
            ptr = ptr->left;
        } else {
            if (ptr->rthread == 1) {
                temp = (struct Node *)malloc(sizeof(struct Node));
                temp->data = key;
                temp->right = ptr->right;
                temp->left = ptr;
                temp->lthread = 1;
                temp->rthread = 1;

                ptr->right = temp;
                ptr->rthread = 0;
                return;
            }
            ptr = ptr->right;
        }
    }
}

struct Node *leftmost(struct Node *ptr) {
    while (ptr->lthread == 0)
        ptr = ptr->left;
    return ptr;
}

void inorderTraversal() {
    struct Node *ptr;

    if (head->lthread == 1) {
        printf("Tree is empty!\n");
        return;
    }

    ptr = leftmost(head->left);

    printf("Inorder Traversal: ");

    while (ptr != head) {
        printf("%d ", ptr->data);

        if (ptr->rthread == 1)
            ptr = ptr->right;
        else
            ptr = leftmost(ptr->right);
    }

    printf("\n");
}

int main() {
    int n, i, value;

    initialize();

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter node values:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        insert(value);
    }

    printf("\nThreaded Binary Tree Traversal\n");
    inorderTraversal();

    return 0;
}
