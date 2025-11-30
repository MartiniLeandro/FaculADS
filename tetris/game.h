#ifndef GAME_H
#define GAME_H

#include "queue.h"
#include "stack.h"

typedef struct {
    PieceQueue *future;
    PieceStack *reserve;
} GameState;

GameState *game_create(void);
void game_free(GameState *g);
void game_fill_random(GameState *g, int n);
int game_next_piece(GameState *g, PieceType *out);
int game_reserve_top(GameState *g);
int game_retrieve_reserve(GameState *g);
void game_print(const GameState *g);

#endif
