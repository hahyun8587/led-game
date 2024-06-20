#ifndef STRATEGY_PATROL_STRAT_H
#define STRATEGY_PATROL_STRAT_H

#include "move_strat.h"

struct patrol_strat {
    struct move_strat move_strat;
    int move_val;
};

void init_patrol_strat(struct patrol_strat *strategy);
void patrol_strat_move(struct move_strat *strategy, struct enemy *enemy);

#endif
