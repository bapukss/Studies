#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

// Struct to represent a dynamic array
typedef struct {
    int *data;       //Pointer to the array's data
    size_t size;     // Current number of elemements
    size_t capacity; // max number of elements
} DynamicArray;

void initArray(DynamicArray *a, size_t initcap);
void addElem(DynamicArray *a, int val);
void freeArray(DynamicArray *a);

#endif