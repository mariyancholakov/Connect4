#include <stdio.h>
#include "board.h"
#include "ai.h"

int main(void) {
    Board b;
    board_init(&b);
    board_print(&b);

    board_drop(&b, 3, PLAYER);
    board_drop(&b, 3, AI);
    board_drop(&b, 2, PLAYER);
    board_print(&b);

    int move = ai_best_move(&b, 4);
    printf("AI wants to play column: %d\n", move);

    return 0;
}