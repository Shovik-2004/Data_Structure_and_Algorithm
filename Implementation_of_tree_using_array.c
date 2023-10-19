#include <stdio.h>
#include <stdlib.h>

// Function to perform a preorder traversal of the binary tree represented as an array
void preorder(char tree[], int index, int size) {
    if (index < size && tree[index] != '\0') {
        printf(" %c ", tree[index]);
        preorder(tree, 2 * index + 1, size);
        preorder(tree, 2 * index + 2, size);
    }
}

// Function to perform a postorder traversal of the binary tree represented as an array
void postorder(char tree[], int index, int size) {
    if (index < size && tree[index] != '\0') {
        postorder(tree, 2 * index + 1, size);
        postorder(tree, 2 * index + 2, size);
        printf(" %c ", tree[index]);
    }
}

// Function to perform an inorder traversal of the binary tree represented as an array
void inorder(char tree[], int index, int size) {
    if (index < size && tree[index] != '\0') {
        inorder(tree, 2 * index + 1, size);
        printf(" %c ", tree[index]);
        inorder(tree, 2 * index + 2, size);
    }
}

int main() {
    char tree[15]; // Assuming a binary tree with a maximum of 15 nodes
    int size = sizeof(tree) / sizeof(tree[0]);

    for (int i = 0; i < size; i++) {
        tree[i] = '\0'; // Initialize the tree with null values
    }

    char input;
    int index = 0;

    printf("Enter nodes to build the binary tree (type 'q' to stop):\n");
    
    while (1) {
        scanf(" %c", &input);
        if (input == 'q') {
            break;
        }
        tree[index] = input;
        index++;
    }

    printf("Preorder:\n");
    preorder(tree, 0, size);
    printf("\nPostorder:\n");
    postorder(tree, 0, size);
    printf("\nInorder:\n");
    inorder(tree, 0, size);
    printf("\n");

    return 0;
}
