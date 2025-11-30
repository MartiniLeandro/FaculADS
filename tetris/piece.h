#ifndef PIECE_H
#define PIECE_H

typedef enum {
    I_PIECE,
    O_PIECE,
    T_PIECE,
    S_PIECE,
    Z_PIECE,
    J_PIECE,
    L_PIECE,
    PIECE_COUNT
} PieceType;

const char *piece_name(PieceType p);

#endif
