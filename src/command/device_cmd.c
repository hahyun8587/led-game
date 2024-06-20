#include "command/device_cmd.h"

/**
 * @brief Initializes device_cmd instance.
 * 
 * @param cmd pointer to the device_cmd instance
 * @param state service state instance
 * @param execute execute function
 */
void init_device_cmd(struct device_cmd *cmd, 
                     struct service_state *state, execute_t execute) {
    cmd->state = state;
    cmd->execute = execute;
}
