#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

// Function to find the vertex with the minimum distance
int minDistance(int dist[], int visited[], int V) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

// Dijkstra's algorithm to find the shortest path from src to all vertices
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[V];      // The output array. dist[i] will hold the shortest distance from src to i
    int visited[V];   // visited[i] will be true if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited, V);

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Update dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] if it's not visited, there is an edge from u to v, 
            // and the total weight of path from src to v through u is smaller than the current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distances
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

int main() {
    int V, src;
    int graph[MAX][MAX];

    // Input number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Input the adjacency matrix
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input the source vertex
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    // Call Dijkstra's algorithm
    dijkstra(graph, V, src);

    return 0;
}
