
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

int preorderIndex = 0;

// Find position of element in inorder array
int search(int inorder[], int start, int end, int value)
{
    int i;

    for (i = start; i <= end; i++)
    {
        if (inorder[i] == value)
            return i;
    }

    return -1;
}

// Construct binary tree using inorder and preorder
struct Node* buildTree(int inorder[], int preorder[],
                       int start, int end)
{
    int position;
    struct Node *newNode;

    if (start > end)
        return NULL;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = preorder[preorderIndex++];

    if (start == end)
    {
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    position = search(inorder, start, end, newNode->data);

    if (position == -1)
    {
        printf("Invalid traversal data!\n");
        exit(1);
    }

    newNode->left = buildTree(inorder, preorder,
                              start, position - 1);

    newNode->right = buildTree(inorder, preorder,
                               position + 1, end);

    return newNode;
}

// Count leaf nodes
int countLeaves(struct Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaves(root->left) +
           countLeaves(root->right);
}

// Find height of binary tree
int height(struct Node *root)
{
    int leftHeight, rightHeight;

    if (root == NULL)
        return 0;

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

// Inorder traversal
void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Preorder traversal
void preorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Free allocated memory
void freeTree(struct Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main function
int main()
{
    int n, i;
    int inorder[100], preorder[100];
    struct Node *root;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid number of nodes!\n");
        return 1;
    }

    printf("Enter inorder traversal:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    printf("Enter preorder traversal:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &preorder[i]);

    preorderIndex = 0;

    root = buildTree(inorder, preorder, 0, n - 1);

    printf("\nConstructed Tree\n");

    printf("Inorder Traversal: ");
    inorderTraversal(root);

    printf("\nPreorder Traversal: ");
    preorderTraversal(root);

    printf("\nNumber of Leaf Nodes: %d", countLeaves(root));

    printf("\nHeight of Binary Tree: %d\n", height(root));

    freeTree(root);

    return 0;
}
