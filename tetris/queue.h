#ifndef QUEUE_H
#define QUEUE_H

#include "piece.h"

typedef struct {
    PieceType *data;
    int capacity;
    int head;
    int tail;
    int size;
} PieceQueue;

PieceQueue *queue_create(int capacity);
void queue_free(PieceQueue *q);
int queue_enqueue(PieceQueue *q, PieceType p);
int queue_enqueue_front(PieceQueue *q, PieceType p);
int queue_dequeue(PieceQueue *q, PieceType *out);
int queue_peek(const PieceQueue *q, PieceType *out);
int queue_is_empty(const PieceQueue *q);
void queue_print(const PieceQueue *q);

#endif
