#include "board.h"
#include <stdio.h>

void board_init(Board *b) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            b->grid[r][c] = EMPTY;
}

void board_print(const Board *b) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            char ch = '.';
            if (b->grid[r][c] == PLAYER1) ch = 'X';
            if (b->grid[r][c] == PLAYER2) ch = 'O';
            printf("%c ", ch);
        }
        printf("\n");
    }
    for (int c = 0; c < COLS; c++)
        printf("%d ", c);
    printf("\n");
}

int board_drop(Board *b, int col, int piece) {
    for (int r = ROWS - 1; r >= 0; r--) {
        if (b->grid[r][col] == EMPTY) {
            b->grid[r][col] = piece;
            return r;
        }
    }
    return -1;
}

int board_check_win(const Board *b, int piece) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c <= COLS - 4; c++)
            if (b->grid[r][c]   == piece &&
                b->grid[r][c+1] == piece &&
                b->grid[r][c+2] == piece &&
                b->grid[r][c+3] == piece)
                return 1;

    for (int r = 0; r <= ROWS - 4; r++)
        for (int c = 0; c < COLS; c++)
            if (b->grid[r][c]   == piece &&
                b->grid[r+1][c] == piece &&
                b->grid[r+2][c] == piece &&
                b->grid[r+3][c] == piece)
                return 1;

    for (int r = 0; r <= ROWS - 4; r++)
        for (int c = 0; c <= COLS - 4; c++)
            if (b->grid[r][c]     == piece &&
                b->grid[r+1][c+1] == piece &&
                b->grid[r+2][c+2] == piece &&
                b->grid[r+3][c+3] == piece)
                return 1;

    for (int r = 0; r <= ROWS - 4; r++)
        for (int c = 3; c < COLS; c++)
            if (b->grid[r][c]     == piece &&
                b->grid[r+1][c-1] == piece &&
                b->grid[r+2][c-2] == piece &&
                b->grid[r+3][c-3] == piece)
                return 1;

    return 0;
}

int board_is_full(const Board *b) {
    for (int c = 0; c < COLS; c++)
        if (b->grid[0][c] == EMPTY)
            return 0;
    return 1;
}

int board_undo_drop(Board *b, int col) {
    for (int r = 0; r < ROWS; r++) {
        if (b->grid[r][col] != EMPTY) {
            b->grid[r][col] = EMPTY;
            return r;
        }
    }
    return -1;
}

void board_get_valid_cols(const Board *b, int *cols, int *count) {
    *count = 0;
    for (int c = 0; c < COLS; c++)
        if (b->grid[0][c] == EMPTY)
            cols[(*count)++] = c;
}
