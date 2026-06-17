#include "ai.h"
#include "board.h"
#include <limits.h>

static const int COL_ORDER[COLS] = {3, 2, 4, 1, 5, 0, 6};

static int score_window(int ai_count, int opp_count)
{
    if (ai_count > 0 && opp_count > 0)
        return 0;
    if (ai_count == 4)  return  100000;
    if (ai_count == 3)  return  100;
    if (ai_count == 2)  return  10;
    if (opp_count == 4) return -100000;
    if (opp_count == 3) return -100;
    if (opp_count == 2) return -10;
    return 0;
}

static int score_board(const Board *b)
{
    int score = 0;

    for (int r = 0; r < ROWS; r++)
        if (b->grid[r][3] == AI)
            score += 3;

    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c <= COLS - 4; c++)
        {
            int ai_c = 0, opp_c = 0;
            for (int k = 0; k < 4; k++)
            {
                int v = b->grid[r][c + k];
                if (v == AI)          ai_c++;
                else if (v == PLAYER) opp_c++;
            }
            score += score_window(ai_c, opp_c);
        }

    for (int c = 0; c < COLS; c++)
        for (int r = 0; r <= ROWS - 4; r++)
        {
            int ai_c = 0, opp_c = 0;
            for (int k = 0; k < 4; k++)
            {
                int v = b->grid[r + k][c];
                if (v == AI)          ai_c++;
                else if (v == PLAYER) opp_c++;
            }
            score += score_window(ai_c, opp_c);
        }

    for (int r = 0; r <= ROWS - 4; r++)
        for (int c = 0; c <= COLS - 4; c++)
        {
            int ai_c = 0, opp_c = 0;
            for (int k = 0; k < 4; k++)
            {
                int v = b->grid[r + k][c + k];
                if (v == AI)          ai_c++;
                else if (v == PLAYER) opp_c++;
            }
            score += score_window(ai_c, opp_c);
        }

    for (int r = 3; r < ROWS; r++)
        for (int c = 0; c <= COLS - 4; c++)
        {
            int ai_c = 0, opp_c = 0;
            for (int k = 0; k < 4; k++)
            {
                int v = b->grid[r - k][c + k];
                if (v == AI)          ai_c++;
                else if (v == PLAYER) opp_c++;
            }
            score += score_window(ai_c, opp_c);
        }

    return score;
}

static int minimax(Board *b, int depth, int is_maximizing)
{
    if (board_check_win(b, AI))
        return 100000;
    if (board_check_win(b, PLAYER))
        return -100000;
    if (board_is_full(b))
        return 0;
    if (depth == 0)
        return score_board(b);

    if (is_maximizing)
    {
        int best = INT_MIN;
        for (int i = 0; i < COLS; i++)
        {
            int col = COL_ORDER[i];
            if (b->grid[0][col] != EMPTY)
                continue;
            board_drop(b, col, AI);
            int score;
            if (board_check_win(b, AI))
                score = 100000;
            else
                score = minimax(b, depth - 1, 0);
            board_undo_drop(b, col);
            if (score > best)
                best = score;
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        for (int i = 0; i < COLS; i++)
        {
            int col = COL_ORDER[i];
            if (b->grid[0][col] != EMPTY)
                continue;
            board_drop(b, col, PLAYER);
            int score;
            if (board_check_win(b, PLAYER))
                score = -100000;
            else
                score = minimax(b, depth - 1, 1);
            board_undo_drop(b, col);
            if (score < best)
                best = score;
        }
        return best;
    }
}

int ai_best_move(Board *b, int depth)
{
    int best_score = INT_MIN;
    int best_col = -1;

    for (int i = 0; i < COLS; i++)
    {
        int col = COL_ORDER[i];
        if (b->grid[0][col] != EMPTY)
            continue;

        board_drop(b, col, AI);
        int score;
        if (board_check_win(b, AI))
            score = 100000;
        else
            score = minimax(b, depth - 1, 0);
        board_undo_drop(b, col);

        if (best_col == -1 || score > best_score)
        {
            best_score = score;
            best_col = col;
        }
    }

    return best_col;
}
