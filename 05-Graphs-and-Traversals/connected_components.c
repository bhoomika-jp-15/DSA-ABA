#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int n;

void dfs(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i])
            dfs(i);
    }
}

int countComponents() {
    int i, count = 0;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            printf("Component %d: ", count);
            dfs(i);
            printf("\n");
        }
    }
    return count;
}

int main() {
    int i, j, edges, u, v, components;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge as two vertices (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    components = countComponents();

    printf("\nNumber of connected components: %d\n", components);
    if (components == 1)
        printf("The graph is CONNECTED\n");
    else
        printf("The graph is NOT CONNECTED\n");

    return 0;
}
