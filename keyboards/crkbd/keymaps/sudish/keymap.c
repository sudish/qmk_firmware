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

extern keymap_config_t keymap_config;
extern uint8_t is_master;
#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config; // allows macro to read current RGB settings
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
    RESET,   ________________SYSTEM_L1__________________,              ________________SYSTEM_R1__________________, RESET,
    VRSN,    ________________SYSTEM_L2__________________,              ________________SYSTEM_R2__________________, EEP_RST,
    TG_SYS,  ________________SYSTEM_L3__________________,              ________________SYSTEM_R3__________________, SHKEYS,
                                           ________________SYSTEM_B6__________________
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

  char *layer_name;
  switch (biton32(layer_state)) {
    case 0:
      layer_name = "Default";
      break;
    case _NUMBER:
      layer_name = "Number";
      break;
    case _FUNC:
      layer_name = "Function";
      break;
    case _SYMBOL:
      layer_name = "Symbol";
      break;
    case _REGEX:
      layer_name = "Regex";
      break;
    case _SYSTEM:
      layer_name = "System";
      break;
    default:
      layer_name = "Unknown";
      break;
  }
  snprintf(state_str, sizeof(state_str), "Layer: %-8.8s", layer_name);

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

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL << _QWERTY);
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
    case SHKEYS:
      if (record->event.pressed) {
        show_keylog = !show_keylog;
      }
      break;
    case VRSN:  // Prints firmware version
      if (record->event.pressed) {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), 5);
      }
      break;
  }

  return true;
}

#ifdef RGB_MATRIX_ENABLE
void set_layer_rgb_indicator_keymap(uint8_t red, uint8_t green, uint8_t  blue) {
    rgb_matrix_layer_helper(red, green, blue, LED_FLAG_UNDERGLOW);
}
#endif // RGB_MATRIX_ENABLE
