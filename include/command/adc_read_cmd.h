#ifndef COMMAND_ADCREADCMD_H
#define COMMAND_ADCREADCMD_H

#include <zephyr/drivers/adc.h>
#include "device_cmd.h"

#define MAX_CHANS  4

struct adc_read_cmd {
    struct device_cmd device_cmd;
    struct adc_dt_spec chans[MAX_CHANS];
    int num_chans;
};

void init_adc_read_cmd(struct adc_read_cmd *cmd, struct service_state *state, 
                       struct adc_dt_spec *chans, int num_chans);
struct adc_read_cmd *adc_read_cmd_get_inst(
        struct service_state *state, struct adc_dt_spec *chans, int num_chans);
void adc_read_cmd_execute(struct device_cmd *cmd);

#endif
