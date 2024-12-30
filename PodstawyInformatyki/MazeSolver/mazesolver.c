#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000 // Maximum size of the maze
#define CYCLE_CHANCE 0.1 // Chance to create a cycle in the maze (10%)

double minPathWeight = 1e9; // Large initial value for the shortest path
int bestPath[MAX_SIZE * MAX_SIZE]; // Array to store the shortest path
int bestPathLength = 0; // Length of the shortest path

// Structure to store neighbor information as a linked list
typedef struct Node {
    int neighbor; // Index of the neighbor
    struct Node* next; // Pointer to the next neighbor
} Node;

// Structure representing a cell in the maze, containing a value and a list of neighbors
typedef struct {
    double value; // Random value assigned to the cell
    Node* neighbors; // List of neighboring cells
} Cell;

Cell maze[MAX_SIZE * MAX_SIZE]; // Array representing the maze
int n, entry, exitt; // Maze size, entry point, and exit point

// Function to check if two vertices are neighbors by searching the neighbor list
int isNeighbor(int u, int v) {
    Node* current = maze[u].neighbors;
    while (current) {
        if (current->neighbor == v) return 1; // Neighbor found
        current = current->next;
    }
    return 0; // No neighbor
}

// Function to check if adding an edge between u and v creates a 2x2 room
int createsRoom2x2(int u, int v) {
    Node* neighborsU = maze[u].neighbors;
    while (neighborsU) {
        int neighborU = neighborsU->neighbor;
        Node* neighborsV = maze[v].neighbors;
        while (neighborsV) {
            int neighborV = neighborsV->neighbor;
            if (isNeighbor(neighborU, neighborV)) {
                return 1; // A 2x2 room is created
            }
            neighborsV = neighborsV->next;
        }
        neighborsU = neighborsU->next;
    }
    return 0; // No 2x2 room created
}

// Function to add an edge to the graph by editing the neighbor list of the vertex
void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->neighbor = v;
    newNode->next = maze[u].neighbors;
    maze[u].neighbors = newNode;
}

// DFS function to generate the maze
void generateMazeDFS(int x, int y, int visited[]) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // List of possible directions (up, down, left, right)
    int order[4] = {0, 1, 2, 3}; // Search order of directions

    // Randomly shuffle the search order
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }

    int current = x * n + y; // Current cell index
    visited[current] = 1;

    for (int i = 0; i < 4; i++) {
        int nx = x + directions[order[i]][0];
        int ny = y + directions[order[i]][1];

        if (nx >= 0 && nx < n && ny >= 0 && ny < n) { 
            int neighbor = nx * n + ny; // Index of the neighboring cell
            if (!visited[neighbor]) { 
                addEdge(current, neighbor);
                addEdge(neighbor, current);
                generateMazeDFS(nx, ny, visited);
            } else if (!createsRoom2x2(current, neighbor) && (double)rand() / RAND_MAX < CYCLE_CHANCE) {
                // If the neighbor is visited, add an edge with some probability ensuring no 2x2 room is created
                addEdge(current, neighbor);
                addEdge(neighbor, current);
            }
        }
    }
}

// Function to print the maze
void printMaze() {
    printf("Maze (%dx%d):\n", n, n); // Print maze size

    for (int i = 0; i < n; i++) {
        // Print northern walls of each cell in the row
        for (int j = 0; j < n; j++) {
            printf("+");
            Node* current = maze[i * n + j].neighbors;
            int hasNorthWall = 1;
            while (current) {
                if (current->neighbor == (i - 1) * n + j) {
                    hasNorthWall = 0; // No northern wall if there is a neighbor above
                    break;
                }
                current = current->next;
            }
            if (j % n == entry && i == 0) hasNorthWall = 0; // No northern wall for the entry point
            printf(hasNorthWall ? "-----" : "     ");
        }
        printf("+\n");

        // Print western walls and cell values
        for (int j = 0; j < n; j++) {
            Node* current = maze[i * n + j].neighbors;
            int hasWestWall = 1;
            while (current) {
                if (current->neighbor == i * n + j - 1) {
                    hasWestWall = 0; // No western wall if there is a neighbor to the left
                    break;
                }
                current = current->next;
            }
            printf(hasWestWall ? "|" : " "); // Print western wall or space
            printf(" %2.1f ", maze[i * n + j].value);
        }
        printf("|\n"); // Close the row with a wall
    }

    // Print the last row of walls (southern walls)
    for (int j = 0; j < n; j++) {
        printf(j != exitt % n ? "+-----" : "+     ");
    }
    printf("+\n");
}

