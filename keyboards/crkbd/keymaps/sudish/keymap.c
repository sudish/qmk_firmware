#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "version.h"
#include "sudish.h"

extern keymap_config_t keymap_config;
extern uint8_t is_master;
#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config; // allows macro to read current RGB settings
#endif


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RGBRST,
  VRSN
};

// Layer Names
enum {
  _QWERTY = 0,
  _NUMBER,
  _FUNC,
  _SYMBOL,
  _REGEX,
  _SYSTEM,
  _MOUSE
};

// Layer when held, key otherwise
#define LT_TAB  LT(_NUMBER, KC_TAB)
#define LT_ESC  LT(_FUNC, KC_ESC)
#define LT_SPC  LT(_SYMBOL, KC_SPC)
#define LT_QUOT LT(_REGEX, KC_QUOT)
#define LT_ENT  LT(_SYSTEM, KC_ENT)
#define LT_BSPC LT(_MOUSE, KC_BSPC)

// Layer on/off toggle
#define TG_NUM  TG(_NUMBER)
#define TG_FUNC TG(_FUNC)
#define TG_SYM  TG(_SYMBOL)
#define TG_REGX TG(_REGEX)
#define TG_SYS  TG(_SYSTEM)
#define TG_MOUS TG(_MOUSE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    TG_FUNC, _________________QWERTY_L1_________________,              _________________QWERTY_R1_________________, TG_SYM,
    KC_CAPS, _________________QWERTY_L2_________________,              _________________QWERTY_R2_________________, TG_NUM,
    TG_MOUS, _________________QWERTY_L3_________________,              _________________QWERTY_R3_________________, TG_REGX,
                                     LT_ESC,  LT_QUOT, LT_TAB,   LT_ENT,  LT_SPC,  LT_BSPC
  ),

  [_NUMBER] = LAYOUT_wrapper(
    _______, ________________NUMBER_L1__________________,              ________________NUMBER_R1__________________, _______,
    _______, ________________NUMBER_L2__________________,              ________________NUMBER_R2__________________, _______,
    _______, ________________NUMBER_L3__________________,              ________________NUMBER_R3__________________, _______,
                                     _______, _______, _______,  _______, KC_0,    KC_PEQL
  ),

  [_FUNC] = LAYOUT_wrapper( \
    _______, ________________FUNC_L1____________________,              ________________FUNC_R1____________________, _______,
    _______, ________________FUNC_L3____________________,              ________________FUNC_R2____________________, _______,
    _______, ________________FUNC_L3____________________,              ________________FUNC_R3____________________, _______,
                                     _______, _______, _______,  _______, _______, _______
  ),

  [_SYMBOL] = LAYOUT_wrapper(
    _______, ________________SYMBOL_L1__________________,              ________________SYMBOL_R1__________________, _______,
    _______, ________________SYMBOL_L2__________________,              ________________SYMBOL_R2__________________, _______,
    _______, ________________SYMBOL_L3__________________,              ________________SYMBOL_R3__________________, _______,
                                     _______, KC_EQL,  KC_BSLS,  _______, _______, _______
  ),

  [_REGEX] = LAYOUT_wrapper(
    _______, ________________REGEX_L1___________________,              ________________REGEX_R1___________________, _______,
    _______, ________________REGEX_L2___________________,              ________________REGEX_R2___________________, _______,
    _______, ________________REGEX_L3___________________,              ________________REGEX_R3___________________, _______,
                                     _______, _______, _______,  _______, KC_BSLS, KC_DEL
  ),

  [_SYSTEM] = LAYOUT_wrapper( \
    RESET,   ________________SYSTEM_L1__________________,              ________________SYSTEM_R1__________________, RESET,
    VRSN,    ________________SYSTEM_L2__________________,              ________________SYSTEM_R2__________________, EEP_RST,
    _______, ________________SYSTEM_L3__________________,              ________________SYSTEM_R3__________________, KC_MPLY,
                                     _______, _______, _______,  _______, _______, _______
  ),

  [_MOUSE] = LAYOUT_wrapper( \
    RESET,   ________________MOUSE_L1___________________,              ________________MOUSE_R1___________________, RESET,
    VRSN,    ________________MOUSE_L2___________________,              ________________MOUSE_R2___________________, EEP_RST,
    _______, ________________MOUSE_L3___________________,              ________________MOUSE_R3___________________, KC_MPLY,
                                     _______, _______, _______,  _______, _______, _______
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case VRSN: // Prints firmware version
        if (record->event.pressed) {
            send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), 5);
        }
        break;
  }
  return true;
}
