#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Skorowidz.h"

#define BUFS 8192 // Buffer size for input 

// Compares two strings to check if their are the same
int is_full_word(const char *word, const char *target) {
    return strcmp(word, target) == 0;
}

int main(int argc, char *argv[]) {
    char buf[BUFS];
    if(argc <= 1){
        fprintf(stderr, "%s: Błąd: proszę podać plik wejściowy\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *in = fopen(argv[1], "r");
    skorowidz_t skorowidz;
    initSkorowidz(argc, argv, &skorowidz);
    if(!skorowidz.wordcnt){
        fprintf(stderr, "%s: Błąd: proszę podać słowa do wyszukiwania\n", argv[0]);
        return EXIT_FAILURE;
    }
    if(in == NULL){
        fprintf(stderr, "%s: Błąd: nie mogę czytać pliku %s\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }
    int currline = 0;
    while (fgets(buf, BUFS, in) != NULL) {
        currline++;
        // Tokenize input into word using delimiters
        char *token = strtok(buf, " \t\n\r.,!?");
        while (token != NULL) {
            for (int i = 0; i < skorowidz.wordcnt; i++) {
                if (is_full_word(token, skorowidz.words[i])) {
                    addSkorowidz(i, currline, &skorowidz);
                }
            }
            token = strtok(NULL, " \t\n\r.,!?");
        }
    }
    printSkorowidz(&skorowidz);
    freeSkorowidz(&skorowidz);
    return EXIT_SUCCESS;
}