void printCell(int ind) {
    printf("[%d,%d] ", ind / n, ind % n);
}

// Recursive function to find all paths between `start` and `exitt`
void findPaths(int current, int stop, int visited[], int path[], int pathIndex, double pathWeight) {
    visited[current] = 1; // Mark the current vertex as visited
    path[pathIndex] = current; // Add the vertex to the current path
    pathIndex++; // Increment the path index
    pathWeight += maze[current].value; // Add the cell's weight to the current weight sum

    // If we have reached the destination
    if (current == stop) {
        printf("Path: ");
        for (int i = 0; i < pathIndex; i++) {
            printCell(path[i]);
            printf(i == pathIndex - 1 ? "" : "-> ");
        }
        printf("| Total weight: %.1f\n", pathWeight);

        // Check if the current path is the shortest
        if (pathWeight < minPathWeight) {
            minPathWeight = pathWeight;
            bestPathLength = pathIndex;
            for (int i = 0; i < pathIndex; i++) {
                bestPath[i] = path[i];
            }
        }
    } else {
        // Traverse neighbors and recursively call DFS
        Node* neighbor = maze[current].neighbors;
        while (neighbor) {
            if (!visited[neighbor->neighbor]) {
                findPaths(neighbor->neighbor, stop, visited, path, pathIndex, pathWeight);
            }
            neighbor = neighbor->next;
        }
    }

    // Backtrack (undo the changes for this path)
    visited[current] = 0;
    pathIndex--;
}

// Helper function to initialize backtracking
void findAllPaths(int start, int stop) {
    int* visited = (int*)calloc(n * n, sizeof(int));
    int* path = (int*)malloc(n * n * sizeof(int));

    if (!visited || !path) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    printf("All paths between [%d, %d] (entry) and [%d, %d] (exit):\n", start / n, start % n, stop / n, stop % n);
    findPaths(start, stop, visited, path, 0, 0.0);

    free(visited);
    free(path);
}

void printShortestPath() {
    printf("\nShortest path: ");
    for (int i = 0; i < bestPathLength; i++) {
        printCell(bestPath[i]);
        printf(i == bestPathLength - 1 ? "" : "-> ");
    }
    printf("| Total weight: %.1f\n", minPathWeight);
}

int main() {
    srand(time(NULL)); // Initialize random number generator

    printf("Enter maze size (n): ");
    scanf("%d", &n); // Read the maze size

    if (n > MAX_SIZE) { // Check the size
        printf("Maze size too large. Maximum size is %d.\n", MAX_SIZE);
        return 1;
    }

    if (n <= 0) { // Check invalid size
        printf("Invalid maze size.\n");
        return 1;
    }

    // Initialize the maze with random values and no neighbors
    for (int i = 0; i < n * n; i++) {
        maze[i].value = (double)(rand() % 100) / 10.0;
        maze[i].neighbors = NULL;
    }

    // Allocate memory for the visited array
    int* visited = (int*)calloc(n * n, sizeof(int));
    if (!visited) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Randomly select entry and exit points
    entry = rand() % n;
    exitt = rand() % n + (n - 1) * n;

    // Generate the maze starting from the entry point
    generateMazeDFS(entry / n, entry % n, visited);

    // Print the generated maze
    printMaze();

    // Find all possible paths between entry and exit
    findAllPaths(entry, exitt);

    // Print the shortest path
    printShortestPath();

    // Free allocated memory
    for (int i = 0; i < n * n; i++) {
        Node* current = maze[i].neighbors;
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(visited);

    return 0;
}