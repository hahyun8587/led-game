#include "command/i2c_write_cmd.h"

static struct i2c_write_cmd cmd;

/**
 * @brief Initializes i2c_write_cmd instance.
 * 
 * @param cmd pointer to the i2c_write_cmd
 * @param target i2c target device
 * @param buf buffer of bytes to be written  
 * @param num_bytes the number of bytes 
 */
void init_i2c_write_cmd(struct i2c_write_cmd *cmd, 
        struct i2c_dt_spec *target, uint8_t *buf, int num_bytes) {
    init_device_cmd((struct device_cmd *) cmd, NULL, i2c_write_cmd_execute);

    cmd->target = target;

    for (int i = 0; i < num_bytes; i++) {
        cmd->buf[i] = buf[i];
    }

    cmd->num_bytes = num_bytes;
}

/**
 * @brief Gets i2c_write_cmd instance.
 * 
 * @param state service_state instance
 * @param target i2c_dt_spec instance
 * @param buf buffer of bytes to be written  
 * @param num_bytes the number of bytes
 * @return pointer to the i2c_write_cmd instance 
 */
struct i2c_write_cmd *i2c_write_cmd_get_inst(
        struct i2c_dt_spec *target, uint8_t *buf, int num_bytes) {
    init_i2c_write_cmd(&cmd, target, buf, num_bytes);

    return &cmd;
}

/**
 * @brief Writes `data` to i2c target.
 * 
 * @param cmd pointer to the i2c_write_cmd
 */
void i2c_write_cmd_execute(struct device_cmd *cmd) {
    struct i2c_write_cmd *iwc = (struct i2c_write_cmd *) cmd;

    i2c_write_dt(iwc->target, iwc->buf, iwc->num_bytes);
}
