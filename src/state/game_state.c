#include <zephyr/kernel.h>
#include <zephyr/random/rand32.h>
#include "command/gpio_read_cmd.h"
#include "command/sensor_read_cmd.h"
#include "node.h"
#include "state/game_set_state.h"
#include "state/game_state.h"
#include "strategy/patrol_strat.h"
#include "strategy/rand_strat.h"

static int gen_rand_loc(struct game_state *state);
static bool is_overlapped(struct game_state *state, 
        struct player *player, struct enemy *enemies, int num_enemies);
static void respawn_all(struct game_state *state, struct player *player, 
                        struct enemy *enemies, int num_enemies);
static void init_rand_enemy(struct game_state *state, struct enemy *enemy, 
        struct patrol_strat *patrol_strat, struct rand_strat *rand_strat, 
        int *patrol_strat_idx);

static struct game_state state;

/**
 * @brief Initialzes game_state instance.
 * 
 * @param state pointer to the game_state instance
 * @param diff game difficulty
 */
void init_game_state(struct game_state *state, int diff) {
    init_service_state((struct service_state *) state, game_state_begin);

    state->diff = diff;
    state->score = 0;
}

/**
 * @brief Gets game_state instance.
 * 
 * @param diff difficulty of the game
 * @return pointer to the game_state instance
 */
struct game_state *game_state_get_inst(int diff) {
    init_game_state(&state, diff);

    return &state;
}

/**
 * @brief Begins game state.
 * 
 * @param state pointer to the game_state instance
 * @param app app instance
 */
void game_state_begin(struct service_state *state, struct app *app) {
    struct player player;
    struct patrol_strat patrol_strats[MAX_DIFF];
    struct rand_strat rand_strat;
    struct enemy enemies[MAX_DIFF];
    struct service_state *next_state;
    struct game_state *game_state = (struct game_state *) state;
    struct displayer *displayer = get_displayer(app);
    struct dev *joystick = get_joystick(app);
    struct gpio_dt_spec sw = GPIO_DT_SPEC_GET(ROTARY_ENCODER_NODE, gpios);
    int patrol_strats_idx = 0;
    
    init_player(&player, INIT_PLAYER_LOC, MAX_HEALH, false);
    
    init_rand_strat(&rand_strat);

    for (int i = 0; i < game_state->diff; i++) {
        init_rand_enemy(game_state, enemies + i, 
                        patrol_strats + patrol_strats_idx, &rand_strat, 
                        &patrol_strats_idx);
    }

    while (game_state->diff <= MAX_DIFF && player.health > 0) {
        request(joystick);
        
        if (state->adc_vals[JOY_X] < JOY_LEFT_THRESH) {
            move_left(&player);
        } else if (state->adc_vals[JOY_X] < JOY_RIGHT_THRESH) {
            move_right(&player);
        } else if (state->adc_vals[JOY_Y] < JOY_DOWN_THRESH) {
            move_down(&player);
        } else if (state->adc_vals[JOY_Y] < JOY_UP_THRESH) {
            move_up(&player);
        }

        for (int i = 0; i < game_state->diff; i++) {
            move(enemies + i);
        }

        if (is_overlapped(game_state, &player, enemies, game_state->diff)) {
            lose_health(&player);
            respawn_all(game_state, &player, enemies, game_state->diff);
        }

        display_game(displayer, &player, enemies, game_state->diff);

        if (get_loc(&player.unit) % BOARD_WID == BOARD_WID - 1) {   
            game_state->score++;

            respawn_all(game_state, &player, enemies, game_state->diff);
            init_rand_enemy(game_state, enemies + game_state->diff, 
                        patrol_strats + patrol_strats_idx, &rand_strat, 
                        &patrol_strats_idx);

            game_state->diff++;
        }
        printk("%d\n", patrol_strats_idx);
        k_msleep(400);
    }
    
    next_state = (struct service_state *) game_set_state_get_inst();

    set_cmd(get_qdec_dial(app), 
            (struct device_cmd *) sensor_read_cmd_get_inst(next_state, 
                    DEVICE_DT_GET(QDEC_NODE), SENSOR_CHAN_ROTATION));
    set_cmd(get_qdec_btn(app), 
            (struct device_cmd *) gpio_read_cmd_get_inst(next_state, &sw));
    set_state(app, next_state);
    printk("exit game_state\n");
}

/**
 * @brief Generates random location that does not exceed `SAFETY_BOARDER`.
 * 
 * @param state pointer to the game_state instance
 * @return random location
 */
static int gen_rand_loc(struct game_state *state) {
    int rand_loc;

    rand_loc = sys_rand32_get() % (BOARD_HEI * BOARD_WID);

    if (rand_loc % BOARD_WID < SAFETY_BOARDER) {
        rand_loc += SAFETY_BOARDER - rand_loc % BOARD_WID;
    }         

    return rand_loc;
}

/**
 * @brief Checks whether `player` and `enemies` have the same `loc` value.
 * 
 * @param state pointer to the game state instance
 * @param player player instance
 * @param enemies array of enemy instance
 * @param num_enemies the number of enemy instances
 * @return true if `player` has the same `loc` value with `enemies`, 
 * @return false otherwise
 */
static bool is_overlapped(struct game_state *state, 
        struct player *player, struct enemy *enemies, int num_enemies) {
    int player_loc = get_loc(&player->unit);

    for (int i = 0; i < num_enemies; i++) {
        if (player_loc == get_loc(&enemies[i].unit)) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Sets `loc` of `player` and `enemies` to `init_loc` value.
 * 
 * @param state pointer to the game_state instance
 * @param player player instance
 * @param enemies array of enemy instance
 * @param num_enemies the number of enemy instances
 */
static void respawn_all(struct game_state *state, struct player *player, 
                        struct enemy *enemies, int num_enemies) {
    respawn(&player->unit);

    for (int i = 0; i < state->diff; i++) {
        respawn(&enemies[i].unit);
    }
}

/**
 * @brief Initializes `enemy` with random location and random move_strategy instance.
 * 
 * Initializes `patrol_strat` and increases `patrol_strats_idx` by `1`
 * if patrol_strat is selected for the move_strategy instance.
 * 
 * @param state pointer to the game_state instance
 * @param enemy enemy instance to be initialized
 * @param patrol_strat patrol strat instance to be initialized potentially 
 * @param rand_strat rand_strat instance
 * @param patrol_strats_idx patrol strategies index
 */
static void init_rand_enemy(struct game_state *state, struct enemy *enemy,  
        struct patrol_strat *patrol_strat, struct rand_strat *rand_strat,
        int *patrol_strats_idx) {
    if (1) { //sys_rand32_get() % NUM_STRATS == 0) {
        init_patrol_strat(patrol_strat);
        init_enemy(enemy, patrol_strat, gen_rand_loc(state), false);
        
        (*patrol_strats_idx)++;
    } else {
        init_enemy(enemy, rand_strat, gen_rand_loc(state), false);
    }
}
