#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

GameState *game_create(void){
    GameState *g = malloc(sizeof(GameState));
    if(!g) return NULL;
    g->future = queue_create(8);
    g->reserve = stack_create(8);
    srand((unsigned)time(NULL));
    return g;
}

void game_free(GameState *g){
    if(!g) return;
    queue_free(g->future);
    stack_free(g->reserve);
    free(g);
}

void game_fill_random(GameState *g, int n){
    if(!g) return;
    for(int i=0;i<n;i++){
        PieceType p = (PieceType)(rand() % PIECE_COUNT);
        queue_enqueue(g->future, p);
    }
}

int game_next_piece(GameState *g, PieceType *out){
    if(!g) return 0;
    return queue_dequeue(g->future, out);
}

int game_reserve_top(GameState *g){
    if(!g) return 0;
    PieceType p;
    if(!queue_dequeue(g->future, &p)) return 0;
    if(!stack_push(g->reserve, p)) {
        queue_enqueue_front(g->future, p);
        return 0;
    }
    return 1;
}

int game_retrieve_reserve(GameState *g){
    if(!g) return 0;
    PieceType p;
    if(!stack_pop(g->reserve, &p)) return 0;
    if(!queue_enqueue_front(g->future, p)){
        stack_push(g->reserve, p);
        return 0;
    }
    return 1;
}

void game_print(const GameState *g){
    if(!g) return;
    queue_print(g->future);
    stack_print(g->reserve);
}
