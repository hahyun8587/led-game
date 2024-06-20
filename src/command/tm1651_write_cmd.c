#include <zephyr/kernel.h>
#include "command/tm1651_write_cmd.h"

static void write_bytes(struct tm1651_write_cmd *cmd, uint8_t *buf, int len);

static struct tm1651_write_cmd cmd;

/**
 * @brief Initializes tm1651_write_cmd instance.
 * 
 * @param cmd pointer to the tm1651_write_cmd instance
 * @param clk gpio clock
 * @param dio gpio data io
 * @param val value to be written
 */
void init_tm1651_write_cmd(struct tm1651_write_cmd *cmd, 
        struct gpio_dt_spec *clk, struct gpio_dt_spec *dio, uint8_t val) {
	init_device_cmd((struct device_cmd *) cmd, NULL, tm1651_write_cmd_execute);

    cmd->clk = clk;
    cmd->dio = dio;
    cmd->val = val;
}

/**
 * @brief Gets tm1651_write_cmd instance.
 * 
 * @param clk gpio clock
 * @param dio gpio data io
 * @param val value to be written
 * @return pointer to the tm1651_write_cmd instance
 */
struct tm1651_write_cmd *tm1651_write_cmd_get_inst(
        struct gpio_dt_spec *clk, struct gpio_dt_spec *dio, uint8_t val) {
    
    init_tm1651_write_cmd(&cmd, clk, dio, val);

    return &cmd;
}

/**
 * @brief Turns on battery led according to `val`.
 * 
 * @param cmd pointer to the tm1651_write_cmd instance
 * 
 */
void tm1651_write_cmd_execute(struct device_cmd *cmd) {
    struct tm1651_write_cmd *twc = (struct tm1651_write_cmd *) cmd;
    uint8_t data_cmd_buf[] = { TM1651_DATA_CMD };
    uint8_t addr_cmd_buf[] = { TM1651_ADDR_CMD, 
							   twc->val, TM1651_FRAME_ON_DATA };
    uint8_t disp_cmd_buf[] = { TM1651_DISP_CMD };

    write_bytes(twc, data_cmd_buf, sizeof(data_cmd_buf));
    write_bytes(twc, addr_cmd_buf, sizeof(addr_cmd_buf));
    write_bytes(twc, disp_cmd_buf, sizeof(disp_cmd_buf));
}

/**
 * @brief Writes bytes to tm1651 device.
 * 
 * @param cmd pointer to tm1651_write_cmd instance
 * @param buf buffer of bytes to be written
 * @param len the length of buffer
 */
static void write_bytes(struct tm1651_write_cmd *cmd, uint8_t *buf, int len) {
    gpio_pin_configure_dt(cmd->dio, GPIO_OUTPUT);
	k_sleep(K_TICKS(1));

	for (int i = 0; i < len; i++) {
		uint8_t data = buf[i];

		for (int i = 1; i <= 8; i++) {
			gpio_pin_configure_dt(cmd->clk, GPIO_OUTPUT);
			k_sleep(K_TICKS(1));	

			if (data & 0x01) {
				gpio_pin_configure_dt(cmd->dio, GPIO_INPUT);
			} else {
				gpio_pin_configure_dt(cmd->dio, GPIO_OUTPUT);
			}

			k_sleep(K_TICKS(1));

			gpio_pin_configure_dt(cmd->clk, GPIO_INPUT);
			k_sleep(K_TICKS(1));

			data >>= 1;
		}
	}

	gpio_pin_configure_dt(cmd->clk, GPIO_OUTPUT);
	gpio_pin_configure_dt(cmd->dio, GPIO_INPUT);
	k_sleep(K_TICKS(1));

	gpio_pin_configure_dt(cmd->clk, GPIO_INPUT);
	k_sleep(K_TICKS(1));

	gpio_pin_configure_dt(cmd->clk, GPIO_OUTPUT);
	k_sleep(K_TICKS(1));

	gpio_pin_configure_dt(cmd->dio, GPIO_OUTPUT);	
	k_sleep(K_TICKS(1));

	gpio_pin_configure_dt(cmd->clk, GPIO_INPUT);
	k_sleep(K_TICKS(1));

	gpio_pin_configure_dt(cmd->dio, GPIO_INPUT);	
	k_sleep(K_TICKS(1));
}
