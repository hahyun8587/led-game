#ifndef COMMAND_DEVICECMD_H
#define COMMAND_DEVICECMD_H

#include "state/service_state.h"

/**
 * @brief Supports command pattern whose receiver is an instance of 
 *      service_state interface.
 * 
 */
struct device_cmd {
    struct service_state *state;
    void (*execute)(struct device_cmd *);
};

typedef void (*execute_t)(struct device_cmd *);

void init_device_cmd(struct device_cmd *cmd, 
                     struct service_state *state, execute_t execute);

#endif
