#include <stdio.h>
#include "board.h"
#include "ai.h"

int main(void) {
    Board b;
    board_init(&b);

    board_drop(&b, 1, AI);
    board_drop(&b, 2, AI);
    board_drop(&b, 3, AI);
    board_drop(&b, 5, PLAYER);
    board_drop(&b, 6, PLAYER);

    board_print(&b);

    int move = ai_best_move(&b, 4);
    printf("AI plays column: %d (should be 0 or 4)\n", move);

    return 0;
}