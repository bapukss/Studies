#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

// Initializes a dynamic array with given capacity
void initArray(DynamicArray *a, size_t initcap) {
    a->data = (int*)malloc(initcap * sizeof(int));
    if(!a->data){
        fprintf(stderr, "Błąd alokacji pamięci!\n");
        exit(EXIT_FAILURE);
    } 
    a->size = 0;
    a->capacity = initcap;
}

// Adds an element to the dynamic array
void addElem(DynamicArray *a, int val) {
    if(a->size == a->capacity){
        size_t newcap = a->capacity * 2;
        int *newArray = (int*)realloc(a->data, newcap * sizeof(int));
        if(!newArray){
            fprintf(stderr, "Błąd realokacji pamięci!\n");
            exit(EXIT_FAILURE);
        }
        a->data = newArray;
        a->capacity = newcap;
    }
    a->data[a->size++] = val;
}

// Frees the memory
void freeArray(DynamicArray *a){
    free(a->data);
    a->data = NULL; a->size = 0; a->capacity = 0;
}