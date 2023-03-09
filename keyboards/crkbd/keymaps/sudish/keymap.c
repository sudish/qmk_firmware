#include QMK_KEYBOARD_H
#include "version.h"

extern uint8_t is_master;

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif

#include <stdio.h>
#include <string.h>

// Define our keymap using the common sections defined elsewhere.
// Only the keys specific to this board are specified here.
#include "sudish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [U_BASE] = LAYOUT_wrapper(
    KC_ESC,  ___________________BASE_L1_________________,              ___________________BASE_R1_________________, QK_BOOT,
    KC_CAPS, ___________________BASE_L2_________________,              ___________________BASE_R2_________________, KC_QUOT,
    TG_TAP,  ___________________BASE_L3_________________,              ___________________BASE_R3_________________, TG_TAP,
                                           ___________________BASE_B6_________________
  ),

  [U_TAP] = LAYOUT_wrapper(
    _______, ___________________TAP_L1__________________,              ___________________TAP_R1__________________, _______,
    _______, ___________________TAP_L2__________________,              ___________________TAP_R2__________________, _______,
    _______, ___________________TAP_L3__________________,              ___________________TAP_R3__________________, _______,
                                           ___________________TAP_B6__________________
  ),

  [U_NAV] = LAYOUT_wrapper(
    _______, ___________________NAV_L1__________________,              ___________________NAV_R1__________________, _______,
    _______, ___________________NAV_L2__________________,              ___________________NAV_R2__________________, _______,
    _______, ___________________NAV_L3__________________,              ___________________NAV_R3__________________, _______,
                                           ___________________NAV_B6__________________
  ),

  [U_MOUSE] = LAYOUT_wrapper(
    _______, _________________MOUSE_L1__________________,              _________________MOUSE_R1__________________, _______,
    _______, _________________MOUSE_L2__________________,              _________________MOUSE_R2__________________, _______,
    _______, _________________MOUSE_L3__________________,              _________________MOUSE_R3__________________, _______,
                                           _________________MOUSE_B6__________________
  ),

  [U_MEDIA] = LAYOUT_wrapper(
    _______, _________________MEDIA_L1__________________,              _________________MEDIA_R1__________________, _______,
    _______, _________________MEDIA_L2__________________,              _________________MEDIA_R2__________________, _______,
    _______, _________________MEDIA_L3__________________,              _________________MEDIA_R3__________________, _______,
                                           _________________MEDIA_B6__________________
  ),

  [U_NUM] = LAYOUT_wrapper(
    _______, ___________________NUM_L1__________________,              ___________________NUM_R1__________________, _______,
    _______, ___________________NUM_L2__________________,              ___________________NUM_R2__________________, _______,
    _______, ___________________NUM_L3__________________,              ___________________NUM_R3__________________, _______,
                                           ___________________NUM_B6__________________
  ),

  [U_SYM] = LAYOUT_wrapper(
    _______, ___________________SYM_L1__________________,              ___________________SYM_R1__________________, _______,
    _______, ___________________SYM_L2__________________,              ___________________SYM_R2__________________, _______,
    _______, ___________________SYM_L3__________________,              ___________________SYM_R3__________________, _______,
                                           ___________________SYM_B6__________________
  ),

  [U_FUN] = LAYOUT_wrapper(
    _______, ___________________FUN_L1__________________,              ___________________FUN_R1__________________, _______,
    _______, ___________________FUN_L2__________________,              ___________________FUN_R2__________________, _______,
    _______, ___________________FUN_L3__________________,              ___________________FUN_R3__________________, _______,
                                           ___________________FUN_B6__________________
  )
};


#ifdef RGB_MATRIX_ENABLE
void set_layer_rgb_indicator_keymap(uint8_t red, uint8_t green, uint8_t  blue) {
    rgb_matrix_layer_helper(red, green, blue, LED_FLAG_UNDERGLOW);
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    char buf[10];
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
    #define MIRYOKU_X(LAYER, STRING) case U_##LAYER: oled_write_P(PSTR(STRING), false); break;
    MIRYOKU_LAYER_LIST
    #undef MIRYOKU_X
    default:
        oled_write_P(PSTR("Undef-"), false);
        snprintf(buf,sizeof(buf), "%u", layer_state);
        oled_write(buf, false);
    }
    oled_write_P(PSTR("\n"), false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
