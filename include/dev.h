#ifndef DEV_H
#define DEV_H

#include "command/device_cmd.h"

#define JOY_X   0
#define JOY_Y   1

#define JOY_LEFT_THRESH     100
#define JOY_RIGHT_THRESH    2000
#define JOY_UP_THRESH       2000
#define JOY_DOWN_THRESH     1000

struct dev {
    struct device_cmd *cmd;
};

void init_dev(struct dev *dev, struct device_cmd *cmd);
void request(struct dev *dev);
void set_cmd(struct dev *dev, struct device_cmd *cmd);

#endif
