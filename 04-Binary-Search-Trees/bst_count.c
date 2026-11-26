#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node *createNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node *insert(struct node *root, int key) {
    if (root == NULL)
        return createNode(key);
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        printf("Duplicate %d not inserted\n", key);
    return root;
}

int countNodes(struct node *root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(struct node *root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int height(struct node *root) {
    int lh, rh;
    if (root == NULL)
        return -1;
    lh = height(root->left);
    rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

int findMin(struct node *root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findMax(struct node *root) {
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct node *root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- BST Count Operations ---\n");
        printf("1. Insert\n2. Inorder Display\n3. Count Nodes\n4. Count Leaves\n");
        printf("5. Height\n6. Minimum\n7. Maximum\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                if (root == NULL)
                    printf("Tree is empty\n");
                else {
                    printf("Inorder: ");
                    inorder(root);
                    printf("\n");
                }
                break;
            case 3:
                printf("Total nodes: %d\n", countNodes(root));
                break;
            case 4:
                printf("Leaf nodes: %d\n", countLeaves(root));
                break;
            case 5:
                if (root == NULL)
                    printf("Tree is empty\n");
                else
                    printf("Height of tree: %d\n", height(root));
                break;
            case 6:
                if (root == NULL)
                    printf("Tree is empty\n");
                else
                    printf("Minimum value: %d\n", findMin(root));
                break;
            case 7:
                if (root == NULL)
                    printf("Tree is empty\n");
                else
                    printf("Maximum value: %d\n", findMax(root));
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
