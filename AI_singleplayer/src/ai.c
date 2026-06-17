#include "ai.h"
#include "board.h"
#include <limits.h>

static int minimax(Board *b, int depth, int is_maximizing)
{
    if (board_check_win(b, AI))
        return 100000;
    if (board_check_win(b, PLAYER))
        return -100000;
    if (board_is_full(b))
        return 0;
    if (depth == 0)
        return 0;

    int cols[COLS], count;
    board_get_valid_cols(b, cols, &count);

    if (is_maximizing)
    {
        int best = INT_MIN;
        for (int i = 0; i < count; i++)
        {
            board_drop(b, cols[i], AI);
            int score;
            if (board_check_win(b, AI))
                score = 100000;
            else
                score = minimax(b, depth - 1, 0);
            board_undo_drop(b, cols[i]);
            if (score > best)
                best = score;
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        for (int i = 0; i < count; i++)
        {
            board_drop(b, cols[i], PLAYER);
            int score;
            if (board_check_win(b, PLAYER))
                score = -100000;
            else
                score = minimax(b, depth - 1, 1);
            board_undo_drop(b, cols[i]);
            if (score < best)
                best = score;
        }
        return best;
    }
}

int ai_best_move(Board *b, int depth)
{
    int cols[COLS], count;
    board_get_valid_cols(b, cols, &count);

    int best_score = INT_MIN;
    int best_col = cols[0];

    for (int i = 0; i < count; i++)
    {
        board_drop(b, cols[i], AI);
        int score;
        if (board_check_win(b, AI))
            score = 100000;
        else
            score = minimax(b, depth - 1, 0);
        board_undo_drop(b, cols[i]);

        if (score > best_score)
        {
            best_score = score;
            best_col = cols[i];
        }
    }

    return best_col;
}