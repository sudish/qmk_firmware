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

extern uint8_t is_master;

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif


// Define our keymap using the common sections defined elsewhere.
// Only the keys specific to this board are specified here.
#include "sudish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    TG_REGX, _________________QWERTY_L1_________________,              _________________QWERTY_R1_________________, TG_SYM,
    KC_CAPS, _________________QWERTY_L2_________________,              _________________QWERTY_R2_________________, TG_NUM,
    TG_SYS,  _________________QWERTY_L3_________________,              _________________QWERTY_R3_________________, TG_FUNC,
                                           _________________QWERTY_B6_________________
  ),

  [_NUMBER] = LAYOUT_wrapper(
    _______, ________________NUMBER_L1__________________,              ________________NUMBER_R1__________________, _______,
    _______, ________________NUMBER_L2__________________,              ________________NUMBER_R2__________________, _______,
    _______, ________________NUMBER_L3__________________,              ________________NUMBER_R3__________________, _______,
                                           ________________NUMBER_B6__________________
  ),

  [_FUNC] = LAYOUT_wrapper( \
    _______, ________________FUNC_L1____________________,              ________________FUNC_R1____________________, _______,
    _______, ________________FUNC_L3____________________,              ________________FUNC_R2____________________, _______,
    _______, ________________FUNC_L3____________________,              ________________FUNC_R3____________________, _______,
                                           ________________FUNC_B6____________________
  ),

  [_SYMBOL] = LAYOUT_wrapper(
    _______, ________________SYMBOL_L1__________________,              ________________SYMBOL_R1__________________, _______,
    _______, ________________SYMBOL_L2__________________,              ________________SYMBOL_R2__________________, _______,
    _______, ________________SYMBOL_L3__________________,              ________________SYMBOL_R3__________________, _______,
                                           ________________SYMBOL_B6__________________
  ),

  [_REGEX] = LAYOUT_wrapper(
    _______, ________________REGEX_L1___________________,              ________________REGEX_R1___________________, _______,
    _______, ________________REGEX_L2___________________,              ________________REGEX_R2___________________, _______,
    _______, ________________REGEX_L3___________________,              ________________REGEX_R3___________________, _______,
                                           ________________REGEX_B6___________________
  ),

  [_SYSTEM] = LAYOUT_wrapper( \
    RESET,   ________________SYSTEM_L1__________________,              ________________SYSTEM_R1__________________, TO_ADJS,
    VRSN,    ________________SYSTEM_L2__________________,              ________________SYSTEM_R2__________________, EEP_RST,
    TG_SYS,  ________________SYSTEM_L3__________________,              ________________SYSTEM_R3__________________, SHKEYS,
                                           ________________SYSTEM_B6__________________
  ),

  [_GAME] = LAYOUT_wrapper( \
    _6_KEY____________________GAME_L1___________________,              _________________GAME_R1___________________, TO_ADJS,
    _6_KEY____________________GAME_L2___________________,              _________________GAME_R2___________________, KC_NO,
    _6_KEY____________________GAME_L3___________________,              _________________GAME_R3___________________, TO_DEFL,
                                           _________________GAME_B6___________________
  ),

  [_GAMENF] = LAYOUT_wrapper( \
    KC_TAB,  ________________GAMENF_L1__________________,              _________________GAME_R1___________________, TO_ADJS,
    KC_LSFT, ________________GAMENF_L2__________________,              _________________GAME_R2___________________, KC_NO,
    KC_RCTL, ________________GAMENF_L3__________________,              _________________GAME_R3___________________, TO_DEFL,
                                           _________________GAME_B6___________________
  ),

  [_GAMENAV] = LAYOUT_wrapper( \
    KC_TAB,  ________________GAMENAV_1__________________,              ________________GAMENAV_1__________________, TO_ADJS,
    KC_LSFT, ________________GAMENAV_2__________________,              ________________GAMENAV_2__________________, KC_NO,
    KC_RCTL, ________________GAMENAV_3__________________,              ________________GAMENAV_3__________________, TO_DEFL,
                                           _________________GAME_B6___________________
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    RESET,   ________________ADJUST_L1__________________,              ________________ADJUST_R1__________________, RESET,
    VRSN,    ________________ADJUST_L2__________________,              ________________ADJUST_R2__________________, EEP_RST,
    TO_DEFL, ________________ADJUST_L3__________________,              ________________ADJUST_R3__________________, TO_DEFL,
                                           ________________ADJUST_B6__________________
  ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
  iota_gfx_init(!has_usb());  // turns on the display
#endif
}

#ifdef SSD1306OLED
static bool show_keylog = false;
static char keylog_str[24] = {};
static char keylogs_str[21] = {};

static const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '
};

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
  static uint8_t keylogs_str_idx = 0;
  uint16_t basekey = ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
                      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX))
              ? keycode & 0xFF : keycode;
  char name = (basekey < 60) ? code_to_name[basekey] : ' ';

  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d, k%2d: %c",
           record->event.key.row, record->event.key.col,
           keycode, basekey != keycode ? basekey : 0, name);

  if (keylogs_str_idx == sizeof(keylogs_str) - 2) {
    keylogs_str_idx = 0;
  }

  keylogs_str[keylogs_str_idx++] = name;
  keylogs_str[keylogs_str_idx] = ' ';
}

static const char *read_logo(void) {
  static char logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};

  return logo;
}

static const char *get_layer_state(void) {
  static char state_str[25];

  const char *layer_name = get_layer_name(biton32(layer_state));
  snprintf(state_str, sizeof(state_str), "Layer: %-10.10s", layer_name);

  return state_str;
}

static const char *get_mod_state(void) {
  static char state_str[25];

  uint8_t modifiers = get_mods();
  uint8_t one_shot  = get_oneshot_mods();
  snprintf(state_str, sizeof(state_str), "Mod: %-3.3s %-3.3s %-3.3s %-3.3s",
           (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? "SFT" : "",
           (modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT)   ? "ALT" : "",
           (modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL)  ? "CTL" : "",
           (modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI)   ? "GUI" : "");

  return state_str;
}

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // OLED display has 3 lines of 21 characters each
    matrix_write_ln(matrix, get_layer_state());
    if (!show_keylog) {
      matrix_write_ln(matrix, get_mod_state());
    } else {
      matrix_write_ln(matrix, keylog_str);
      matrix_write_ln(matrix, keylogs_str);
    }
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
#endif // SSD1306OLED


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef SSD1306OLED
  if (show_keylog && record->event.pressed) {
    set_keylog(keycode, record);
  }
#endif

  if (record->event.pressed) {
    switch (keycode) {
    case QWERTY:
      persistent_default_layer_set(1UL << _QWERTY);
      return false;
    case SHKEYS:
      show_keylog = !show_keylog;
      return false;
    case VRSN:
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), 5);
      return false;
#ifdef RGB_MATRIX_ENABLE
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:    // from quantum_keycodes.h
      if (rgb_matrix_config.mode == RGB_LAYER_INDICATOR_MODE) {
        layer_state_set_user(layer_state);          // run the RGB layer hook right away
      }
      else {
        set_layer_rgb_indicator_keymap(0, 0, 0);    // blank the layer LEDs
      }
      break;                                        // must allow keycode to be processed
#endif // RGB_MATRIX_ENABLE
    }
  }

  return true;
}

#ifdef RGB_MATRIX_ENABLE
void set_layer_rgb_indicator_keymap(uint8_t red, uint8_t green, uint8_t  blue) {
    rgb_matrix_layer_helper(red, green, blue, LED_FLAG_UNDERGLOW);
}
#endif // RGB_MATRIX_ENABLE
