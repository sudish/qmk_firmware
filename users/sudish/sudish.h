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
  _NUMBER_L,
  _NUMBER_R,
  _SYMBOL_L,
  _SYMBOL_R,
  _SYSTEM,
  _GAME,
  _GAMENAV,
  _GAMENF,
  _ADJUST,      // Highest layer so it gets priority
  _N_LAYERS
};


#ifdef TAP_DANCE_ENABLE
enum {
  TD_M_SYS = 0,
};

#define TD_MSYS TD(TD_M_SYS)
#endif // TAP_DANCE_ENABLE


// Modifier/layer macros to ease using MT(), LT() and similar across multiple keyboards and keymaps.

// Home row
#define HROW_L(K1, K2, K3, K4, K5)           LSFT_T(K1), LT(_SYSTEM,K2), LT(_SYMBOL_R,K3), LT(_NUMBER_R,K4), K5
#define HROW_R(K1, K2, K3, K4, K5)           K1, LT(_NUMBER_L,K2), LT(_SYMBOL_L,K3), LT(_SYSTEM,K4), RSFT_T(K5)
// Bottom row
#define BROW(K1, K2, K3, K4, K5, K6)         LGUI_T(K1), LCTL_T(K2), LALT_T(K3), RALT_T(K4), RCTL_T(K5), RGUI_T(K6)
#define BROW_L3(K1, K2, K3)                  LGUI_T(K1), LCTL_T(K2), LALT_T(K3)
#define BROW_R3(K4, K5, K6)                  RALT_T(K4), RCTL_T(K5), RGUI_T(K6)

// Layer on/off toggle/switch
#define TG_SYS  TG(_SYSTEM)
#define TG_ADJS TG(_ADJUST)

#define TO_DEFL TO(_QWERTY)
#define TO_GAME TO(_GAME)
#define TO_GMNV TO(_GAMENAV)

/*
Blocks for each of the layers we use.
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
*/

#define ___________________KC_NO___________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________PASS____________________              _______, _______, _______, _______, _______
#define          _________PASS_B3_________                       _______, _______, _______
#define __________________PASS_B6__________________              _______, _______, _______, _______, _______, _______
#define _______________HROW_L_NO___________________       HROW_L(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define _______________HROW_R_NO___________________       HROW_R(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)


#define _________________QWERTY_LNUM_______________              KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________QWERTY_L1_________________              KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       HROW_L(KC_A,    KC_S,    KC_D,    KC_F,    KC_G)
#define _________________QWERTY_L3_________________              KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_RNUM_______________              KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________QWERTY_R1_________________              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       HROW_R(KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN)
#define _________________QWERTY_R3_________________              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________QWERTY_B6_________________         BROW(KC_ESC,   KC_BSPC, KC_TAB,  KC_ENT,  KC_SPC,  KC_QUOT)
#define          ________QWERTY_B3_R______               BROW_R3(KC_ENT,   KC_SPC,  KC_QUOT)
#define          ________QWERTY_B3_L______               BROW_L3(KC_ESC,   KC_BSPC, KC_TAB)


#define ________________NUMBER_L1__________________              KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ________________NUMBER_L2__________________              KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_L3__________________              KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO

#define ________________NUMBER_R1__________________              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define ________________NUMBER_R2__________________              KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define ________________NUMBER_R3__________________              KC_NO,   KC_NO,   KC_NO,   KC_F11,  KC_F12

#define ________________NUMBER_B6__________________              __________________PASS_B6__________________


#define ________________SYMBOL_L1__________________              KC_NO,   KC_QUOT, KC_GRV,  KC_BSLS, KC_NO
#define ________________SYMBOL_L2__________________              KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define ________________SYMBOL_L3__________________              KC_NO,   KC_DQT,  KC_TILD, KC_PIPE, KC_NO

#define ________________SYMBOL_R1__________________              KC_NO,   KC_EQL,  KC_MINS, KC_LBRC, KC_RBRC
#define ________________SYMBOL_R2__________________              KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define ________________SYMBOL_R3__________________              KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR

#define ________________SYMBOL_B6__________________              __________________PASS_B6__________________


#define ________________SYSTEM_L1__________________              KC_BRIU, KC_VOLU, KC_MUTE, KC_MNXT, KC_NO
#define ________________SYSTEM_L2__________________              KC_BRID, KC_VOLD, KC_MPLY, KC_MPRV, KC_NO
#define ________________SYSTEM_L3__________________              TG_ADJS, KC_PSCR, KC_PAUS, KC_SLCK, TO_DEFL

