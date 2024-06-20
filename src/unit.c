#include "unit.h"

/**
 * @brief Initializes unit instance.
 * 
 * @param unit pointer to the unit instance
 * @param init_loc initial location
 * @param overflow whether a move of `unit` can overflow the board or not
 */
void init_unit(struct unit *unit, int init_loc, bool overflow) {
    unit->init_loc = init_loc;
    unit->loc = unit->init_loc;
    unit->overflow = overflow;
}

void respawn(struct unit *unit) {
    unit->loc = unit->init_loc;
}

int get_loc(struct unit *unit) {
    return unit->loc;
}

void set_loc(struct unit *unit, int loc) {
    unit->loc = loc;
}
