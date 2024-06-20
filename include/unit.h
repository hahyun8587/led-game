#ifndef UNIT_H
#define UNIT_H

#include <stdbool.h>

/**
 * @brief Struct that represents unit of the game. 
 * 
 * It is base class of `struct player` and `struct enemy`.
 * 
 */
struct unit {
    int init_loc;
    int loc;
    bool overflow;
};

void init_unit(struct unit *unit, int init_loc, bool overflow);
void respawn(struct unit *unit);
int get_loc(struct unit *unit);
void set_loc(struct unit *unit, int loc);

#endif
