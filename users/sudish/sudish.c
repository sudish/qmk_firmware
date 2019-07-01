#include QMK_KEYBOARD_H
#include "sudish.h"


/* Layer names */
static const char *sj_layer_name[] = {
    [_QWERTY]   = "Default",
    [_NUMBER]   = "Number",
    [_FUNC]     = "Function",
    [_SYMBOL]   = "Symbol",
    [_REGEX]    = "Regex",
    [_SYSTEM]   = "System",
    [_GAME]     = "Game",
    [_GAMENF]   = "Game NF",
    [_GAMENAV]  = "Game Nav",
    [_ADJUST]   = "Adjust",
    [_N_LAYERS] = "Unknown"
};

const char *get_layer_name(uint8_t layer) {
    if (layer > _N_LAYERS) { layer = _N_LAYERS; };
    return sj_layer_name[layer];
}


/* Layers to color map */
#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;

typedef struct PACKED {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} sjRGB;

sjRGB layer_to_color[] = {
    [_QWERTY]   = { RGB_WHITE },
    [_NUMBER]   = { RGB_GREEN },
    [_FUNC]     = { RGB_SPRINGGREEN },
    [_SYMBOL]   = { RGB_CHARTREUSE },
    [_REGEX]    = { RGB_TEAL },
    [_SYSTEM]   = { RGB_BLUE },
    [_GAME]     = { RGB_GOLD },
    [_GAMENF]   = { RGB_GREEN },
    [_GAMENAV]  = { RGB_GOLDENROD },
    [_ADJUST]   = { RGB_MAGENTA },
    [_N_LAYERS] = { RGB_RED }       // Catchall color for unknown layer values
};

__attribute__ ((weak))
void set_layer_rgb_indicator_keymap(uint8_t r, uint8_t g, uint8_t b) {
    return;
}

void set_layer_rgb_indicator(uint8_t layer) {
    if (layer > _N_LAYERS) { layer = _N_LAYERS; };
    set_layer_rgb_indicator_keymap(layer_to_color[layer].r, layer_to_color[layer].g, layer_to_color[layer].b);
}
#endif // RGB_MATRIX_ENABLE

__attribute__ ((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGB_MATRIX_ENABLE
    set_layer_rgb_indicator(biton32(state));
#endif // RGB_MATRIX_ENABLE

    return layer_state_set_keymap(state);
}

void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif // RGB_MATRIX_ENABLE
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif // RGB_MATRIX_ENABLE
}

void keyboard_post_init_user(void) {
    // Simulate a layer change to the default at startup so hooks can run
    layer_state_set_user(1UL << _QWERTY);

#ifdef RGB_MATRIX_ENABLE
    // Don't write to the EEPROM unless needed
    if (!rgb_matrix_config.enable) { rgb_matrix_enable(); }
    if (rgb_matrix_config.mode != RGB_LAYER_INDICATOR_MODE) { rgb_matrix_mode(RGB_LAYER_INDICATOR_MODE); }
#endif // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_ENABLE
extern led_config_t g_led_config;

void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type) {
    if (rgb_matrix_config.enable
            && (rgb_matrix_config.mode == RGB_LAYER_INDICATOR_MODE)
            && !g_suspend_state) {
        for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
            if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
                rgb_matrix_set_color(i, red, green, blue);
            }
        }
    }
}
#endif // RGB_MATRIX_ENABLE
