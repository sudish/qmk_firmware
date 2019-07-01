/*
Copyright 2019 Sudish Joseph <sudish@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Idea from @drashna's wrappers.h

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
  #define LAYOUT KEYMAP
#endif

#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)


// Common keycodes across all keyboards
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SHKEYS,
  VRSN
};

// Common layers
enum {
  _QWERTY = 0,
  _NUMBER,
  _FUNC,
  _SYMBOL,
  _REGEX,
  _SYSTEM,
  _GAME,
  _GAMENF,
  _GAMENAV,
  _ADJUST,      // Highest layer so it gets priority
  _N_LAYERS
};

// Tap dance
enum {
  TD_M_SYS = 0,
};


// Modifier/layer macros to ease using MT(), LT() and similar across multiple keyboards and keymaps.

// Home row
#define HROW_L(K1, K2, K3, K4, K5)           LSFT_T(K1), LT(_FUNC,K2), LT(_REGEX,K3), LT(_NUMBER,K4), K5
#define HROW_R(K1, K2, K3, K4, K5)           K1, LT(_SYSTEM,K2), LT(_SYMBOL,K3), K4, RSFT_T(K5)
// Bottom row
#define BROW(K1, K2, K3, K4, K5, K6)         LGUI_T(K1), LCTL_T(K2), LALT_T(K3), RALT_T(K4), RCTL_T(K5), RGUI_T(K6)


// Layer on/off toggle/switch
#define TG_NUM  TG(_NUMBER)
#define TG_FUNC TG(_FUNC)
#define TG_SYM  TG(_SYMBOL)
#define TG_REGX TG(_REGEX)
#define TG_SYS  TG(_SYSTEM)

#define TO_DEFL TO(_QWERTY)
#define TO_ADJS TO(_ADJUST)
#define TO_GAME TO(_GAME)
#define TO_GMNV TO(_GAMENAV)

// Tap dance
#define TD_MSYS TD(TD_M_SYS)

/*
Blocks for each of the layers we use.
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
*/

#define ___________________BLANK___________________              _______, _______, _______, _______, _______
#define ___________________KC_NO___________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO


#define _________________QWERTY_L1_________________              KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       HROW_L(KC_A,    KC_S,    KC_D,    KC_F,    KC_G)
#define _________________QWERTY_L3_________________              KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       HROW_R(KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN)
#define _________________QWERTY_R3_________________              KC_N,    TD_MSYS, KC_COMM, KC_DOT,  KC_SLSH

#define _________________QWERTY_B6_________________        BROW(KC_ESC,   KC_BSPC, KC_TAB,  KC_ENT,  KC_SPC,  KC_QUOT)


#define ________________NUMBER_L1__________________              KC_NO,   KC_D,    KC_E,    KC_F,    KC_NO
#define ________________NUMBER_L2__________________       HROW_L(KC_NO,   KC_A,    KC_B,    KC_C,    KC_NO)
#define ________________NUMBER_L3__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________NUMBER_R1__________________              KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR
#define ________________NUMBER_R2__________________       HROW_R(KC_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS)
#define ________________NUMBER_R3__________________              KC_COMM, KC_1,    KC_2,    KC_3,    KC_PLUS

#define ________________NUMBER_B6__________________              _______, _______, _______, KC_EQL,  KC_0,    _______


#define ________________FUNC_L1____________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________FUNC_L2____________________       HROW_L(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define ________________FUNC_L3____________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________FUNC_R1____________________              KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F12
#define ________________FUNC_R2____________________       HROW_R(KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_F11)
#define ________________FUNC_R3____________________              KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F10

#define ________________FUNC_B6____________________              _______, _______, _______, _______, _______, _______


#define ________________SYMBOL_L1__________________              KC_EQL,  KC_DOT,  KC_ASTR, KC_AMPR, KC_GRV
#define ________________SYMBOL_L2__________________              KC_EXLM, KC_UNDS, KC_PERC, KC_MINS, KC_TILD
#define ________________SYMBOL_L3__________________              KC_NO,   KC_PLUS, KC_AT,   KC_SLSH, KC_PIPE

#define ________________SYMBOL_R1__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________SYMBOL_R2__________________       HROW_R(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define ________________SYMBOL_R3__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________SYMBOL_B6__________________              _______, KC_DEL,  _______, _______, _______, _______


#define ________________REGEX_L1___________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________REGEX_L2___________________       HROW_L(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define ________________REGEX_L3___________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________REGEX_R1___________________              KC_PIPE, KC_LBRC, KC_CIRC, KC_RBRC, KC_PLUS
#define ________________REGEX_R2___________________              KC_DOT,  KC_LPRN, KC_DLR,  KC_RPRN, KC_EQL
#define ________________REGEX_R3___________________              KC_ASTR, KC_LCBR, KC_HASH, KC_RCBR, KC_BSLS

#define ________________REGEX_B6___________________              _______, _______, _______, _______, _______, _______


#define ________________SYSTEM_L1__________________              KC_BRIU, KC_HOME, KC_UP,   KC_END,  KC_PGUP
#define ________________SYSTEM_L2__________________       HROW_L(KC_BRID, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN)
#define ________________SYSTEM_L3__________________              KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT

#define ________________SYSTEM_R1__________________              RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define ________________SYSTEM_R2__________________       HROW_R(KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO)
#define ________________SYSTEM_R3__________________              RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, KC_NO

#define ________________SYSTEM_B6__________________              TO_DEFL, _______, _______, _______, _______, TO_ADJS

#define ________________ADJUST_L1__________________              TO_GAME, TO_GMNV, KC_NO,   KC_NO,   KC_NO
#define ________________ADJUST_L2__________________              TO_DEFL, KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________ADJUST_L3__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________ADJUST_R1__________________              RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define ________________ADJUST_R2__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________ADJUST_R3__________________              RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, KC_NO

#define ________________ADJUST_B6__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
/*
Special gaming layouts, these have no relation to normal layouts
*/

// Base left rotates QWERT by one column so we don't have to remap WASD to ESDF
#define _6_KEY____________________GAME_L1___________________              KC_T,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R
#define _6_KEY____________________GAME_L2___________________       LSFT_T(KC_G),   KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F
#define _6_KEY____________________GAME_L3___________________       LCTL_T(KC_B),   KC_RCTL, KC_Z,    KC_X,    KC_C,    KC_V

#define _________________GAME_R1___________________              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________GAME_R2___________________              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________GAME_R3___________________              KC_N,    TD_MSYS, KC_COMM, KC_DOT,  KC_SLSH

// A number and function key layer for one handed left half
#define ________________GAMENF_L1__________________              KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ________________GAMENF_L2__________________              KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________GAMENF_L3__________________       LCTL_T(KC_NO),  KC_6,    KC_7,    KC_F6,   KC_F7

// Nav keys
#define ________________GAMENAV_1__________________              KC_BRIU, KC_HOME, KC_UP,   KC_END,  KC_PGUP
#define ________________GAMENAV_2__________________              KC_BRID, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define ________________GAMENAV_3__________________              KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT

#define _________________GAME_B6___________________      LM(_GAMENF,MOD_LSFT), KC_SPC, MO(_GAMENF),  KC_ENT,  KC_SPC,  KC_ESC


extern const char *get_layer_name(uint8_t layer);
extern void set_layer_rgb_indicator_keymap(uint8_t r, uint8_t g, uint8_t b);
extern void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
