#include "enemy.h"

/**
 * @brief Initializes enemy instance.
 * 
 * @param enemy pointer to the enemy instance
 * @param strategy move strategy
 * @param init_loc initial location
 * @param overflow whether move of `enemy` can overflow the board or not
 */
void init_enemy(struct enemy *enemy, 
                struct move_strat *strategy, int init_loc, bool overflow) {
    init_unit((struct unit *) enemy, init_loc, overflow);
    
    enemy->strategy = strategy;
}

/**
 * @brief Moves `enemy` according to its `strategy`.
 * 
 * @param enmy pointer to the enemy instance
 */
void move(struct enemy *enemy) {
    enemy->strategy->move(enemy->strategy, enemy);
}