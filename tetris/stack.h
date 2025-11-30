#ifndef STACK_H
#define STACK_H

#include "piece.h"

typedef struct {
    PieceType *data;
    int capacity;
    int size;
} PieceStack;

PieceStack *stack_create(int capacity);
void stack_free(PieceStack *s);
int stack_push(PieceStack *s, PieceType p);
int stack_pop(PieceStack *s, PieceType *out);
int stack_peek(const PieceStack *s, PieceType *out);
int stack_is_empty(const PieceStack *s);
void stack_print(const PieceStack *s);

#endif
