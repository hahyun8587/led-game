#include "command/i2c_write_cmd.h"
#include "command/tm1651_write_cmd.h"
#include "displayer.h"
#include "node.h"

#define HT16K33_SYSTEM_ON_CMD   0x21U
#define HT16K33_DISPLAY_ON_CMD  0x81U
#define HT16K33_CMD_LEN         1

#define MAX_DATA_SIZE           16

static uint8_t health2byte(int health);
static void ht16k33_init(struct displayer *displayer);

/**
 * @brief Initializes displayer instance.
 * 
 * @param displayer pointer to the displayer instance
 * @param led_matrix dev instance that represents led matrix
 * @param battery_led dev instancce that represents battery led
 */
void init_displayer(struct displayer *displayer, 
                    struct dev *led_matrix, struct dev *battery_led) {
    displayer->led_matrix = led_matrix;
    displayer->battery_led = battery_led;

    ht16k33_init(displayer);
}

/**
 * @brief Initializes ht16k33 led matrix hardware. 
 * 
 * @param displayer pointer to the displayer instance
 */
static void ht16k33_init(struct displayer *displayer) {
    struct i2c_dt_spec led_spec = I2C_DT_SPEC_GET(HT16K33_NODE);
    const uint8_t init_cmds[] = { HT16K33_SYSTEM_ON_CMD, 
                                  HT16K33_DISPLAY_ON_CMD };

    for (int i = 0; i < sizeof(init_cmds) / sizeof(uint8_t); i++) {
        set_cmd(displayer->led_matrix, 
                (struct device_cmd *) i2c_write_cmd_get_inst(
                        &led_spec, init_cmds + i, HT16K33_CMD_LEN));
        request(displayer->led_matrix);
    }
}

/**
 * @brief Displays game to UI.
 * 
 * @param displayer pointer to the displayer instance
 * @param player player instance to be displayed
 * @param enemies array of enemy instance to be displayed
 * @param num_enemies the number of the enemy instances 
 */
void display_game(struct displayer *displayer, struct player *player,
                  struct enemy *enemies, int num_enemies) {
    struct i2c_dt_spec led = I2C_DT_SPEC_GET(HT16K33_NODE);
    struct gpio_dt_spec clk = GPIO_DT_SPEC_GET_BY_IDX(TM1651_NODE, gpios, 0);
    struct gpio_dt_spec dio = GPIO_DT_SPEC_GET_BY_IDX(TM1651_NODE, gpios, 1);
    uint8_t buf[MAX_DATA_SIZE + 1] = { 0 };

    buf[player->unit.loc / (BOARD_WID / 2) + 1] |= 
            1 << player->unit.loc % (BOARD_WID / 2);

    for (int i = 0; i < num_enemies; i++) {
        buf[enemies[i].unit.loc / (BOARD_WID / 2) + 1] |= 
                1 << enemies[i].unit.loc % (BOARD_WID / 2);
    }

    set_cmd(displayer->led_matrix, 
            (struct device_cmd *) i2c_write_cmd_get_inst(
                    &led, buf, MAX_DATA_SIZE + 1));
    request(displayer->led_matrix);

    set_cmd(displayer->battery_led, 
            (struct device_cmd *) tm1651_write_cmd_get_inst(
                    &clk, &dio, health2byte(player->health)));
    request(displayer->battery_led);    
}

/**
 * @brief Displays number to UI.
 * 
 * @param displayer pointer to the displayer instance
 * @param num number to be displayed 
 */
void display_number(struct displayer *displayer, int num) {
    struct i2c_write_cmd cmd;
    struct i2c_dt_spec led = I2C_DT_SPEC_GET(HT16K33_NODE);
    uint8_t numbers_bytes[][8] = 
        { { 0x38, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38 }, 
          { 0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x7C },
          { 0x10, 0x28, 0x44, 0x20, 0x10, 0x08, 0x04, 0x7C },
          { 0x3C, 0x40, 0x40, 0x3C, 0x40, 0x40, 0x40, 0x3C },
          { 0x20, 0x30, 0x28, 0x24, 0x7E, 0x20, 0x20, 0x20 },
          { 0x7C, 0x04, 0x04, 0x3C, 0x40, 0x40, 0x44, 0x38 },
          { 0x38, 0x04, 0x04, 0x3C, 0x44, 0x44, 0x44, 0x38 },
          { 0x7C, 0x44, 0x44, 0x44, 0x40, 0x40, 0x40, 0x40 },
          { 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x44, 0x38 },
          { 0x38, 0x44, 0x44, 0x44, 0x78, 0x40, 0x40, 0x40 } };
    uint8_t buf[BUF_SIZE] = { 0 };

    for (int i = 1; i < BUF_SIZE; i++) {
        buf[i] = i % 2 == 0 ? numbers_bytes[num % 10][(i - 1) / 2] 
                            : numbers_bytes[num / 10][(i - 1) / 2];
    }

    init_i2c_write_cmd(&cmd, &led, buf, MAX_DATA_SIZE + 1);
    set_cmd(displayer->led_matrix, &cmd);
    request(displayer->led_matrix);
}

static uint8_t health2byte(int health) {    
    uint8_t byte = 0x00;

    for (int i = 1; i <= health; i++) {
        byte |= 1 << (8 - i);
    }

    return byte;
}
