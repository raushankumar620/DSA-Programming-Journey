#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  
struct Deque {
    int items[SIZE];
    int front;
    int rear;
};
void initializeDeque(struct Deque* dq);
int isFull(struct Deque* dq);
int isEmpty(struct Deque* dq);
void insertFront(struct Deque* dq, int value);
void insertRear(struct Deque* dq, int value);
void deleteFront(struct Deque* dq);
void deleteRear(struct Deque* dq);
void displayDeque(struct Deque* dq);
void initializeDeque(struct Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
}
int isFull(struct Deque* dq) {
    return (dq->front == 0 && dq->rear == SIZE - 1) || (dq->front == dq->rear + 1);
}
int isEmpty(struct Deque* dq) {
    return dq->front == -1;
}
void insertFront(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert %d at the front.\n", value);
        return;
    }
    if (dq->front == -1) {  
        dq->front = dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = SIZE - 1;  
    } else {
        dq->front--;
    }
    dq->items[dq->front] = value;
    printf("Inserted %d at the front.\n", value);
}
void insertRear(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert %d at the rear.\n", value);
        return;
    }
    if (dq->front == -1) {  
        dq->front = dq->rear = 0;
    } else if (dq->rear == SIZE - 1) {
        dq->rear = 0;  
    } else {
        dq->rear++;
    }
    dq->items[dq->rear] = value;
    printf("Inserted %d at the rear.\n", value);
}
void deleteFront(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from the front.\n");
        return;
    }
    printf("Deleted %d from the front.\n", dq->items[dq->front]);
    if (dq->front == dq->rear) { 
        dq->front = dq->rear = -1;  
    } else if (dq->front == SIZE - 1) {
        dq->front = 0;  
    } else {
        dq->front++;
    }
}
void deleteRear(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from the rear.\n");
        return;
    }
    printf("Deleted %d from the rear.\n", dq->items[dq->rear]);
    if (dq->front == dq->rear) {  
        dq->front = dq->rear = -1; 
    } else if (dq->rear == 0) {
        dq->rear = SIZE - 1; 
    } else {
        dq->rear--;
    }
}
void displayDeque(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->items[i]);
        if (i == dq->rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}
int main() {
    struct Deque dq;
    initializeDeque(&dq);

    int choice, value;
    do {
        printf("\nDeque Operations Menu:\n");
        printf("1. Insert at front\n");
        printf("2. Insert at rear\n");
        printf("3. Delete from front\n");
        printf("4. Delete from rear\n");
        printf("5. Display deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&dq, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&dq, value);
                break;
            case 3:
                deleteFront(&dq);
                break;
            case 4:
                deleteRear(&dq);
                break;
            case 5:
                displayDeque(&dq);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}