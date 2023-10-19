#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new binary tree node
struct TreeNode* createNode(char data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary tree
void insert(struct TreeNode** root, char data) {
    if (*root == NULL) {
        *root = createNode(data);
    } else if (data < (*root)->data) {
        insert(&((*root)->left), data);
    } else {
        insert(&((*root)->right), data);
    }
}

void preorder(struct TreeNode* root) {
    if (root != NULL) {
        printf(" %c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf(" %c ", root->data);
    }
}

void inorder(struct TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf(" %c ", root->data);
        inorder(root->right);
    }
}

void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct TreeNode* root = NULL;
    char input;
    printf("Enter nodes to build the binary tree (type 'q' to stop):\n");
    
    while (1) {
        scanf(" %c", &input);
        if (input == 'q') {
            break;
        }
        insert(&root, input);
    }

    printf("Preorder:\n");
    preorder(root);
    printf("\nPostorder:\n");
    postorder(root);
    printf("\nInorder:\n");
    inorder(root);
    printf("\n");

    // Free allocated memory
    freeTree(root);

    return 0;
}
