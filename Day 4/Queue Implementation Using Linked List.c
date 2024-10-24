#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node *front, *rear;
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

// Function to create an empty Queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) {
        printf("Memory allocation error\n");
        return NULL;
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to add an element to the queue (enqueue)
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) return;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        printf("%d enqueued to queue\n", data);
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
    printf("%d enqueued to queue\n", data);
}

// Function to remove an element from the queue (dequeue)
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    int dequeuedData = temp->data;
    free(temp);
    return dequeuedData;
}

// Function to get the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->data;
}

// Function to display all elements in the queue
void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    struct Node* temp = queue->front;
    printf("Queue elements are: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Queue* queue = createQueue();
    int choice, value;

    while (1) {
        printf("\n-- Queue Menu --\n");
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
                    printf("%d dequeued from queue\n", value);
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
                exit(0);  // Exit the program
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
