#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for the maximum number of states, symbols, and input length, as well as a buffer size
#define MAX_STATES 100
#define MAX_SYMBOLS 10
#define MAX_INPUT_LENGTH 10000
#define BUFOR 5

// Struct for the finite automaton
typedef struct {
    int num_states; //  Number of states
    int num_symbols; // Number of input symbols
    int **transition_table; // 2D transition table
    int start_state; // Start state
    int *accepting_states; // Array of accepting states
    int num_accepting_states; // Number of accepting states
} FiniteAutomaton;

// Function to create a new finite automaton, allocating memory for the struct and its tables
// Returns a pointer to the newly created automaton
FiniteAutomaton *create_automaton(int num_states, int num_symbols, int start) {
    FiniteAutomaton *fa = (FiniteAutomaton *)malloc(sizeof(FiniteAutomaton));
    fa->num_states = num_states;
    fa->num_symbols = num_symbols;
    fa->start_state = start;

    // Allocate memory for the 2D transition table
    fa->transition_table = (int **)malloc(num_states * sizeof(int *));
    for (int i = 0; i < num_states; i++) {
        fa->transition_table[i] = (int *)malloc(num_symbols * sizeof(int));
    }

    // Allocate memory for the array of accepting states
    fa->accepting_states = (int *)malloc(num_states * sizeof(int));
    fa->num_accepting_states = 0;

    // Return the pointer to the created automaton
    return fa;
}

// Function to set a transition in the automaton's transition table
void set_transition(FiniteAutomaton *fa, int state, int symbol, int next_state) {
    fa->transition_table[state][symbol] = next_state;
}

// Function to add an accepting state to the automaton
void add_accepting_state(FiniteAutomaton *fa, int state) {
    fa->accepting_states[fa->num_accepting_states++] = state;
}

// Function to check if a given state is an accepting state
int is_accepting_state(FiniteAutomaton *fa, int state) {
    for (int i = 0; i < fa->num_accepting_states; i++) {
        if (fa->accepting_states[i] == state) {
            return 1;
        }
    }
    return 0;
}

// Function to display a transition diagram while processing input
void print_transition_diagram(int current_state, char symbol) {
    printf("Processed symbol '%c', transitioned to state: q%d\n", symbol, current_state);
}

// Function to display the complete transition path after processing input
void print_transition_path(FiniteAutomaton *fa, int *path, int length) {
    printf("Transition path: ");
    for (int i = 0; i < length; i++) {
        // Handle the initial state separately
        if (i == 0) {
            printf("q%d -> ", fa->start_state);
        }
        // Display each state in the transition path
        printf("q%d ", path[i]);
        if (i < length - 1) {
            printf("-> ");
        }
    }
    printf("\n");
}

// Function to simulate the operation of the automaton on a given input string
void simulate_automaton(FiniteAutomaton *fa, const char *input) {
    int current_state = fa->start_state;
    int path[MAX_INPUT_LENGTH + BUFOR], path_length = 0;

    printf("Starting at state: q%d\n", current_state);

    int length = strlen(input);

    // Check if the input string is too long
    if (length >= MAX_INPUT_LENGTH) {
        printf("Error: Input string is too long. Maximum allowed length is %d.\n", MAX_INPUT_LENGTH);
        return;
    }

    for (int i = 0; i < length; i++) {
        char symbol = input[i];
        
        // Validate the input symbol
        if (symbol != '0' && symbol != '1') {
            printf("Error: Invalid symbol '%c' at position %d. Allowed symbols are '0' and '1'.\n", symbol, i);
            return;
        }
        // TODO: handle more than 2 symbols
        int symbol_index = symbol - '0'; // Convert '0' or '1' to index 0 or 1
        current_state = fa->transition_table[current_state][symbol_index];
        path[path_length++] = current_state;

        // Display the transition diagram
        print_transition_diagram(current_state, symbol);
    }

    // Display the transition path
    print_transition_path(fa, path, path_length);

    // Display whether the input is accepted or rejected
    if (is_accepting_state(fa, current_state)) {
        printf("The input string is accepted.\n");
    } else {
        printf("The input string is rejected.\n");
    }
}

int main() {
    // Create a finite automaton with the given parameters
    FiniteAutomaton *fa = create_automaton(4, 2, 0);

    // Define the transitions for the example automaton
    set_transition(fa, 0, 0, 1);
    set_transition(fa, 0, 1, 2);
    set_transition(fa, 1, 0, 3);
    set_transition(fa, 1, 1, 0);
    set_transition(fa, 2, 0, 0);
    set_transition(fa, 2, 1, 3);
    set_transition(fa, 3, 0, 1);
    set_transition(fa, 3, 1, 2);

    // Add an accepting state
    add_accepting_state(fa, 3);

    // Read input strings from the user
    char input[MAX_INPUT_LENGTH + BUFOR];
    while (1) {
        printf("Enter a binary string (0s and 1s), or 'q' to quit: ");
        scanf("%10000s", input);

        // Exit if the user inputs 'q'
        if (strcmp(input, "q") == 0) {
            break;
        }

        // Simulate the automaton on the given input
        simulate_automaton(fa, input);
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < fa->num_states; i++) {
        free(fa->transition_table[i]);
    }
    free(fa->transition_table);
    free(fa->accepting_states);
    free(fa);

    return 0;
}
