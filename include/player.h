#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "board.h"
#include "unit.h"

#define INIT_PLAYER_LOC     64
#define MAX_HEALH           7

/**
 * @brief Struct that represents player of the game.
 * 
 */
struct player {
    struct unit unit;
    int health;
};

void init_player(struct player *player, 
                 int init_loc, int health, bool overflow);
void move_right(struct player *player);
void move_left(struct player *player);
void move_up(struct player *player);
void move_down(struct player *player);
void lose_health(struct player *player);

#endif
