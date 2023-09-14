#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node* head = NULL;

void create();
void display();
void insert_beg();
void insert_pos();
void insert_end();
void delete_beg();
void delete_pos();
void delete_end();

int main() {
    int choice;
    while (1) {
        printf("\n****************************\n");
        printf("1. Create\n");
        printf("2. Display\n");
        printf("3. Insert at the beginning\n");
        printf("4. Insert after a position\n");
        printf("5. Insert at the end of the list\n");
        printf("6. Delete from the beginning\n");
        printf("7. Delete a particular element in the middle\n");
        printf("8. Delete the last element\n");
        printf("9. Exit\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                insert_beg();
                break;
            case 4:
                insert_pos();
                break;
            case 5:
                insert_end();
                break;
            case 6:
                delete_beg();
                break;
            case 7:
                delete_pos();
                break;
            case 8:
                delete_end();
                break;
            case 9:
                exit(0);
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
}

void create() {
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    printf("Enter node data: ");
    scanf("%d", &temp->data);
    temp->next = NULL;
    temp->prev = NULL;
    if (head == NULL)
        head = temp;
    else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
        temp->prev = ptr;
    }
}

void display() {
    struct node* ptr = head;
    if (ptr == NULL) {
        printf("Linked list is empty\n");
        return;
    }
    printf("Linked list: ");
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void insert_beg() {
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    printf("Enter node data: ");
    scanf("%d", &temp->data);
    temp->next = head;
    temp->prev = NULL;
    if (head != NULL) {
        head->prev = temp;
    }
    head = temp;
}

void insert_pos() {
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    printf("Enter node data: ");
    scanf("%d", &temp->data);
    temp->next = NULL;
    temp->prev = NULL;

    int pos;
    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos == 0) {
        temp->next = head;
        temp->prev = NULL;
        if (head != NULL) {
            head->prev = temp;
        }
        head = temp;
        return;
    }

    struct node* ptr = head;
    for (int i = 0; i < pos - 1; i++) {
        if (ptr == NULL) {
            printf("Invalid position\n");
            free(temp);
            return;
        }
        ptr = ptr->next;
    }

    if (ptr == NULL) {
        printf("Invalid position\n");
        free(temp);
        return;
    }

    temp->next = ptr->next;
    temp->prev = ptr;
    if (ptr->next != NULL) {
        ptr->next->prev = temp;
    }
    ptr->next = temp;
}

void insert_end() {
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    printf("Enter node data: ");
    scanf("%d", &temp->data);
    temp->next = NULL;
    temp->prev = NULL;
    if (head == NULL) {
        head = temp;
        return;
    }
    struct node* ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = temp;
    temp->prev = ptr;
}

void delete_beg() {
    if (head == NULL) {
        printf("Linked list is empty. Nothing to delete\n");
        return;
    }
    struct node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
}

void delete_end() {
    if (head == NULL) {
        printf("Linked list is empty\n");
        return;
    }
    struct node* ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    if (ptr->prev != NULL) {
        ptr->prev->next = NULL;
    } else {
        head = NULL;
    }
    free(ptr);
}

void delete_pos() {
    int pos;
    printf("Enter node position to delete: ");
    scanf("%d", &pos);
    if (head == NULL) {
        printf("Linked list is empty\n");
        return;
    }
    if (pos == 0) {
        struct node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
        return;
    }
    struct node* ptr = head;
    for (int i = 0; i < pos; i++) {
        if (ptr == NULL) {
            printf("Invalid position\n");
            return;
        }
        ptr = ptr->next;
    }
    if (ptr == NULL) {
        printf("Invalid position\n");
        return;
    }
    if (ptr->prev != NULL) {
        ptr->prev->next = ptr->next;
    } else {
        head = ptr->next;
    }
    if (ptr->next != NULL) {
        ptr->next->prev = ptr->prev;
    }
    free(ptr);
}
