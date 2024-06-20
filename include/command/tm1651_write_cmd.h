#ifndef COMMAND_TM1651WRITECMD_H
#define COMMAND_TM1651WRITECMD_H

#include <zephyr/drivers/gpio.h>
#include "device_cmd.h"

#define TM1651_DATA_CMD         0x40
#define TM1651_ADDR_CMD         0xC0
#define TM1651_DISP_CMD         0x8F

#define TM1651_FRAME_ON_DATA    0x40, 0x40, 0x40

struct tm1651_write_cmd {
    struct device_cmd device_cmd;
    struct gpio_dt_spec *clk;
    struct gpio_dt_spec *dio;
    uint8_t val;
};

void init_tm1651_write_cmd(struct tm1651_write_cmd *cmd, 
        struct gpio_dt_spec *clk, struct gpio_dt_spec *dio, uint8_t val);
struct tm1651_write_cmd *tm1651_write_cmd_get_inst( 
        struct gpio_dt_spec *clk, struct gpio_dt_spec *dio, uint8_t val);
void tm1651_write_cmd_execute(struct device_cmd *cmd);

#endif