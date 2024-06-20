#ifndef STATE_GAMESTATE_H
#define STATE_GAMESTATE_H

#include "service_state.h"
#include "application.h"
#include "dev.h"
#include "displayer.h"

#define MAX_DIFF            20
#define MIN_DIFF            1
#define SAFETY_BOARDER      5

struct game_state {
    struct service_state service_state;
    int diff;
    int score;
};

void init_game_state(struct game_state *state, int diff);
struct game_state *game_state_get_inst(int diff);
void game_state_begin(struct service_state *state, struct app *app);

#endif
