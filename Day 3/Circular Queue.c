#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

struct CircularQueue {
    int items[SIZE];
    int front, rear;
};

void initialize(struct CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(struct CircularQueue* q) {
    if ((q->front == 0 && q->rear == SIZE - 1) || (q->rear == (q->front - 1) % (SIZE - 1))) {
        return 1;
    }
    return 0;
}

int isEmpty(struct CircularQueue* q) {
    if (q->front == -1) {
        return 1;
    }
    return 0;
}

void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue is Full! Cannot insert %d\n", value);
        return;
    }

    if (q->front == -1) {
        q->front = 0;
        q->rear = 0;
    } else if (q->rear == SIZE - 1 && q->front != 0) {
        q->rear = 0;
    } else {
        q->rear++;
    }

    q->items[q->rear] = value;
    printf("Inserted %d\n", value);
}

int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty! Cannot dequeue.\n");
        return -1;
    }

    int value = q->items[q->front];
    
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else if (q->front == SIZE - 1) {
        q->front = 0;
    } else {
        q->front++;
    }
    printf("Removed %d\n", value);
    return value;
}

void display(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue elements are: ");
    if (q->rear >= q->front) {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
    } else {
        for (int i = q->front; i < SIZE; i++) {
            printf("%d ", q->items[i]);
        }
        for (int i = 0; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
    }
    printf("\n");
}

int main() {
    struct CircularQueue q;
    initialize(&q);

    int choice, value;

    while (1) {
        printf("\nCircular Queue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);  // Exit the program
                break;
            default:
                printf("Invalid choice! Please choose a valid option.\n");
        }
    }

    return 0;
}
