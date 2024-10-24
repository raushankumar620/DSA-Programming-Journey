#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// A structure to represent an adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// A structure to represent a graph
struct Graph {
    int numVertices;
    struct Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];  // Array to keep track of visited nodes
};

// A structure to represent a queue
struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

// Function to create a new node in the adjacency list
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;  // Mark all vertices as unvisited initially
    }

    return graph;
}

// Function to add an edge to the graph (for undirected graph)
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add an edge from dest to src (because the graph is undirected)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to create a queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}

// Enqueue (add an element to the queue)
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX_VERTICES - 1)
        printf("\nQueue is full!!");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Dequeue (remove an element from the queue)
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// Function to perform BFS on a graph using a queue
void BFS(struct Graph* graph, int startVertex) {
    struct Queue* queue = createQueue();

    // Mark the start vertex as visited and enqueue it
    graph->visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        // Dequeue a vertex and print it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            // If the adjacent vertex has not been visited, mark it as visited and enqueue it
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Function to reset visited array for future traversals
void resetVisited(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// Main function to demonstrate BFS
int main() {
    int vertices, choice, src, dest, startVertex;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    while (1) {
        printf("\nGraph Operations Menu:\n");
        printf("1. Add Edge\n");
        printf("2. Display BFS Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertex: ");
                scanf("%d %d", &src, &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &startVertex);
                resetVisited(graph);  // Reset visited array for fresh traversal
                printf("BFS Traversal starting from vertex %d: ", startVertex);
                BFS(graph, startVertex);
                printf("\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
