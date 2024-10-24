#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
int isEmpty(struct Node* top) {
    return top == NULL;
}
void push(struct Node** top, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) {
        return;
    }
    newNode->next = *top;  
    *top = newNode;        
    printf("%d pushed to stack\n", data);
}
int pop(struct Node** top) {
    if (isEmpty(*top)) {
        printf("Stack underflow\n");
        return -1;  
    }
    struct Node* temp = *top;
    *top = (*top)->next; 
    int poppedData = temp->data;
    free(temp);  
    return poppedData;
}
int peek(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}
void display(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty\n");
        return;
    }
    struct Node* temp = top;
    printf("Stack elements are: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
int main() {
    struct Node* stack = NULL;  
    int choice, value;
    while (1) {
        printf("\n-- Stack Menu --\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
            case 2:
                value = pop(&stack);
                if (value != -1)
                    printf("%d popped from stack\n", value);
                break;
            case 3:
                value = peek(stack);
                if (value != -1)
                    printf("Top element is %d\n", value);
                break;
            case 4:
                display(stack);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);  // Exit the program
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
