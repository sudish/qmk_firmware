#include "chimera_ergo_mini.h"
#include "version.h"

// The board's header doesn't define a clean layout macro, so do it ourselves.
#define KEYMAP( \
  k00, k01, k02, k03, k04,           k05, k06, k07, k08, k09, \
  k10, k11, k12, k13, k14,           k15, k16, k17, k18, k19, \
  k20, k21, k22, k23, k24,           k25, k26, k27, k28, k29, \
  k30, k31, k32, k33, k34,           k35, k36, k37, k38, k39, \
            k40, k41, k42,           k43, k44, k45 \
) \
{ \
  { k10,   k00, k21, k12, k03,       k06, k17, k28, k09, k19   }, \
  { k20,   k01, k31, k22, k13,       k16, k27, k38, k08, k29   }, \
  { k30,   k11, k02, k32, k23,       k26, k37, k07, k18, k39   }, \
  { KC_NO, k33, k04, k14, k24,       k25, k15, k05, k36, KC_NO }, \
  { KC_NO, k40, k41, k42, k34,       k35, k43, k44, k45, KC_NO }, \
}

// Define our keymap using the common sections defined elsewhere.
// Only the keys specific to this board are specified here.
#include "sudish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    KC_1,    KC_2,     KC_3,     KC_4,     KC_5,              KC_6,     KC_7,     KC_8,     KC_9,    KC_0,
    _________________QWERTY_L1_________________,              _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________,              _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________,              _________________QWERTY_R3_________________,
                                 _________________QWERTY_B6_________________
  ),

  [_NUMBER] = LAYOUT_wrapper(
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
    ________________NUMBER_L1__________________,              ________________NUMBER_R1__________________,
    ________________NUMBER_L2__________________,              ________________NUMBER_R2__________________,
    ________________NUMBER_L3__________________,              ________________NUMBER_R3__________________,
                                  ________________NUMBER_B6__________________
  ),

  [_FUNC] = LAYOUT_wrapper( \
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
    ________________FUNC_L1____________________,              ________________FUNC_R1____________________,
    ________________FUNC_L3____________________,              ________________FUNC_R2____________________,
    ________________FUNC_L3____________________,              ________________FUNC_R3____________________,
                                  ________________FUNC_B6____________________
  ),

  [_SYMBOL] = LAYOUT_wrapper(
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
    ________________SYMBOL_L1__________________,              ________________SYMBOL_R1__________________,
    ________________SYMBOL_L2__________________,              ________________SYMBOL_R2__________________,
    ________________SYMBOL_L3__________________,              ________________SYMBOL_R3__________________,
                                  ________________SYMBOL_B6__________________
  ),

  [_REGEX] = LAYOUT_wrapper(
    _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,
    ________________REGEX_L1___________________,              ________________REGEX_R1___________________,
    ________________REGEX_L2___________________,              ________________REGEX_R2___________________,
    ________________REGEX_L3___________________,              ________________REGEX_R3___________________,
                                  ________________REGEX_B6___________________
  ),

  [_SYSTEM] = LAYOUT_wrapper( \
    RESET,   VRSN,    _______, _______,  TG_SYS,              _______, _______, _______, _______, _______,
    ________________SYSTEM_L1__________________,              ________________SYSTEM_R1__________________,
    ________________SYSTEM_L2__________________,              ________________SYSTEM_R2__________________,
    ________________SYSTEM_L3__________________,              ________________SYSTEM_R3__________________,
                                  ________________SYSTEM_B6__________________
  )
};


void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case _QWERTY:
      set_led_blue;
      break;
    case _NUMBER:
      set_led_magenta;
      break;
    case _FUNC:
      set_led_cyan;
      break;
    case _SYMBOL:
      set_led_green;
      break;
    case _REGEX:
      set_led_yellow;
      break;
    case _SYSTEM:
      set_led_red;
      break;
    default:
      set_led_white;
      break;
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN: // Prints firmware version
      if (record->event.pressed) {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), 5);
      }
      break;
  }
  return true;
}
