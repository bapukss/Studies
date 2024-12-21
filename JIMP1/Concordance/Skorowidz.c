#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Skorowidz.h"

#define InitSize 8 // Init cap of dynamic arrays

void initSkorowidz(int n, char **tab, skorowidz_t *s) {
    s->wordcnt = n - 2;
    s->words = malloc(s->wordcnt * sizeof(*s->words));
    s->counter = malloc(s->wordcnt * sizeof(*s->counter));
    s->occur = malloc(s->wordcnt * sizeof(s->occur));
    for(int i=2;i<n;i++){
        s->words[i-2] = tab[i];
        s->counter[i-2] = 0;
        s->occur[i-2] = malloc(sizeof(DynamicArray));
        initArray(s->occur[i-2], InitSize);
    }
}

void addSkorowidz(int i, int line, skorowidz_t *s){
    s->counter[i]++;
    addElem(s->occur[i], line);
}

void printSkorowidz(skorowidz_t *s){
    for(int i=0;i<s->wordcnt;i++){
        if(s->counter[i] > 0){
            printf("Słowo \"%s\" wystąpiło w liniach:", s->words[i]);
            for(int j=0;j<(int)s->occur[i]->size;j++){
                printf(" %d", s->occur[i]->data[j]);
            }
            printf("\n");
        } else {
            printf("Nie napotkano słowa \"%s\"\n", s->words[i]);
        }
    }
}

void freeSkorowidz(skorowidz_t *s) {
    free(s->words);
    free(s->counter);
    for (int i = 0; i < s->wordcnt; i++) {
        freeArray(s->occur[i]);
        free(s->occur[i]);
    }
    free(s->occur);
}
