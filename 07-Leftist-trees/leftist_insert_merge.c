#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int npl; // Null Path Length
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

    // Maintain min-heap property
    if (h1->data > h2->data) {
        struct Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }

    h1->right = merge(h1->right, h2);

    // Enforce leftist property: NPL(left) >= NPL(right)
    if (getNPL(h1->left) < getNPL(h1->right)) {
        swapChildren(h1);
    }

    h1->npl = getNPL(h1->right) + 1;
    return h1;
}

struct Node* insert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    return merge(root, newNode);
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d(NPL:%d) ", root->data, root->npl);
        inorder(root->right);
    }
}

int main() {
    struct Node *tree1 = NULL, *tree2 = NULL, *mergedTree = NULL;
    int n1, n2, val;

    printf("Enter number of elements for Leftist Tree 1: ");
    scanf("%d", &n1);
    printf("Enter elements: ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        tree1 = insert(tree1, val);
    }

    printf("Enter number of elements for Leftist Tree 2: ");
    scanf("%d", &n2);
    printf("Enter elements: ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        tree2 = insert(tree2, val);
    }

    printf("\nInorder traversal of Tree 1: ");
    inorder(tree1);

    printf("\nInorder traversal of Tree 2: ");
    inorder(tree2);

    mergedTree = merge(tree1, tree2);
    printf("\nInorder traversal after Merging Tree 1 & Tree 2: ");
    inorder(mergedTree);
    printf("\n");

    return 0;
}
