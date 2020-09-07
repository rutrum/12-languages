// Challenge 7
// Adjacency Matrix

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void breadth(int start, int end, bool graph[5][5], int solution[5]) {
    int j = 0;
    int cur = start;
    solution[j] = cur;
    j += 1;
    while (cur != end && j < 5) {
        for (int i = 0; i < 5; i += 1) {
            //if (i == cur) continue;
            printf("[%d][%d] = %d\n", cur, i, graph[cur][i]);
            if (graph[cur][i]) {
                
                // check to see if already in solution
                bool seen = false;
                for (int k = 0; k < j; k++) {
                    if (solution[k] == i) {
                        seen = true;
                        break;
                    }
                }

                if (!seen) {
                    solution[j] = i;
                    j += 1;
                    cur = i;
                    break;
                }
            }
        }
    }
}

int main() {
    bool graph[5][5] = {0};
    graph[1][2] = 1;
    graph[2][1] = 1;
    graph[0][2] = 1;
    graph[2][0] = 1;
    graph[0][3] = 1;
    graph[0][3] = 1;

    int path[5] = {0};
    breadth(0, 3, graph, path);
    
    printf("%d", path[0]);
    int i = 1;
    while (i < 5 && path[i] > 0) {
        printf(" -> %d", path[i]);
        i += 1;
    }
    printf("\n");

    return EXIT_SUCCESS;
}
