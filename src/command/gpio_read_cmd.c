#include "command/gpio_read_cmd.h"

static struct gpio_read_cmd cmd;

/**
 * @brief Initializes gpio_read_cmd instance.
 * 
 * @param cmd pointer to the gpio_read_cmd instnace
 * @param state service_state instance
 * @param pin gpio_dt_spec instance
 */
void init_gpio_read_cmd(struct gpio_read_cmd *cmd, 
        struct service_state *state, struct gpio_dt_spec *pin) {
    init_device_cmd((struct device_cmd *) cmd, state, gpio_read_cmd_execute);
    
    cmd->pin = pin; 
    gpio_pin_configure_dt(cmd->pin, GPIO_INPUT);
}

/**
 * @brief Gets gpio_read_cmd instance.
 * 
 * @param state service_state instance
 * @param pin gpio_dt_spec instance
 * @return pointer to the gpio_read_cmd instance
 */
struct gpio_read_cmd *gpio_read_cmd_get_inst(
        struct service_state *state, struct gpio_dt_spec *pin) {
    init_gpio_read_cmd(&cmd, state, pin);

    return &cmd;
}

/**
 * @brief Reads gpio input pin value. 
 * 
 * @param cmd pointer to the gpio_read_cmd instance
 */
void gpio_read_cmd_execute(struct device_cmd *cmd) {
    struct gpio_read_cmd *gpio_read_cmd = (struct gpio_read_cmd *) cmd;
    
    set_gpio_val(cmd->state, gpio_pin_get_dt(gpio_read_cmd->pin));
}
