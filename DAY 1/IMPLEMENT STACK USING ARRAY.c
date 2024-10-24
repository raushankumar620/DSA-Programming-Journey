#include <stdio.h>
#define MAXSIZE 10

int stack[MAXSIZE];
int top = -1;

void push();  
void pop();
void display();
void peek();  

int main() {
    int choice;
    do {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Peek\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); 
        switch (choice) {
            case 1: 
                push();
                break;
            case 2: 
                pop();
                break;
            case 3: 
                display();
                break;    
            case 4: 
                peek();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please choose a valid option.\n");
        }
    } while (choice != 5);  
    return 0;
}

void push() {
    int n;
    if (top == MAXSIZE - 1) {
        printf("Stack overflow\n");  
    } else {
        printf("Enter an element to push: ");
        scanf("%d", &n);
        top++;
        stack[top] = n;
    }
}

void pop() {
    if (top == -1) {
        printf("Stack underflow\n");  
    } else {
        printf("Popped element: %d\n", stack[top]);
        top--;
    }
}

void display() {
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

void peek() {
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Top element is: %d\n", stack[top]);
    }
}
