#ifndef ENEMY_H
#define ENEMY_H

#include "strategy/move_strat.h"
#include "unit.h"

/**
 * @brief Struct that represents enemy of the game.
 * 
 */
struct enemy {
    struct unit unit;
    struct move_strat *strategy;
};

void init_enemy(struct enemy *enemy, 
                struct move_strat *strategy, int init_loc, bool overflow);
void move(struct enemy *enemy);

#endif
