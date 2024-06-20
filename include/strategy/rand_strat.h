#ifndef STRATEGY_RANDSTRAT_H
#define STRATEGY_RANDSTRAT_H

#include "move_strat.h"

struct rand_strat {
    struct move_strat move_strat;
};

void init_rand_strat(struct rand_strat *strategy);
void rand_strat_move(struct move_strat *strategy, struct enemy *enemy);

#endif
