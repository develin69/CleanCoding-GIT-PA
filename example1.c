/* Clean version of example1.c - Check if a direct connection exists between two nodes in a graph */

#include <stdio.h>
#include <stdlib.h>

// Node in adjacency list
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

// Graph structure
typedef struct Graph {
    int vertices;
    int *visited;
    NODE **adj_list;
} GPH;

// Create a new node
NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Create a new graph
GPH *create_graph(int vertices) {
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adj_list = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adj_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Add edge (undirected)
void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

// DFS traversal to check path
int dfs_path_exists(GPH *graph, int src, int target) {
    if (src == target) return 1;

    graph->visited[src] = 1;
    NODE *temp = graph->adj_list[src];

    while (temp != NULL) {
        int neighbor = temp->data;
        if (!graph->visited[neighbor]) {
            if (dfs_path_exists(graph, neighbor, target)) {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

// Reset visited array
void reset_visited(GPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

int main() {
    int vertices, edges;
    printf("Number of locations (nodes): ");
    scanf("%d", &vertices);

    GPH *graph = create_graph(vertices);

    printf("Number of roads (edges): ");
    scanf("%d", &edges);

    printf("Enter each road (source destination):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    int rest1, rest2;
    printf("Enter two restaurants to check connection: ");
    scanf("%d %d", &rest1, &rest2);

    int exists = dfs_path_exists(graph, rest1, rest2);
    printf("%s\n", exists ? "Path exists between restaurants." : "No direct path between restaurants.");

    return 0;
}
