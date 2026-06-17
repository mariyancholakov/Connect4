#include <stdio.h>
#include "board.h"
#include "ai.h"

static void swap_sides(Board *b) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++) {
            if (b->grid[r][c] == AI)          b->grid[r][c] = PLAYER;
            else if (b->grid[r][c] == PLAYER) b->grid[r][c] = AI;
        }
}

int main(void) {
    Board b;
    board_init(&b);

    const int DEPTH = 4;
    const int MOVES = 6;

    for (int i = 0; i < MOVES; i++) {
        int piece = (i % 2 == 0) ? AI : PLAYER;
        int move;

        if (piece == AI) {
            move = ai_best_move(&b, DEPTH);
        } else {
            swap_sides(&b);
            move = ai_best_move(&b, DEPTH);
            swap_sides(&b);
        }

        board_drop(&b, move, piece);
        printf("Move %d (%c) -> column %d\n",
               i + 1, piece == AI ? 'O' : 'X', move);
    }

    printf("\nFinal board after %d self-play moves:\n", MOVES);
    board_print(&b);

    return 0;
}
