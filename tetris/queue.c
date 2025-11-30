#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static int queue_expand(PieceQueue *q){
    int newcap = q->capacity ? q->capacity * 2 : 4;
    PieceType *tmp = realloc(q->data, sizeof(PieceType) * newcap);
    if(!tmp) return 0;
    if(q->head > q->tail){
        for(int i = 0; i < q->head; ++i) tmp[i + q->capacity] = tmp[i];
        q->tail = q->tail + q->capacity;
    }
    q->data = tmp;
    q->capacity = newcap;
    return 1;
}

PieceQueue *queue_create(int capacity){
    PieceQueue *q = malloc(sizeof(PieceQueue));
    if(!q) return NULL;
    q->capacity = capacity > 0 ? capacity : 4;
    q->data = malloc(sizeof(PieceType) * q->capacity);
    if(!q->data){ free(q); return NULL; }
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    return q;
}

void queue_free(PieceQueue *q){
    if(!q) return;
    free(q->data);
    free(q);
}

int queue_enqueue(PieceQueue *q, PieceType p){
    if(!q) return 0;
    if(q->size == q->capacity) if(!queue_expand(q)) return 0;
    q->data[q->tail] = p;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return 1;
}

int queue_enqueue_front(PieceQueue *q, PieceType p){
    if(!q) return 0;
    if(q->size == q->capacity) if(!queue_expand(q)) return 0;
    q->head = (q->head - 1 + q->capacity) % q->capacity;
    q->data[q->head] = p;
    q->size++;
    return 1;
}

int queue_dequeue(PieceQueue *q, PieceType *out){
    if(!q || q->size == 0) return 0;
    if(out) *out = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return 1;
}

int queue_peek(const PieceQueue *q, PieceType *out){
    if(!q || q->size == 0) return 0;
    if(out) *out = q->data[q->head];
    return 1;
}

int queue_is_empty(const PieceQueue *q){
    return !q || q->size == 0;
}

void queue_print(const PieceQueue *q){
    if(!q) return;
    printf("Fila futura (size=%d): ", q->size);
    for(int i=0;i<q->size;i++){
        int idx = (q->head + i) % q->capacity;
        printf("%s ", piece_name(q->data[idx]));
    }
    printf("\n");
}
