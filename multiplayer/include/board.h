#ifndef BOARD_H
#define BOARD_H

#define ROWS 6
#define COLS 7

#define EMPTY    0
#define PLAYER1  1
#define PLAYER2  2

typedef struct {
    int grid[ROWS][COLS];
} Board;

void board_init(Board *b);
void board_print(const Board *b);
int  board_drop(Board *b, int col, int piece);
int  board_check_win(const Board *b, int piece);
int  board_is_full(const Board *b);

#endif
