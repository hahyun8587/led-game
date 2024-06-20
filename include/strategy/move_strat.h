#ifndef STRATEGY_MOVESTRAT_H
#define STRATEGY_MOVESTRAT_H

#include "enemy.h"

#define NUM_STRATS  2

//Supports strategy pattern for enemy instance.

struct move_strat {
    void (*move)(struct move_strat *, struct enemy *);
};

typedef void (*move_t)(struct move_strat *, struct enemy *);

void init_move_strat(struct move_strat *strategy, move_t move);

#endif
