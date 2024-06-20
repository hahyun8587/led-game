#ifndef APP_H
#define APP_H

#include "displayer.h"
#include "dev.h"
#include "state/service_state.h"

struct app {
    struct displayer *displayer;
    struct dev *joystick;
    struct dev *qdec_dial;
    struct dev *qdec_btn;
    struct service_state *state;
};

void init_app(struct app *app, struct displayer *displayer, 
        struct dev *joystick, struct dev *qdec_dial, struct dev *qdec_btn, 
        struct service_state *state);
void start(struct app *app);
struct displayer *get_displayer(struct app *app);
struct dev *get_joystick(struct app *app);
struct dev *get_qdec_btn(struct app *app);
struct dev *get_qdec_dial(struct app *app);
void set_state(struct app *app, struct service_state *state);


#endif
