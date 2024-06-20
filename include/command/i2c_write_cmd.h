#ifndef COMMAND_I2CWRITECMD_H
#define COMMAND_I2CWRITECMD_H

#include <zephyr/drivers/i2c.h>
#include "device_cmd.h"
#include "state/service_state.h"

#define BUF_SIZE        17 

struct i2c_write_cmd {
    struct device_cmd device_cmd;
    struct i2c_dt_spec *target;
    uint8_t buf[BUF_SIZE];
    int num_bytes;
};

void init_i2c_write_cmd(struct i2c_write_cmd *cmd, 
        struct i2c_dt_spec *target, uint8_t *buf, int num_bytes);
struct i2c_write_cmd *i2c_write_cmd_get_inst(
        struct i2c_dt_spec *target, uint8_t *buf, int num_bytes);
void i2c_write_cmd_execute(struct device_cmd *cmd); 

#endif