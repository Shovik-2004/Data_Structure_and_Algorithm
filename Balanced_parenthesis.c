#include <stdio.h>
#include <stdlib.h>

// Structure of a stack node
struct sNode {
    char data;
    struct sNode* next;
};

// Function to push a character onto the stack
void push(struct sNode** top_ref, char new_data);

// Function to pop a character from the stack
char pop(struct sNode** top_ref);

// Returns 1 if character1 and character2 are matching left and right brackets
int isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}

// Return 1 if expression has balanced brackets
int areBracketsBalanced(char exp[]) {
    int i = 0;

    // Declare an empty character stack
    struct sNode* stack = NULL;

    // Traverse the given expression to check matching brackets
    while (exp[i]) {
        // If the exp[i] is a starting bracket, push it
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
            push(&stack, exp[i]);

        // If exp[i] is an ending bracket, pop from stack and check if it's a matching pair
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (stack == NULL)
                return 0; // Unmatched closing bracket
            else if (!isMatchingPair(pop(&stack), exp[i]))
                return 0; // Mismatched brackets
        }
        i++;
    }

    // If the stack is empty, all brackets were matched
    return stack == NULL;
}

// Driver code
int main() {
    int num;

    //for (int i = 0; i < num; i++) {
        char exp[100];
        printf("Enter expression: ");
        scanf("%s", exp);

        if (areBracketsBalanced(exp))
            printf("Expression  is Balanced\n");
        else
            printf("Expression is Not Balanced\n");
    
    
    return 0;

}
// Function to push a character onto the stack
void push(struct sNode** top_ref, char new_data) {
    // Allocate node
    struct sNode* new_node = (struct sNode*)malloc(sizeof(struct sNode));

    if (new_node == NULL) {
        printf("Stack overflow\n");
        exit(0);
    }

    // Put in the data
    new_node->data = new_data;

    // Link the old list to the new node
    new_node->next = (*top_ref);

    // Move the head to point to the new node
    (*top_ref) = new_node;
}

// Function to pop a character from the stack
char pop(struct sNode** top_ref) {
    char res;
    struct sNode* top;

    // If stack is empty, return an error character
    if (*top_ref == NULL) {
        printf("Stack underflow\n");
        exit(0);
    } else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}
