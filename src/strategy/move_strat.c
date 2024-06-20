#include "strategy/move_strat.h"

/**
 * @brief Initializes move_strat instance.
 * 
 * @param strategy pointer to the move_strat instance
 * @param move move function
 */
void init_move_strat(struct move_strat *strategy, move_t move) {
    strategy->move = move;
}
