#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for lift
struct Lift {
    int queue[MAX];       // Array to store floor requests
    int current_floor;     // Current floor of the lift
    int size;              // Number of requests in the queue
};

// Initialize the lift
void initLift(struct Lift* lift) {
    lift->current_floor = 0;
    lift->size = 0;
}

// Request a floor
void requestFloor(struct Lift* lift, int floor) {
    if (lift->size < MAX) {
        lift->queue[lift->size++] = floor;
        printf("Floor %d requested.\n", floor);
    } else {
        printf("Queue is full. Cannot request more floors.\n");
    }
}

// Move the lift to the next floor in the queue
void moveLift(struct Lift* lift) {
    if (lift->size == 0) {
        printf("No more requests. Lift is idle at floor %d.\n", lift->current_floor);
    } else {
        int next_floor = lift->queue[0];
        printf("Lift moving from floor %d to floor %d.\n", lift->current_floor, next_floor);
        lift->current_floor = next_floor;

        // Shift all elements in the queue
        for (int i = 1; i < lift->size; i++) {
            lift->queue[i - 1] = lift->queue[i];
        }
        lift->size--;
    }
}

// Display pending floor requests
void displayQueue(struct Lift* lift) {
    if (lift->size == 0) {
        printf("No pending floor requests. Lift is idle.\n");
    } else {
        printf("Pending floor requests: ");
        for (int i = 0; i < lift->size; i++) {
            printf("%d ", lift->queue[i]);
        }
        printf("\n");
    }
}

int main() {
    struct Lift lift;
    initLift(&lift);

    int choice, floor;
    
    while (1) {
        printf("\n--- Lift Management System ---\n");
        printf("1. Request Lift to a floor\n");
        printf("2. Move Lift to the next floor\n");
        printf("3. Display pending floor requests\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the floor number to request the lift: ");
                scanf("%d", &floor);
                requestFloor(&lift, floor);
                break;
            case 2:
                moveLift(&lift);
                break;
            case 3:
                displayQueue(&lift);
                break;
            case 4:
                printf("Exiting Lift Management System...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
