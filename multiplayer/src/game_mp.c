#include "game_mp.h"
#include "board.h"
#include <stdio.h>

static int prompt_move(const Board *b, int player)
{
    int col;
    while (1)
    {
        printf("Player %d (%c), your move (0-6): ", player, player == 1 ? 'X' : 'O');
        int r = scanf("%d", &col);
        if (r == EOF)
            return -1;
        if (r != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input.\n");
            continue;
        }
        if (col < 0 || col > 6)
        {
            printf("Out of range. Choose a column 0-6.\n");
            continue;
        }
        if (b->grid[0][col] != EMPTY)
        {
            printf("Column %d is full. Pick another.\n", col);
            continue;
        }
        return col;
    }
}

void game_run_multiplayer(void)
{
    Board b;
    board_init(&b);

    int current = 1;
    int piece;

    while (1)
    {
        board_print(&b);

        piece = (current == 1) ? PLAYER1 : PLAYER2;

        int col = prompt_move(&b, current);
        if (col < 0)
        {
            printf("Input closed. Exiting.\n");
            return;
        }
        board_drop(&b, col, piece);

        if (board_check_win(&b, piece))
        {
            board_print(&b);
            printf("Player %d wins!\n", current);
            return;
        }
        if (board_is_full(&b))
        {
            board_print(&b);
            printf("Draw!\n");
            return;
        }

        current = (current == 1) ? 2 : 1;
    }
}
