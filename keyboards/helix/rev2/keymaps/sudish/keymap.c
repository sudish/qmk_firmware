#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "version.h"
#include "sudish.h"

extern uint8_t is_master;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [U_BASE] = LAYOUT_wrapper( \
      KC_EQL,  ___________________BASE_LNUM_______________,                   ___________________BASE_RNUM_______________, KC_MINS, \
      KC_GRV,  ___________________BASE_L1_________________,                   ___________________BASE_R1_________________, KC_BSLS, \
      KC_CAPS, ___________________BASE_L2_________________,                   ___________________BASE_R2_________________, KC_QUOT, \
      U_NA,    ___________________BASE_L3_________________, U_NA,       U_NA, ___________________BASE_R3_________________, U_NA,    \
      QK_BOOT, KC_DOWN, KC_UP,   KC_RGHT,     ___________________BASE_B6_________________,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
      ),

  [U_TAP] = LAYOUT_wrapper( \
      _______, ___________________TAP_LNUM________________,                   ___________________TAP_LNUM________________, _______, \
      _______, ___________________TAP_L1__________________,                   ___________________TAP_R1__________________, _______, \
      _______, ___________________TAP_L2__________________,                   ___________________TAP_R2__________________, _______, \
      _______, ___________________TAP_L3__________________, _______, _______, ___________________TAP_R3__________________, _______, \
      _______, _______, _______, _______,     ___________________TAP_B6__________________,      _______, _______, _______, _______  \
      ),

  [U_NAV] = LAYOUT_wrapper( \
      _______, ___________________KC_NO___________________,                   ___________________KC_NO___________________, _______, \
      _______, ___________________NAV_L1__________________,                   ___________________NAV_R1__________________, _______, \
      _______, ___________________NAV_L2__________________,                   ___________________NAV_R2__________________, _______, \
      _______, ___________________NAV_L3__________________, _______, _______, ___________________NAV_R3__________________, _______, \
      _______, _______, _______, _______,     ___________________NAV_B6__________________,      _______, _______, _______, _______  \
      ),

  [U_MOUSE] = LAYOUT_wrapper( \
      QK_BOOT, ___________________KC_NO___________________,                   ___________________KC_NO___________________, VRSN,    \
      _______, _________________MOUSE_L1__________________,                   _________________MOUSE_R1__________________, _______, \
      _______, _________________MOUSE_L2__________________,                   _________________MOUSE_R2__________________, _______, \
      _______, _________________MOUSE_L3__________________, _______, _______, _________________MOUSE_R3__________________, _______, \
      _______, _______, _______, _______,     _________________MOUSE_B6__________________,      _______, _______, _______, _______  \
      ),

  [U_MEDIA] = LAYOUT_wrapper( \
      QK_BOOT, ___________________KC_NO___________________,                   ___________________KC_NO___________________, VRSN,    \
      _______, _________________MEDIA_L1__________________,                   _________________MEDIA_R1__________________, _______, \
      _______, _________________MEDIA_L2__________________,                   _________________MEDIA_R2__________________, _______, \
      _______, _________________MEDIA_L3__________________, _______, _______, _________________MEDIA_R3__________________, _______, \
      _______, _______, _______, _______,     _________________MEDIA_B6__________________,      _______, _______, _______, _______  \
      ),

  [U_NUM] = LAYOUT_wrapper( \
      QK_BOOT, ___________________KC_NO___________________,                   ___________________KC_NO___________________, VRSN,    \
      _______, ___________________NUM_L1__________________,                   ___________________NUM_R1__________________, _______, \
      _______, ___________________NUM_L2__________________,                   ___________________NUM_R2__________________, _______, \
      _______, ___________________NUM_L3__________________, _______, _______, ___________________NUM_R3__________________, _______, \
      _______, _______, _______, _______,     ___________________NUM_B6__________________,      _______, _______, _______, _______  \
      ),

  [U_SYM] = LAYOUT_wrapper( \
      QK_BOOT, ___________________KC_NO___________________,                   ___________________KC_NO___________________, VRSN,    \
      _______, ___________________SYM_L1__________________,                   ___________________SYM_R1__________________, _______, \
      _______, ___________________SYM_L2__________________,                   ___________________SYM_R2__________________, _______, \
      _______, ___________________SYM_L3__________________, _______, _______, ___________________SYM_R3__________________, _______, \
      _______, _______, _______, _______,     ___________________SYM_B6__________________,      _______, _______, _______, _______  \
      ),

  [U_FUN] = LAYOUT_wrapper( \
      QK_BOOT, ___________________KC_NO___________________,                   ___________________KC_NO___________________, VRSN,    \
      _______, ___________________FUN_L1__________________,                   ___________________FUN_R1__________________, _______, \
      _______, ___________________FUN_L2__________________,                   ___________________FUN_R2__________________, _______, \
      _______, ___________________FUN_L3__________________, _______, _______, ___________________FUN_R3__________________, _______, \
      _______, _______, _______, _______,     ___________________FUN_B6__________________,      _______, _______, _______, _______  \
      )
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case VRSN:
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), 5);
      return false;
    }
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE
void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}
#endif // AUSIO_ENABLE


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

static void render_logo(struct CharacterMatrix *matrix) {
  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
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

void render_status(struct CharacterMatrix *matrix) {
    matrix_write(matrix, get_layer_state());
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, get_mod_state());
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  if (is_master) {
    render_status(&matrix);
  } else {
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}
#endif // SSD1306OLED
