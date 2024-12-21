#ifndef SKOROWIDZ_H
#define SKOROWIDZ_H

#include <stdlib.h>
#include "DynamicArray.h"

// Structure to store information abaout words and thier occurences
typedef struct {
    int wordcnt; // Number of words to search for
    char **words; // Array of words to search
    int *counter; // Array to store number of occurrences
    DynamicArray **occur; // Array to store element occurrences
} skorowidz_t;

void initSkorowidz(int n, char **tab, skorowidz_t *s);
void addSkorowidz(int i, int line, skorowidz_t *s);
void printSkorowidz(skorowidz_t *s);
void freeSkorowidz(skorowidz_t *s);

#endif