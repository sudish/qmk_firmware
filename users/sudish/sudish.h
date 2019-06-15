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

/* All of the below taken from @drashna's wrappers.h */

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#   define LAYOUT KEYMAP
#endif

#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)

/*
Modifier/layer macros to ease using MT(), LT() and similar across multiple keyboards and keymaps.
These macros assume they are being applied to a 5-key core row.
*/

// GUI, Ctl, Alt, Shift for the home row
#define GCAS_L(K1, K2, K3, K4, K5)           LGUI_T(K1), LCTL_T(K2), LALT_T(K3), LSFT_T(K4), K5
#define GCAS_R(K1, K2, K3, K4, K5)           K1, RSFT_T(K2), RALT_T(K3), RCTL_T(K4), RGUI_T(K5)


/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

#define _________________QWERTY_L1_________________              KC_Q,     KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       GCAS_L(KC_A,     KC_S,    KC_D,    KC_F,    KC_G)
#define _________________QWERTY_L3_________________              KC_Z,     KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________              KC_Y,     KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       GCAS_R(KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN)
#define _________________QWERTY_R3_________________              KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH


#define ___________________BLANK___________________              _______,  _______, _______, _______, _______


#define ________________NUMBER_L1__________________              KC_NO,    KC_D,    KC_E,    KC_F,    KC_NO
#define ________________NUMBER_L2__________________       GCAS_L(KC_NO,    KC_A,    KC_B,    KC_C,    KC_NO)
#define ________________NUMBER_L3__________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________NUMBER_R1__________________              KC_SLSH,   KC_7,    KC_8,   KC_9,    KC_ASTR
#define ________________NUMBER_R2__________________       GCAS_R(KC_DOT,    KC_4,    KC_5,   KC_6,    KC_MINS)
#define ________________NUMBER_R3__________________              KC_COMM,   KC_1,    KC_2,   KC_3,    KC_PLUS


#define ________________FUNC_L1____________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________FUNC_L2____________________       GCAS_L(KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define ________________FUNC_L3____________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________FUNC_R1____________________              KC_NO,    KC_F7,   KC_F8,   KC_F9,   KC_F12
#define ________________FUNC_R2____________________       GCAS_R(KC_NO,    KC_F4,   KC_F5,   KC_F6,   KC_F11)
#define ________________FUNC_R3____________________              KC_NO,    KC_F1,   KC_F2,   KC_F3,   KC_F10


#define ________________SYMBOL_L1__________________              KC_MINS,  KC_DOT,  KC_ASTR, KC_AMPR, KC_GRV
#define ________________SYMBOL_L2__________________       GCAS_L(KC_UNDS,  KC_LT,   KC_PERC, KC_GT,   KC_TILD)
#define ________________SYMBOL_L3__________________              KC_EXLM,  KC_PLUS, KC_AT,   KC_SLSH, KC_PIPE

#define ________________SYMBOL_R1__________________              KC_NO,    KC_HOME, KC_UP,   KC_END,  KC_PGUP
#define ________________SYMBOL_R2__________________       GCAS_R(KC_NO,    KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN)
#define ________________SYMBOL_R3__________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO


#define ________________REGEX_L1___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________REGEX_L2___________________       GCAS_L(KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define ________________REGEX_L3___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________REGEX_R1___________________              KC_ASTR,  KC_LBRC, KC_CIRC, KC_RBRC, KC_PLUS
#define ________________REGEX_R2___________________       GCAS_R(KC_QUES,  KC_LPRN, KC_DLR,  KC_RPRN, KC_DOT)
#define ________________REGEX_R3___________________              KC_PIPE,  KC_LCBR, KC_HASH, KC_RCBR, KC_MINS


#define ________________SYSTEM_L1__________________              RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define ________________SYSTEM_L2__________________              MU_TOG ,  CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define ________________SYSTEM_L3__________________              RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______

#define ________________SYSTEM_R1__________________              _______,  _______, _______, _______, _______
#define ________________SYSTEM_R2__________________              AG_SWAP,  _______, _______, _______, _______
#define ________________SYSTEM_R3__________________              _______,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT


#define ________________MOUSE_L1___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________MOUSE_L2___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________MOUSE_L3___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO

#define ________________MOUSE_R1___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________MOUSE_R2___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________MOUSE_R3___________________              KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO
