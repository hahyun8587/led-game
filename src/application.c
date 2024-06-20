#include "application.h"

static void begin_state(struct app *app);

/**
 * @brief Initializes app instance.
 * 
 * @param app pointer to app instance
 * @param displayer displayer instance
 * @param joystick dev instance that represents joystick
 * @param qdec_dial dev instance that represent qdec dial
 * @param qdec_btn dev instance that represent qdec button
 * @param state service_state instance
 */
void init_app(struct app *app, struct displayer *displayer, 
        struct dev *joystick, struct dev *qdec_dial, struct dev *qdec_btn, 
        struct service_state *state ) {
    app->displayer = displayer;
    app->joystick = joystick;
    app->qdec_dial = qdec_dial;
    app->qdec_btn = qdec_btn;
    app->state = state;
}

/**
 * @brief Starts app instance.
 * 
 * @param app pointer to app instance
 */
void start(struct app *app) {
    while (1) {
        printk("begin state\n");
        begin_state(app);
    }
}

/**
 * @brief Begins `state`.
 * 
 * @param app pointer to the app instance
 */
static void begin_state(struct app *app) {
    app->state->begin(app->state, app);
}

struct displayer *get_displayer(struct app *app) {
    return app->displayer;
}

struct dev *get_joystick(struct app *app) {
    return app->joystick;
}

struct dev *get_qdec_dial(struct app *app) {
    return app->qdec_dial;
}

struct dev *get_qdec_btn(struct app *app) {
    return app->qdec_btn;
}

void set_state(struct app *app, struct service_state *state) {
    app->state = state;
}
