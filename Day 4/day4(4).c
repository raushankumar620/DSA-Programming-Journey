#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Deque {
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
    newNode->next = newNode->prev = NULL;
    return newNode;
}

struct Deque* createDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    if (!deque) {
        printf("Memory allocation error\n");
        return NULL;
    }
    deque->front = deque->rear = NULL;
    return deque;
}

int isEmpty(struct Deque* deque) {
    return deque->front == NULL;
}

void insertFront(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) return;

    if (isEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }

    printf("%d inserted at front\n", data);
}

void insertRear(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (!newNode) return;

    if (isEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }

    printf("%d inserted at rear\n", data);
}

int deleteFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque underflow\n");
        return -1;
    }

    struct Node* temp = deque->front;
    int data = temp->data;

    if (deque->front == deque->rear) {
        deque->front = deque->rear = NULL;
    } else {
        deque->front = deque->front->next;
        deque->front->prev = NULL;
    }

    free(temp);
    return data;
}

int deleteRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque underflow\n");
        return -1;
    }

    struct Node* temp = deque->rear;
    int data = temp->data;

    if (deque->front == deque->rear) {
        deque->front = deque->rear = NULL;
    } else {
        deque->rear = deque->rear->prev;
        deque->rear->next = NULL;
    }

    free(temp);
    return data;
}

int getFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    return deque->front->data;
}

int getRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    return deque->rear->data;
}

void display(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }

    struct Node* temp = deque->front;
    printf("Deque elements are: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Deque* deque = createDeque();
    int choice, value;

    while (1) {
        printf("\n-- Deque Menu --\n");
        printf("1. Insert at front\n");
        printf("2. Insert at rear\n");
        printf("3. Delete from front\n");
        printf("4. Delete from rear\n");
        printf("5. Get front element\n");
        printf("6. Get rear element\n");
        printf("7. Display deque\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(deque, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(deque, value);
                break;
            case 3:
                value = deleteFront(deque);
                if (value != -1)
                    printf("%d deleted from front\n", value);
                break;
            case 4:
                value = deleteRear(deque);
                if (value != -1)
                    printf("%d deleted from rear\n", value);
                break;
            case 5:
                value = getFront(deque);
                if (value != -1)
                    printf("Front element is %d\n", value);
                break;
            case 6:
                value = getRear(deque);
                if (value != -1)
                    printf("Rear element is %d\n", value);
                break;
            case 7:
                display(deque);
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}