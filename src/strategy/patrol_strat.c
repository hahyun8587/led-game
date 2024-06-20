#include "strategy/patrol_strat.h"
#include "board.h"

/**
 * @brief Initializes patrol_strat instance.
 * 
 * @param strategy pointer to the patrol_strat instance
 */
void init_patrol_strat(struct patrol_strat *strategy) {
    init_move_strat((struct move_strat *) strategy, patrol_strat_move);

    strategy->move_val = BOARD_WID;
}

/**
 * @brief Patrols `enemy` by one pixel. 
 * 
 * @param strategy pointer to the patrol_strat instance
 * @param enemy enemy instance to be moved
 */
void patrol_strat_move(struct move_strat *strategy, struct enemy *enemy) {
    struct patrol_strat *patrol_strat = (struct patrol_strat *) strategy;
    int loc = get_loc(&enemy->unit);
    
    if (loc / BOARD_WID == 0) {
        patrol_strat->move_val = BOARD_WID;
    } else if (loc / BOARD_WID == BOARD_HEI - 1) {
        patrol_strat->move_val = -BOARD_WID;
    }
    
    set_loc(&enemy->unit, loc + patrol_strat->move_val);
}
