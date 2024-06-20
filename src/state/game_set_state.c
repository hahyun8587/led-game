#include <zephyr/drivers/adc.h>
#include "command/adc_read_cmd.h"
#include "command/i2c_write_cmd.h"
#include "node.h"
#include "state/game_set_state.h"
#include "state/game_state.h"

static struct game_set_state state;

/**
 * @brief Initializes game_set_state instance.
 * 
 * @param state pointer to the game_set_state instance
 */
void init_game_set_state(struct game_set_state *state) {
    init_service_state((struct service_state *) state, game_set_state_begin);
}

/**
 * @brief Gets game_set_state instance.
 * 
 * @return pointer to the game_set_state instance
 */
struct game_set_state *game_set_state_get_inst() {
    init_game_set_state(&state);

    return &state;
}

/**
 * @brief Begins game set state.
 * 
 * @param state pointer to the game_set_state instance
 * @param app application instance
 */
void game_set_state_begin(struct service_state *state, struct app *app) {
    struct service_state *next_state;
    struct dev *displayer = get_displayer(app);
    struct dev *qdec_dial = get_qdec_dial(app);
    struct dev *qdec_btn = get_qdec_btn(app);
    struct adc_dt_spec chans[] = { ADC_DT_SPEC_GET_BY_IDX(USER_NODE, 0), 
                                   ADC_DT_SPEC_GET_BY_IDX(USER_NODE, 1) };
    int diff = MIN_DIFF;
    printk("game_set_state\n");
    do {
        request(qdec_dial);

        if (state->sensor_val.val1 < 0) {
            diff = diff == MAX_DIFF ? MIN_DIFF : diff + 1;
        } else if (state->sensor_val.val1 > 0) {
            diff = diff == MIN_DIFF ? MAX_DIFF : diff - 1;
        }
       
        display_number(displayer, diff);
        k_msleep(500);
        request(qdec_btn);
    } while (state->gpio_val);
    
    next_state = (struct service_state *) game_state_get_inst(diff);

    set_cmd(get_joystick(app), 
            (struct device_cmd *) adc_read_cmd_get_inst(next_state, chans, 2));
    set_state(app, next_state);
}
