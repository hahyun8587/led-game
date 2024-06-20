#ifndef COMMAND_GPIOREADCMD_H
#define COMMAND_GPIOREADCMD_H

#include <zephyr/drivers/gpio.h>
#include "device_cmd.h"

struct gpio_read_cmd {
    struct device_cmd device_cmd;
    struct gpio_dt_spec *pin;
};

void init_gpio_read_cmd(struct gpio_read_cmd *cmd, 
        struct service_state *state, struct gpio_dt_spec *pin);
struct gpio_read_cmd *gpio_read_cmd_get_inst(
        struct service_state *state, struct gpio_dt_spec *pin);
void gpio_read_cmd_execute(struct device_cmd *cmd);

#endif
