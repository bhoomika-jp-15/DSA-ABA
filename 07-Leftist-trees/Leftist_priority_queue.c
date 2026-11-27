#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int npl;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->npl = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int getNPL(struct Node* node) {
    return (node == NULL) ? -1 : node->npl;
}

void swapChildren(struct Node* root) {
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

struct Node* merge(struct Node* h1, struct Node* h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    if (h1->data > h2->data) {
        struct Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    h1->right = merge(h1->right, h2);

    if (getNPL(h1->left) < getNPL(h1->right)) {
        swapChildren(h1);
    }

    h1->npl = getNPL(h1->right) + 1;
    return h1;
}

struct Node* enqueue(struct Node* root, int data) {
    return merge(root, createNode(data));
}

struct Node* deleteMin(struct Node* root) {
    if (root == NULL) {
        printf("Priority Queue is empty!\n");
        return NULL;
    }
    printf("Deleted min element: %d\n", root->data);
    struct Node* leftSubtree = root->left;
    struct Node* rightSubtree = root->right;
    free(root);
    return merge(leftSubtree, rightSubtree);
}

void display(struct Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}

int main() {
    struct Node* pq = NULL;
    int choice, val;

    while (1) {
        printf("\n--- Leftist Tree Priority Queue ---\n");
        printf("1. Enqueue (Insert)\n");
        printf("2. Delete-Min\n");
        printf("3. Peek Min\n");
        printf("4. Display (Inorder)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                pq = enqueue(pq, val);
                break;
            case 2:
                pq = deleteMin(pq);
                break;
            case 3:
                if (pq != NULL)
                    printf("Minimum element: %d\n", pq->data);
                else
                    printf("Priority Queue is empty!\n");
                break;
            case 4:
                if (pq == NULL) {
                    printf("Priority Queue is empty!\n");
                } else {
                    printf("Elements (Inorder): ");
                    display(pq);
                    printf("\n");
                }
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
