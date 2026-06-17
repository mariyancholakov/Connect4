#include "ai.h"
#include "board.h"

int ai_best_move(Board *b, int depth) {
    int cols[COLS], count;
    board_get_valid_cols(b, cols, &count);

    return cols[0];
}