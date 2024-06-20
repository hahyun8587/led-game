#include <zephyr/random/rand32.h>
#include "board.h"
#include "strategy/rand_strat.h"

/**
 * @brief Initializes rand_strat instance.
 * 
 * @param strategy pointer to the rand_strat instance
 */
void init_rand_strat(struct rand_strat *strategy) {
    init_move_strat((struct move_strat *) strategy, rand_strat_move);
}

/**
 * @brief Moves `enemy` randomly by one pixel.
 * 
 * @param strategy pointer to the rand_strat instance
 * @param enemy enemy instance to be moved
 */
void rand_strat_move(struct move_strat *strategy, struct enemy *enemy) {
    int move_vals[] = { 1, -1, -BOARD_WID, BOARD_WID };
    int loc = get_loc(&enemy->unit);
    enum move_dir dir = sys_rand32_get() % NUM_DIR;
    
    if (enemy->unit.overflow) {
        if (loc % BOARD_WID == BOARD_WID - 1 && dir == DIR_RIGHT) {
            set_loc(&enemy->unit, loc - (BOARD_WID - 1));
        } else if (loc % BOARD_WID == 0 && dir == DIR_LEFT) {
            set_loc(&enemy->unit, loc + (BOARD_WID - 1));
        } else if (loc / BOARD_WID == 0 && dir == DIR_UP) {
            set_loc(&enemy->unit, loc + (BOARD_HEI - 1) * BOARD_WID);
        } else if (loc / BOARD_WID == BOARD_HEI - 1 && dir == DIR_DOWN) {
            set_loc(&enemy->unit, loc - (BOARD_HEI - 1) * BOARD_WID);
        } else {
            set_loc(&enemy->unit, loc + move_vals[dir]);
        }
    } else {
        if ((loc % BOARD_WID == BOARD_WID - 1 && dir == DIR_RIGHT) 
                || (loc % BOARD_WID == 0 && dir == DIR_LEFT) 
                || (loc / BOARD_WID == 0 && dir == DIR_UP)
                || (loc / BOARD_WID == BOARD_HEI - 1 && dir == DIR_DOWN)) {
            set_loc(&enemy->unit, loc - move_vals[dir]);    
        } else {
            set_loc(&enemy->unit, loc + move_vals[dir]);
        }
    } 
}
