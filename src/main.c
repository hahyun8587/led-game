#include "application.h"
#include "node.h"
#include "state/game_set_state.h"

int main() {
    struct game_set_state game_set_state;
    struct dev led_matrix;
    struct dev battery_led;
    struct dev joystick;
    struct dev qdec_dial;
    struct dev qdec_btn;
    struct displayer displayer;
    struct app app;
    struct gpio_dt_spec sw = GPIO_DT_SPEC_GET(ROTARY_ENCODER_NODE, gpios);

    init_displayer(&displayer, &led_matrix, &battery_led);
    
    init_game_set_state(&game_set_state);
    init_dev(&qdec_dial, 
             (struct device_cmd *) sensor_read_cmd_get_inst(&game_set_state, 
                    DEVICE_DT_GET(QDEC_NODE), SENSOR_CHAN_ROTATION));
    init_dev(&qdec_btn, 
             (struct device_cmd *) gpio_read_cmd_get_inst(
                    &game_set_state, &sw));
    
    init_app(&app, &displayer, &joystick, &qdec_dial, &qdec_btn, 
             &game_set_state);

    start(&app);

    return 0;
}
