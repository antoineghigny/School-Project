#ifndef DUEL_H
#define DUEL_H

#include "Pawn.h"
#include "Position.h"

enum Result{WIN, LOSE, DRAW, NOTHING};

typedef struct duel {
    Result result;
    Pawn attaker;
    Position attakerPos;
    Pawn defender;
    Position defenderPos;
} duel;

#endif // DUEL_H
