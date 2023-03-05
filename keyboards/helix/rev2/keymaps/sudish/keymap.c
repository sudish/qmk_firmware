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

  [_QWERTY] = LAYOUT_wrapper( \
      KC_EQL,  _________________QWERTY_LNUM_______________,                   _________________QWERTY_RNUM_______________, KC_MINS, \
      KC_GRV,  _________________QWERTY_L1_________________,                   _________________QWERTY_R1_________________, KC_BSLS, \
      KC_CAPS, _________________QWERTY_L2_________________,                   _________________QWERTY_R2_________________, KC_QUOT, \
      KC_LGUI, _________________QWERTY_L3_________________, TG_SYS,   TG_SYS, _________________QWERTY_R3_________________, KC_RGUI, \
      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, ________QWERTY_B3_L______, ________QWERTY_B3_R______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
      ),

  [_NUMBER_L] = LAYOUT_wrapper( \
      _______, ________________NUMBER_L1__________________,                   ___________________KC_NO___________________, _______, \
      _______, ________________NUMBER_L1__________________,                   ___________________KC_NO___________________, _______, \
      _______, ________________NUMBER_L2__________________,                   _______________HROW_R_NO___________________, _______, \
      _______, ________________NUMBER_L3__________________, _______, _______, ___________________KC_NO___________________, _______, \
      _______, _______, _______, _______, _________PASS_B3_________, _________PASS_B3_________, _______, _______, _______, _______  \
      ),

  [_NUMBER_R] = LAYOUT_wrapper( \
      _______, ___________________KC_NO___________________,                   ________________NUMBER_R1__________________, _______, \
      _______, ___________________KC_NO___________________,                   ________________NUMBER_R1__________________, _______, \
      _______, _______________HROW_L_NO___________________,                   ________________NUMBER_R2__________________, _______, \
      _______, ___________________KC_NO___________________, _______, _______, ________________NUMBER_R3__________________, _______, \
      _______, _______, _______, _______, _________PASS_B3_________, _________PASS_B3_________, _______, _______, _______, _______  \
      ),

  [_SYMBOL_L] = LAYOUT_wrapper( \
      _______, ___________________PASS____________________,                   ___________________PASS____________________, _______, \
      _______, ________________SYMBOL_L1__________________,                   ___________________KC_NO___________________, _______, \
      _______, ________________SYMBOL_L2__________________,                   _______________HROW_R_NO___________________, _______, \
      _______, ________________SYMBOL_L3__________________, _______, _______, ___________________KC_NO___________________, _______, \
      _______, _______, _______, _______, _________PASS_B3_________, _________PASS_B3_________, _______, _______, _______, _______  \
      ),

  [_SYMBOL_R] = LAYOUT_wrapper( \
      _______, ___________________PASS____________________,                   ___________________PASS____________________, _______, \
      _______, ___________________KC_NO___________________,                   ________________SYMBOL_R1__________________, _______, \
      _______, _______________HROW_L_NO___________________,                   ________________SYMBOL_R2__________________, _______, \
      _______, ___________________KC_NO___________________, _______, _______, ________________SYMBOL_R3__________________, _______, \
      _______, _______, _______, _______, _________PASS_B3_________, _________PASS_B3_________, _______, _______, _______, _______  \
      ),

  [_SYSTEM] = LAYOUT_wrapper( \
      QK_BOOT, ___________________PASS____________________,                   ___________________PASS____________________, TG_ADJS, \
      EE_CLR,  ________________SYSTEM_L1__________________,                   ________________SYSTEM_R1__________________, EE_CLR,  \
      VRSN,    ________________SYSTEM_L2__________________,                   ________________SYSTEM_R2__________________, _______, \
      _______, ________________SYSTEM_L3__________________, TG_SYS,  TG_SYS,  ________________SYSTEM_R3__________________, _______, \
      _______, _______, _______, _______, _________PASS_B3_________, _________PASS_B3_________, _______, _______, _______, SHKEYS   \
      )

};


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case QWERTY:
      persistent_default_layer_set(1UL << _QWERTY);
      return false;
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
