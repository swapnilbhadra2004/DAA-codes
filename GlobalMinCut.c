#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 4

int find(int parent[], int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int kargerMinCut(int graph[V][V]) {
    int parent[V], rank[V];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int remainingVertices = V;
    while (remainingVertices > 2) {
        int u, v;
        do {
            u = rand() % V;
            v = rand() % V;
        } while (graph[u][v] == 0 || find(parent, u) == find(parent, v));
        
        unionSets(parent, rank, u, v);
        remainingVertices--;
    }
    
    int cutEdges = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] && find(parent, i) != find(parent, j))
                cutEdges++;
        }
    }
    return cutEdges / 2;
}

int main() {
    srand(time(NULL));
    int graph[V][V] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    
    printf("Minimum Cut: %d\n", kargerMinCut(graph));
    return 0;
}
