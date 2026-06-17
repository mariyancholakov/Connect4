#ifndef AI_H
#define AI_H

#include "board.h"

int ai_best_move(Board *b, int depth);
int ai_best_move_scored(Board *b, int depth, int *out_score);

#endif