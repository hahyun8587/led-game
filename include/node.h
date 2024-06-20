#ifndef NODE_H
#define NODE_H

#define HT16K33_NODE            DT_CHILD(DT_NODELABEL(i2c0), ht16k33_70)
#define QDEC_NODE               DT_NODELABEL(qdec)
#define ROTARY_ENCODER_NODE     DT_CHILD(DT_NODELABEL(shield_gpios), rotary_encoder)
#define TM1651_NODE             DT_CHILD(DT_NODELABEL(shield_gpios), tm1651)
#define USER_NODE               DT_PATH(zephyr_user)

#endif 