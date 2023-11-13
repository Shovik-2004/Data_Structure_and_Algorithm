#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEYS 100 // Define the maximum number of keys
#define MIN_DEGREE 2 // Define the minimum degree

struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode* children[MAX_KEYS + 1];
    int num_keys;
    bool leaf;
};

struct BTree {
    struct BTreeNode* root;
    int min_degree;
};

struct BTreeNode* createNode(bool leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->leaf = leaf;
    newNode->num_keys = 0;
    for (int i = 0; i <= MAX_KEYS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

struct BTree* createBTree(int t) {
    struct BTree* newTree = (struct BTree*)malloc(sizeof(struct BTree));
    newTree->root = NULL;
    newTree->min_degree = t;
    return newTree;
}

void traverse(struct BTreeNode* node) {
    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (node->leaf == false)
            traverse(node->children[i]);
        printf(" %d", node->keys[i]);
    }
    if (node->leaf == false)
        traverse(node->children[i]);
}

struct BTreeNode* search(struct BTreeNode* node, int k) {
    int i = 0;
    while (i < node->num_keys && k > node->keys[i])
        i++;

    if (node->keys[i] == k)
        return node;

    if (node->leaf == true)
        return NULL;

    return search(node->children[i], k);
}

void insert(struct BTree* tree, int key) {
    struct BTreeNode* root = tree->root;
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = key;
        root->num_keys = 1;
        tree->root = root;
    } else {
        if (root->num_keys == 2 * MIN_DEGREE - 1) {
            struct BTreeNode* newRoot = createNode(false);
            newRoot->children[0] = root;
            tree->root = newRoot;
            splitChild(newRoot, 0, root);
            insertNonFull(newRoot, key);
        } else {
            insertNonFull(root, key);
        }
    }
}

void insertNonFull(struct BTreeNode* node, int key) {
    int i = node->num_keys - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys = node->num_keys + 1;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->num_keys == 2 * MIN_DEGREE - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void splitChild(struct BTreeNode* parentNode, int index, struct BTreeNode* childNode) {
    struct BTreeNode* newNode = createNode(childNode->leaf);
    newNode->num_keys = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++)
        newNode->keys[j] = childNode->keys[j + MIN_DEGREE];

    if (childNode->leaf == false) {
        for (int j = 0; j < MIN_DEGREE; j++)
            newNode->children[j] = childNode->children[j + MIN_DEGREE];
    }

    childNode->num_keys = MIN_DEGREE - 1;

    for (int j = parentNode->num_keys; j >= index + 1; j--)
        parentNode->children[j + 1] = parentNode->children[j];

    parentNode->children[index + 1] = newNode;

    for (int j = parentNode->num_keys - 1; j >= index; j--)
        parentNode->keys[j + 1] = parentNode->keys[j];

    parentNode->keys[index] = childNode->keys[MIN_DEGREE - 1];
    parentNode->num_keys = parentNode->num_keys + 1;
}

void menu() {
    printf("Menu:\n");
    printf("1. Insert Key\n");
    printf("2. Search Key\n");
    printf("3. Traverse Tree\n");
    printf("4. Exit\n");
}

int main() {
    struct BTree* bTree = createBTree(MIN_DEGREE);
    int choice, key;

    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(bTree, key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(bTree->root, key) != NULL)
                    printf("Key %d is present in the tree.\n", key);
                else
                    printf("Key %d is not present in the tree.\n", key);
                break;
            case 3:
                printf("Tree Traversal: ");
                if (bTree->root != NULL)
                    traverse(bTree->root);
                printf("\n");
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
