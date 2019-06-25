#include QMK_KEYBOARD_H
#include "sudish.h"


/* Layers to color map */
#ifdef RGB_MATRIX_ENABLE
typedef struct PACKED {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} sjRGB;

sjRGB layer_to_color[] = {
    [_QWERTY] = { RGB_WHITE },
    [_NUMBER] = { RGB_GREEN },
    [_FUNC]   = { RGB_SPRINGGREEN },
    [_SYMBOL] = { RGB_CHARTREUSE },
    [_REGEX]  = { RGB_TEAL },
    [_SYSTEM] = { RGB_BLUE },
    [_N_LAYERS] = { RGB_RED } // catch all color for unknown layer values
};

__attribute__ ((weak))
void set_layer_rgb_indicator_keymap(uint8_t r, uint8_t g, uint8_t b) {
    return;
}

void set_layer_rgb_indicator(uint8_t layer) {
    if (layer > _N_LAYERS) { layer = _N_LAYERS; };
    set_layer_rgb_indicator_keymap(layer_to_color[layer].r, layer_to_color[layer].g, layer_to_color[layer].b);
}
#endif // RGB_MATRIX_ENABLED

__attribute__ ((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);

#ifdef RGB_MATRIX_ENABLE
    set_layer_rgb_indicator(biton32(state));
#endif // RGB_MATRIX_ENABLED

    return layer_state_set_keymap(state);
}

void keyboard_post_init_user(void) {
    // Simulate a layer change to the default at startup so hooks can run
    layer_state_set_user(1UL << _QWERTY);
}

#ifdef RGB_MATRIX_ENABLE
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}
#endif
