#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void createNode(struct Node** head, int value);
void insertAtBeginning(struct Node** head, int value);
void insertAtEnd(struct Node** head, int value);
void insertAfter(struct Node* prevNode, int value);
void deleteByValue(struct Node** head, int value);
void deleteAtPosition(struct Node** head, int position);
void displayList(struct Node* head);

void createNode(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;  
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;  
        }
        temp->next = newNode;  
    }
    printf("Node with value %d created.\n", value);
}

void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at the beginning.\n", value);
}

void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Inserted %d at the end.\n", value);
}

void insertAfter(struct Node* prevNode, int value) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    printf("Inserted %d after node with value %d.\n", value, prevNode->data);
}

void deleteByValue(struct Node** head, int value) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == value) {
        *head = temp->next;  
        free(temp);          
        printf("Node with value %d deleted.\n", value);
        return;
    }while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Node with value %d not found.\n", value);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Node with value %d deleted.\n", value);
}

void deleteAtPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = *head;
    if (position == 0) {
        *head = temp->next; 
        free(temp);         
        printf("Node at position %d deleted.\n", position);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position %d does not exist.\n", position);
        return;
    }
    struct Node* next = temp->next->next;
    free(temp->next);  
    temp->next = next; 
    printf("Node at position %d deleted.\n", position);
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL; 
    int choice, value, pos;

    do {
        printf("\n--- Linked List Menu ---\n");
        printf("1. Create Node\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at End\n");
        printf("4. Insert After a Node\n");
        printf("5. Delete by Value\n");
        printf("6. Delete by Position\n");
        printf("7. Display List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to create node: ");
                scanf("%d", &value);
                createNode(&head, value);
                break;
            case 2:
                printf("Enter value to insert at the beginning: ");
                scanf("%d", &value);
                insertAtBeginning(&head, value);
                break;
            case 3:
                printf("Enter value to insert at the end: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;
            case 4:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter position after which to insert (0-based): ");
                scanf("%d", &pos);
                struct Node* temp = head;
                for (int i = 0; i < pos && temp != NULL; i++) {
                    temp = temp->next;
                }
                if (temp != NULL) {
                    insertAfter(temp, value);
                } else {
                    printf("Invalid position.\n");
                }
                break;
            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(&head, value);
                break;
            case 6:
                printf("Enter position to delete (0-based): ");
                scanf("%d", &pos);
                deleteAtPosition(&head, pos);
                break;
            case 7:
                displayList(head);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 8);

    return 0;
}