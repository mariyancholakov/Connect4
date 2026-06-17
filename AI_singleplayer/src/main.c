#include "game_sp.h"

int main(void)
{
    int difficulty = ui_select_difficulty();
    game_run_singleplayer(difficulty);
    return 0;
}
