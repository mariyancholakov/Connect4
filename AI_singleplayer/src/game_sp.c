#include "game_sp.h"
#include "board.h"
#include "ai.h"
#include <stdio.h>
#include <time.h>

int ui_select_difficulty(void)
{
    int choice;
    while (1)
    {
        printf("Select difficulty:\n");
        printf("  1) Easy\n");
        printf("  2) Medium\n");
        printf("  3) Hard\n");
        printf("> ");

        int r = scanf("%d", &choice);
        if (r == EOF)
            return 2;
        if (r != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("Invalid input. Please enter 1, 2, or 3.\n");
            continue;
        }

        if (choice >= 1 && choice <= 3)
            return choice;

        printf("Invalid choice. Please enter 1, 2, or 3.\n");
    }
}

static int prompt_human_move(const Board *b)
{
    int col;
    while (1)
    {
        printf("Your move(X): ");
        int r = scanf("%d", &col);
        if (r == EOF)
            return -1;
        if (r != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
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

void game_run_singleplayer(int difficulty)
{
    int depth;
    switch (difficulty)
    {
        case 1: depth = 3; break;
        case 2: depth = 5; break;
        case 3: depth = 7; break;
        default: depth = 5; break;
    }

    Board b;
    board_init(&b);

    while (1)
    {
        board_print(&b);

        int human_col = prompt_human_move(&b);
        if (human_col < 0)
        {
            printf("Input closed. Exiting.\n");
            return;
        }
        board_drop(&b, human_col, PLAYER);

        if (board_check_win(&b, PLAYER))
        {
            board_print(&b);
            printf("You win!\n");
            return;
        }
        if (board_is_full(&b))
        {
            board_print(&b);
            printf("Draw!\n");
            return;
        }

        int ai_score = 0;
        clock_t t0 = clock();
        int ai_col = ai_best_move_scored(&b, depth, &ai_score);
        clock_t t1 = clock();
        long ms = (long)((t1 - t0) * 1000 / CLOCKS_PER_SEC);
        board_drop(&b, ai_col, AI);
        printf("AI thinking time: %ld ms\n", ms);
        printf("AI played column %d (score: %d)\n", ai_col, ai_score);

        if (board_check_win(&b, AI))
        {
            board_print(&b);
            printf("AI wins!\n");
            return;
        }
        if (board_is_full(&b))
        {
            board_print(&b);
            printf("Draw!\n");
            return;
        }
    }
}
