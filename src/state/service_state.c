#include "state/service_state.h"

/**
 * @brief Initializes service_state instance.
 * 
 * @param state pointer to the service_state instance
 * @param begin begin function
 */
void init_service_state(struct service_state *state, begin_t begin) {
    state->begin = begin;
}

void set_sensor_val(struct service_state *state, struct sensor_value *val) {
    state->sensor_val = *val;
}

void set_adc_val(struct service_state *state, int adc_val, int idx) {
    state->adc_vals[idx] = adc_val;
}

void set_gpio_val(struct service_state *state, int gpio_val) {
    state->gpio_val = gpio_val;
}
