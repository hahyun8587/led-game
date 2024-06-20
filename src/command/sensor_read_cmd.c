#include "command/sensor_read_cmd.h"

static struct sensor_read_cmd cmd;

/**
 * @brief Initializes sensor_read_cmd instance.
 * 
 * @param cmd pointer to the sensor_read_cmd instance 
 * @param state service_state instance
 * @param sensor device instance that has sensor api
 * @param sensor_chan sensor channel
 */
void init_sensor_read_cmd(struct sensor_read_cmd *cmd, 
                          struct service_state *state, 
                          struct device *sensor, enum sensor_channel chan) {
    init_device_cmd((struct device_cmd *) cmd, state, sensor_read_cmd_execute);

    cmd->sensor = sensor;
    cmd->chan = chan;
}

/**
 * @brief Gets sensor_read_cmd instance.
 *  
 * @param state state instance
 * @param sensor device instance that has sensor api
 * @param chan sensor channel
 * @return pointer to the sensor_read_cmd instance
 */
struct sensor_read_cmd *sensor_read_cmd_get_inst(struct service_state *state, 
        struct device *sensor, enum sensor_channel chan) {
    init_sensor_read_cmd(&cmd, state, sensor, chan);

    return &cmd;
}

/**
 * @brief Reads sensor value.
 * 
 * @param cmd pointer to the sensor_read_cmd instance
 */
void sensor_read_cmd_execute(struct device_cmd *cmd) {
    struct sensor_value val;
    struct sensor_read_cmd *sensor_read_cmd = (struct sensor_read_cmd *) cmd;

    sensor_sample_fetch(sensor_read_cmd->sensor);
    sensor_channel_get(sensor_read_cmd->sensor, sensor_read_cmd->chan, &val);

    set_sensor_val(cmd->state, &val);
}