#define ________________SYSTEM_R1__________________              KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS
#define ________________SYSTEM_R2__________________              KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL
#define ________________SYSTEM_R3__________________              TG_ADJS, KC_NO,   KC_NO,   KC_NO,   TO_DEFL

#define ________________SYSTEM_B6__________________              __________________PASS_B6__________________


#define ________________ADJUST_L1__________________              RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define ________________ADJUST_L2__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________ADJUST_L3__________________              RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, KC_NO

#define ________________ADJUST_R1__________________              TO_GAME, TO_GMNV, KC_NO,   KC_NO,   RESET
#define ________________ADJUST_R2__________________              TO_DEFL, KC_NO,   KC_NO,   KC_NO,   EEP_RST
#define ________________ADJUST_R3__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   SHKEYS

#define ________________ADJUST_B6__________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO_DEFL


/*
Special gaming layouts, these have no relation to normal layouts
*/

#define ARROWS1(K1, K2, K3, K4, K5)           K1, K2,      KC_UP,   K4,      K5
#define ARROWS2(K1, K2, K3, K4, K5)           K1, KC_LEFT, KC_DOWN, KC_RGHT, K5

// Base left rotates QWERT by one column so we don't have to remap WASD to ESDF
#define _________________GAME_L1___________________              KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R
#define _________________GAME_L2___________________              KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F
#define _________________GAME_L3___________________              KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V

#define _________________GAME_R1___________________              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________GAME_R2___________________              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________GAME_R3___________________              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

// Nav keys
#define ________________GAMENAV_R1_________________      ARROWS1(KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R)
#define ________________GAMENAV_R2_________________      ARROWS2(KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F)
#define ________________GAMENAV_R3_________________              KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V

// A number and function key layer for one handed left half
#define ________________GAMENF_L1__________________              KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ________________GAMENF_L2__________________       LSFT_T(KC_1),   KC_2,    KC_3,    KC_4,    KC_5
#define ________________GAMENF_L3__________________       LCTL_T(KC_NO),  KC_6,    KC_7,    KC_F6,   KC_F7

#define _________________GAME_B6___________________      LM(_GAMENF,MOD_LSFT), KC_SPC, MO(_GAMENF),  KC_ENT,  KC_SPC,  TO_DEFL


extern const char *get_layer_name(uint8_t layer);
#ifdef RGB_MATRIX_ENABLE
extern void set_layer_rgb_indicator_keymap(uint8_t r, uint8_t g, uint8_t b);
extern void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
#endif // RGB_MATRIX_ENABLE

#if 0
// Original Numpad / Regexp / Symbol / Func setup
#define ________________NUMBER_L1__________________              KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F12
#define ________________NUMBER_L2__________________       HROW_L(KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_F11)
#define ________________NUMBER_L3__________________              KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F10

#define ________________NUMBER_R1__________________              KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR
#define ________________NUMBER_R2__________________       HROW_R(KC_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS)
#define ________________NUMBER_R3__________________              KC_COMM, KC_1,    KC_2,    KC_3,    KC_PLUS

#define ________________NUMBER_B6__________________              _______, _______, _______, KC_EQL,  KC_0,    _______


#define ________________SYMBOL_L1__________________              KC_EQL,  KC_DOT,  KC_ASTR, KC_AMPR, KC_GRV
#define ________________SYMBOL_L2__________________              KC_EXLM, KC_UNDS, KC_PERC, KC_MINS, KC_TILD
#define ________________SYMBOL_L3__________________              KC_NO,   KC_PLUS, KC_AT,   KC_SLSH, KC_PIPE

#define ________________SYMBOL_R1__________________              KC_PIPE, KC_LBRC, KC_CIRC, KC_RBRC, KC_PLUS
#define ________________SYMBOL_R2__________________              KC_DOT,  KC_LPRN, KC_DLR,  KC_RPRN, KC_EQL
#define ________________SYMBOL_R3__________________              KC_ASTR, KC_LCBR, KC_HASH, KC_RCBR, KC_BSLS

#define ________________SYMBOL_B6__________________              _______, KC_DEL,  _______, _______, _______, _______
#endif
