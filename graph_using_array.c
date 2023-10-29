#include <stdio.h>
#define V 4 /* number of vertices in the graph */

/* function to initialize the matrix to zero */
void init(int arr[][V]) {
    int i, j;
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            arr[i][j] = 0;
}

/* function to add edges to the graph */
void insertEdge(int arr[][V], int i, int j) {
    arr[i][j] = 1;
    arr[j][i] = 1;
}

/* function to print the matrix elements */
void printAdjMatrix(int arr[][V]) {
    int i, j;
    for (i = 0; i < V; i++) {
        printf("%d: ", i);
        for (j = 0; j < V; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int adjMatrix[V][V];

    init(adjMatrix);

    // Take user input for edges
    int numEdges;
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    if (numEdges < 0 || numEdges > V * (V - 1) / 2) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        printf("Enter edge %d (format: u v): ", i + 1);
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < V && v >= 0 && v < V) {
            insertEdge(adjMatrix, u, v);
        } else {
            printf("Invalid edge. Both u and v must be between 0 and %d.\n", V - 1);
            i--; // Decrement i to retry input for this edge
        }
    }

    printAdjMatrix(adjMatrix);

    return 0;
}
