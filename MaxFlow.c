#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V] = {false};
    int queue[V], front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = true;
    parent[s] = -1;
    
    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v, rGraph[V][V], parent[V], max_flow = 0;
    
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
    
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    printf("Maximum Flow: %d\n", fordFulkerson(graph, 0, 5));
    return 0;
}
