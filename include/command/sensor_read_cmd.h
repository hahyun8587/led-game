#ifndef COMMAND_SENSORREADCMD
#define COMMAND_SENSORREADCMD

#include <zephyr/drivers/sensor.h>
#include "device_cmd.h"

struct sensor_read_cmd {
    struct device_cmd device_cmd;
    struct device *sensor;
    enum sensor_channel chan;
};

void init_sensor_read_cmd(struct sensor_read_cmd *cmd, 
                          struct service_state *state, 
                          struct device *sensor, enum sensor_channel chan);
struct sensor_read_cmd *sensor_read_cmd_get_inst(struct service_state *state, 
        struct device *sensor, enum sensor_channel chan);              
void sensor_read_cmd_execute(struct device_cmd *cmd);

#endif
