#include "command/adc_read_cmd.h"

static struct adc_read_cmd cmd; 

/**
 * @brief Initializes adc_read_cmd instance.
 * 
 * @param cmd pointer to the adc_read_cmd instance
 * @param state service_state instance
 * @param chans adc channels
 * @param num_chans the number adc channels
 */
void init_adc_read_cmd(struct adc_read_cmd *cmd, struct service_state *state,
                       struct adc_dt_spec *chans, int num_chans) {    
    init_device_cmd((struct device_cmd *) cmd, state, adc_read_cmd_execute);
    
    for (int i = 0; i < num_chans; i++) {
        cmd->chans[i] = chans[i];
    }

    cmd->num_chans = num_chans;
}

/**
 * @brief Gets adc_read_cmd instance.
 * 
 * @param state service_state instance
 * @param chans array of adc_dt_spec instance
 * @param num_chans the number of adc channels
 * @return adc_read_cmd instance
 */
struct adc_read_cmd *adc_read_cmd_get_inst(struct service_state *state, 
        struct adc_dt_spec *chans, int num_chans) {
    init_adc_read_cmd(&cmd, state, chans, num_chans);

    return &cmd;
}

/**
 * @brief Reads values from adc channels.
 * 
 * @param cmd pointer to adc_read_cmd instance
 */
void adc_read_cmd_execute(struct device_cmd *cmd) {
    struct adc_read_cmd *arc = (struct adc_read_cmd *) cmd; 

    for (int i = 0; i < arc->num_chans; i++) {
        uint16_t buf;
        struct adc_sequence seq = 
                { .options = NULL, .buffer = &buf, 
                  .buffer_size = sizeof(buf), .calibrate = false };
        
        adc_channel_setup_dt(arc->chans + i);
        adc_sequence_init_dt(arc->chans + i, &seq);
        adc_read(arc->chans[i].dev, &seq);
        adc_raw_to_millivolts_dt(arc->chans + i, (int32_t *) seq.buffer);
        set_adc_val(cmd->state, (int) buf, i);
    }
}
