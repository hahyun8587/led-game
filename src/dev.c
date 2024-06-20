#include "dev.h"

/**
 * @brief Initializes dev instance.
 * 
 * @param dev pointer to the dev instance
 * @param cmd device_cmd instance
 */
void init_dev(struct dev *dev, struct device_cmd *cmd) {
    dev->cmd = cmd;
}

/**
 * @brief Requests `cmd`.
 * 
 * @param dev pointer to the dev instance
 */
void request(struct dev *dev) {
    dev->cmd->execute(dev->cmd);
}

void set_cmd(struct dev *dev, struct device_cmd *cmd) {
    dev->cmd = cmd;
}
