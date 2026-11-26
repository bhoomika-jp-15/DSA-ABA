#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct node {
    int vertex;
    struct node *next;
};

struct node *adj[MAX];
int visited[MAX];
int n;

struct node *createNode(int v) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->vertex = v;
    temp->next = NULL;
    return temp;
}

void addEdge(int u, int v) {
    struct node *temp = createNode(v);
    temp->next = adj[u];
    adj[u] = temp;

    temp = createNode(u);
    temp->next = adj[v];
    adj[v] = temp;
}

void dfs(int v) {
    struct node *p;
    visited[v] = 1;
    printf("%d ", v);
    for (p = adj[v]; p != NULL; p = p->next) {
        if (!visited[p->vertex])
            dfs(p->vertex);
    }
}

void bfs(int start) {
    int queue[MAX], front = 0, rear = -1, i, v;
    struct node *p;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[++rear] = start;

    while (front <= rear) {
        v = queue[front++];
        printf("%d ", v);
        for (p = adj[v]; p != NULL; p = p->next) {
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                queue[++rear] = p->vertex;
            }
        }
    }
}

void display() {
    int i;
    struct node *p;
    for (i = 0; i < n; i++) {
        printf("%d -> ", i);
        for (p = adj[i]; p != NULL; p = p->next)
            printf("%d ", p->vertex);
        printf("\n");
    }
}

int main() {
    int i, edges, u, v, start, choice;

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++)
        adj[i] = NULL;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge as two vertices (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    while (1) {
        printf("\n--- Graph Traversal (Adjacency List) ---\n");
        printf("1. Display Adjacency List\n2. DFS\n3. BFS\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display();
                break;
            case 2:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);
                for (i = 0; i < n; i++)
                    visited[i] = 0;
                printf("DFS: ");
                dfs(start);
                printf("\n");
                break;
            case 3:
                printf("Enter starting vertex (0 to %d): ", n - 1);
                scanf("%d", &start);
                printf("BFS: ");
                bfs(start);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
