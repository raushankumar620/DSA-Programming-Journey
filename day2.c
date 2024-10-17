#include <stdio.h>

#define MAXSIZE 10

int Queue[MAXSIZE];
int front = 0;
int rear = -1;

void Insert();  
void Delete();
void Display();
void Peek();  

int main() {
    int choice;
    do {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Peek\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); 
        switch (choice) {
            case 1: 
                Insert();
                break;
            case 2: 
                Delete();
                break;
            case 3: 
                Display();
                break;    
            case 4: 
                Peek();
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

void Insert() {
    int n;
    if (rear == MAXSIZE - 1) {
        printf("Queue overflow\n");  
    } else {
        printf("Enter an element to push: ");
        scanf("%d", &n);
        rear++;
        Queue[rear] = n;
        printf("Element %d pushed to the queue.\n", n);
    }
}

void Delete() {
    if (front > rear) {  
        printf("Queue underflow\n");
        front = 0;       
        rear = -1;
    } else {
        printf("Popped element: %d\n", Queue[front]);
        front++;         // Move front forward
    }
}

void Display() {
    if (front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", Queue[i]);
        }
        printf("\n");
    }
}

void Peek() {
    if (front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("Front element is: %d\n", Queue[front]);
    }
}