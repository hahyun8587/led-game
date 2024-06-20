#include "player.h"

/**
 * @brief Initializes player instance.
 * 
 * @param player pointer to the player instance
 * @param init_loc inital location
 * @param health health 
 * @param overflow whether a move of `player` can overflow the board or not
 */
void init_player(struct player *player, 
                 int init_loc, int health, bool overflow) {
    init_unit((struct unit *) player, init_loc, overflow);
    
    player->health = health; 
}

/**
 * @brief Sets `loc` of `player` one pixel right.
 * 
 * @param player pointer to the player instance
 */
void move_right(struct player *player) {
    if (player->unit.loc % BOARD_WID == BOARD_WID - 1) {
        if (player->unit.overflow) {
            player->unit.loc -= BOARD_WID - 1;
        } 
    } else {
        player->unit.loc++;
    }
}

/**
 * @brief Sets `loc` of `player` one pixel left.
 * 
 * @param player pointer to the player instance
 */
void move_left(struct player *player) {
    if (player->unit.loc % BOARD_WID == 0) {
        if (player->unit.overflow) {
            player->unit.loc += BOARD_WID - 1;
        } 
    } else {
        player->unit.loc--;
    }
}

/**
 * @brief Sets `loc` of `player` one pixel upward.
 * 
 * @param player pointer to the player instance
 */
void move_up(struct player *player) {
    if (player->unit.loc / BOARD_WID == 0) {
        if (player->unit.overflow) {
            player->unit.loc += BOARD_WID * (BOARD_HEI - 1);
        } 
    } else {
        player->unit.loc -= BOARD_WID;
    }
}

/**
 * @brief Sets `loc` of `player` one pixel downward.
 * 
 * @param player pointer to the player instance
 */
void move_down(struct player *player) {
    if (player->unit.loc / BOARD_WID == BOARD_HEI - 1) {
        if (player->unit.overflow) {
            player->unit.loc -= BOARD_WID * (BOARD_HEI - 1);
        } 
    } else {
        player->unit.loc += BOARD_WID;
    }
}

/**
 * @brief Decreases `health` of `player` by 1.
 * 
 * @param player pointer to the player instance
 */
void lose_health(struct player *player) {   
    player->health--;
}
