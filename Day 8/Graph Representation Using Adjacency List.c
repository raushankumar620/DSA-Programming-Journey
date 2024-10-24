#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// A structure to represent an adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// A structure to represent an adjacency list
struct Graph {
    int numVertices;
    struct Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];  // For DFS and BFS traversal
};

// Function to create a new node
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

    // Initialize the adjacency list for each vertex
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;  // Mark all vertices as unvisited
    }

    return graph;
}

// Function to add an edge to the graph (for undirected graph)
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add an edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to remove an edge from the graph
void removeEdge(struct Graph* graph, int src, int dest) {
    struct Node *temp = graph->adjLists[src], *prev = NULL;

    // Search for dest in the adjacency list of src
    while (temp != NULL && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }

    // If found, remove the node
    if (temp != NULL) {
        if (prev == NULL)
            graph->adjLists[src] = temp->next;
        else
            prev->next = temp->next;
        free(temp);
    }

    // Remove the reverse edge (since it's an undirected graph)
    temp = graph->adjLists[dest];
    prev = NULL;
    while (temp != NULL && temp->vertex != src) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev == NULL)
            graph->adjLists[dest] = temp->next;
        else
            prev->next = temp->next;
        free(temp);
    }
}

// Function to print the graph (adjacency list representation)
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("\n Vertex %d: ", v);
        while (temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// DFS algorithm
void DFS(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// BFS algorithm
void BFS(struct Graph* graph, int startVertex) {
    int queue[MAX_VERTICES], front = 0, rear = -1;

    graph->visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                queue[++rear] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// Function to reset the visited array for DFS/BFS traversal
void resetVisited(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// Main function
int main() {
    int vertices, choice, src, dest, startVertex;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    while (1) {
        printf("\nGraph Operations Menu:\n");
        printf("1. Add Edge\n");
        printf("2. Remove Edge\n");
        printf("3. Display Graph\n");
        printf("4. Depth First Search (DFS)\n");
        printf("5. Breadth First Search (BFS)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertex: ");
                scanf("%d %d", &src, &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                printf("Enter source and destination vertex to remove edge: ");
                scanf("%d %d", &src, &dest);
                removeEdge(graph, src, dest);
                break;
            case 3:
                printGraph(graph);
                break;
            case 4:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &startVertex);
                resetVisited(graph);
                printf("DFS Traversal: ");
                DFS(graph, startVertex);
                printf("\n");
                break;
            case 5:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &startVertex);
                resetVisited(graph);
                printf("BFS Traversal: ");
                BFS(graph, startVertex);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
