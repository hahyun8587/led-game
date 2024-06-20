#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include "dev.h"
#include "enemy.h"
#include "player.h"

struct displayer {
    struct dev *led_matrix;
    struct dev *battery_led;
};

void init_displayer(struct displayer *displayer, 
                    struct dev *led_matrix, struct dev *battery_led);
void display_game(struct displayer *displayer, struct player *player, 
                  struct enemy *enemies, int num_enemies);
void display_number(struct displayer *displayer, int num);

#endif
