#include "piece.h"

const char *piece_name(PieceType p){
    static const char *names[] = {"I","O","T","S","Z","J","L"};
    if(p < 0 || p >= PIECE_COUNT) return "?";
    return names[p];
}
