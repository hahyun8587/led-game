#ifndef STATE_GAME_SET_STATE
#define STATE_GAME_SET_STATE

#include "application.h"
#include "service_state.h"

struct game_set_state {
    struct service_state service_state;
};

void init_game_set_state(struct game_set_state *state);
struct game_set_state *game_set_state_get_inst();
void game_set_state_begin(struct service_state *state, struct app *app);

#endif
