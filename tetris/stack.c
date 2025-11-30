#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

PieceStack *stack_create(int capacity){
    PieceStack *s = malloc(sizeof(PieceStack));
    if(!s) return NULL;
    s->capacity = capacity > 0 ? capacity : 4;
    s->data = malloc(sizeof(PieceType) * s->capacity);
    if(!s->data){ free(s); return NULL; }
    s->size = 0;
    return s;
}

void stack_free(PieceStack *s){
    if(!s) return;
    free(s->data);
    free(s);
}

int stack_push(PieceStack *s, PieceType p){
    if(!s) return 0;
    if(s->size == s->capacity){
        int nc = s->capacity * 2;
        PieceType *tmp = realloc(s->data, sizeof(PieceType) * nc);
        if(!tmp) return 0;
        s->data = tmp;
        s->capacity = nc;
    }
    s->data[s->size++] = p;
    return 1;
}

int stack_pop(PieceStack *s, PieceType *out){
    if(!s || s->size == 0) return 0;
    s->size--;
    if(out) *out = s->data[s->size];
    return 1;
}

int stack_peek(const PieceStack *s, PieceType *out){
    if(!s || s->size == 0) return 0;
    if(out) *out = s->data[s->size-1];
    return 1;
}

int stack_is_empty(const PieceStack *s){
    return !s || s->size == 0;
}

void stack_print(const PieceStack *s){
    if(!s) return;
    printf("Pilha reservada (size=%d): ", s->size);
    for(int i=s->size-1;i>=0;i--) printf("%s ", piece_name(s->data[i]));
    printf("\n");
}
