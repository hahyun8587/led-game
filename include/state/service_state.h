#ifndef STATE_SERVICESTATE_H
#define STATE_SERVICESTATE_H

#include <zephyr/drivers/sensor.h>
#include "application.h"

//Supports state pattern for application.

struct service_state {
    struct sensor_value sensor_val;
    int adc_vals[2];
    int gpio_val;
    void (*begin)(struct service_state *, struct app *);
};

typedef void (*begin_t)(struct service_state *, struct app *);

void init_service_state(struct service_state *state, begin_t begin);
void set_sensor_val(struct service_state *state, struct sensor_value *val);
void set_adc_val(struct service_state *state, int adc_val, int idx);
void set_gpio_val(struct service_state *state, int gpio_val);

#endif
