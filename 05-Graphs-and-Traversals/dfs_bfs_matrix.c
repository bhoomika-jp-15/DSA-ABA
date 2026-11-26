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

void bfs(int start) {
    int queue[MAX], front = 0, rear = -1, i, v;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[++rear] = start;

    while (front <= rear) {
        v = queue[front++];
        printf("%d ", v);
        for (i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

int main() {
    int i, j, start, choice;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    while (1) {
        printf("\n--- Graph Traversal (Adjacency Matrix) ---\n");
        printf("1. DFS\n2. BFS\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);
                for (i = 0; i < n; i++)
                    visited[i] = 0;
                printf("DFS: ");
                dfs(start);
                printf("\n");
                break;
            case 2:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);
                printf("BFS: ");
                bfs(start);
                printf("\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
