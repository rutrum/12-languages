// Challenge 7
// Adjacency Matrix

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef bool matrix[5][5];

void add_edge(int a, int b, matrix graph) {
    graph[a][b] = true;
    graph[b][a] = true;
}

void remove_edge(int a, int b, matrix graph) {
    graph[a][b] = false;
    graph[b][a] = false;
}

void print_sol(int s[5]) {
    printf("%i %i %i %i %i\n", s[0], s[1], s[2], s[3], s[4]);
}

bool search_for(int v, int solution[5]) {
    for (int i = 0; i < 5; i++) {
        if (v == solution[i]) {
            return true;
        }
    }
    return false;
}

// starting at the start node, traverse the matrix graph
// until every node is found, recursing on a single node before moving
// to the next
void breadth_from(int start, matrix graph, int* solved, int solution[5]) {
    printf("searching at %i\n", start);
    
    // Check if every node has been found
    if (*solved == 5) return;

    for (int i = 0; i < 5; i += 1) {
        if (i == start) continue;
        if (graph[start][i]) {
            if (!search_for(i, solution)) {
                solution[*solved] = i;
                *solved += 1;
                breadth_from(i, graph, solved, solution);
            }
        }
    }
}

void breadth(matrix graph, int solution[5]) {
    solution[0] = 0;
    int solved = 1;
    breadth_from(0, graph, &solved, solution);
}

int main() {
    matrix graph = {0};
    add_edge(0, 1, graph);
    add_edge(1, 3, graph);
    add_edge(1, 4, graph);
    add_edge(2, 3, graph);
    add_edge(0, 3, graph);

    int path[5] = {0};
    breadth(graph, path);
    
    printf("%d", path[0]);
    int i = 1;
    while (i < 5 && path[i] > 0) {
        printf(", %d", path[i]);
        i += 1;
    }
    printf("\n");

    return EXIT_SUCCESS;
}
