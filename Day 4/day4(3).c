#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct CircularQueue {
    struct Node* front;
    struct Node* rear;
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

struct CircularQueue* createQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (!queue) {
        printf("Memory allocation error\n");
        return NULL;
    }
    queue->front = queue->rear = NULL;
    return queue;
}

int isEmpty(struct CircularQueue* queue) {
    return queue->front == NULL;
}

void enqueue(struct CircularQueue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) return;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        queue->rear->next = queue->front;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
        queue->rear->next = queue->front;
    }

    printf("%d enqueued to circular queue\n", data);
}

int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }

    int data;
    struct Node* temp = queue->front;

    if (queue->front == queue->rear) {
        data = temp->data;
        free(temp);
        queue->front = queue->rear = NULL;
    } else {
        data = temp->data;
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
        free(temp);
    }

    return data;
}

int peek(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->data;
}

void display(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    struct Node* temp = queue->front;
    printf("Circular Queue elements are: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->front);
    printf("\n");
}

int main() {
    struct CircularQueue* queue = createQueue();
    int choice, value;

    while (1) {
        printf("\n-- Circular Queue Menu --\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                value = dequeue(queue);
                if (value != -1)
                    printf("%d dequeued from circular queue\n", value);
                break;
            case 3:
                value = peek(queue);
                if (value != -1)
                    printf("Front element is %d\n", value);
                break;
            case 4:
                display(queue);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}