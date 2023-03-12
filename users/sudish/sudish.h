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


/* Since our block definitions are basically a list of comma separated
   arguments, we need a wrapper in order for these definitions to be
   expanded before being used as arguments to the LAYOUT_xxx macro. */
#if (!defined(LAYOUT) && defined(KEYMAP))
  #define LAYOUT KEYMAP
#endif

#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)


#if !defined (MIRYOKU_LAYER_LIST)

#define MIRYOKU_LAYER_LIST \
MIRYOKU_X(BASE,   "Base") \
MIRYOKU_X(EXTRA,  "Extra") \
MIRYOKU_X(TAP,    "Tap") \
MIRYOKU_X(BUTTON, "Button") \
MIRYOKU_X(NAV,    "Nav") \
MIRYOKU_X(MOUSE,  "Mouse") \
MIRYOKU_X(MEDIA,  "Media") \
MIRYOKU_X(NUM,    "Num") \
MIRYOKU_X(SYM,    "Sym") \
MIRYOKU_X(FUN,    "Fun")

#endif

// Layers
enum miryoku_layers {
#define MIRYOKU_X(LAYER, STRING) U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
  N_LAYERS  // Total number of layers
};

// tap dances
enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

#define TG_TAP TG(U_TAP)

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// Modifier/layer macros to ease using MT(), LT() and similar across multiple keyboards and keymaps.

// Home row
#define HROW_L(K1, K2, K3, K4, K5)           LSFT_T(K1), LCTL_T(K2), LALT_T(K3), LGUI_T(K4), K5
#define HROW_R(K1, K2, K3, K4, K5)           K1, RGUI_T(K2), RALT_T(K3), RCTL_T(K4), RSFT_T(K5)
// Bottom row
#define BROW(K1, K2, K3, K4, K5, K6)         LT(U_MEDIA, K1), LT(U_NAV, K2), LT(U_MOUSE, K3), LT(U_SYM, K4), LT(U_NUM, K5), LT(U_FUN, K6)
#define BROW_L3(K1, K2, K3)                  LT(U_MEDIA, K1), LT(U_NAV, K2), LT(U_MOUSE, K3)
#define BROW_R3(K4, K5, K6)                  LT(U_SYM, K4), LT(U_NUM, K5), LT(U_FUN, K6)

// Blocks for main 3x5 rows and bottom row.
#define ___________________KC_NO___________________              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ___________________PASS____________________              _______, _______, _______, _______, _______
#define          _________PASS_B3_________                       _______, _______, _______
#define __________________PASS_B6__________________              _______, _______, _______, _______, _______, _______
#define _______________HROW_L_NO___________________       HROW_L(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)
#define _______________HROW_R_NO___________________       HROW_R(KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO)

// MIRYOKU_ALTERNATIVES_TAP_QWERTY
#define ___________________TAP_LNUM________________              KC_1,              KC_2,              KC_3,              KC_4,              KC_5
#define ___________________TAP_L1__________________              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T
#define ___________________TAP_L2__________________              KC_A,              KC_S,              KC_D,              KC_F,              KC_G
#define ___________________TAP_L3__________________              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B

#define ___________________TAP_RNUM________________              KC_6,              KC_7,              KC_8,              KC_9,              KC_0
#define ___________________TAP_R1__________________              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P
#define ___________________TAP_R2__________________              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT
#define ___________________TAP_R3__________________              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH

#define ___________________TAP_B6__________________              KC_DEL,            KC_BSPC,           KC_TAB,            KC_ENT,            KC_SPC,            KC_ESC


// MIRYOKU_ALTERNATIVES_TAP_QWERTY 
#define ___________________BASE_LNUM_______________              KC_1,              KC_2,              KC_3,              KC_4,              KC_5
#define ___________________BASE_L1_________________              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T
#define ___________________BASE_L2_________________       HROW_L(KC_A,              KC_S,              KC_D,              KC_F,              KC_G)
#define ___________________BASE_L3_________________              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B

#define ___________________BASE_RNUM_______________              KC_6,              KC_7,              KC_8,              KC_9,              KC_0
#define ___________________BASE_R1_________________              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P
#define ___________________BASE_R2_________________       HROW_R(KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT)
#define ___________________BASE_R3_________________              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH

#define ___________________BASE_B6_________________         BROW(KC_DEL,            KC_BSPC,           KC_TAB,            KC_ENT,            KC_SPC,            KC_ESC)
#define          __________BASE_B3_L______               BROW_L3(KC_DEL,            KC_BSPC,           KC_TAB)
#define          __________BASE_B3_R______               BROW_R3(KC_ENT,            KC_SPC,            KC_ESC)

// Same hand bindings for layers
#define __________________SAME_L1__________________              TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA
#define __________________SAME_L2__________________              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA
#define __________________SAME_L3__________________              U_NA,              KC_ALGR,           TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    U_NA

#define __________________SAME_R1__________________              U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT)
#define __________________SAME_R2__________________              U_NA,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT
#define __________________SAME_R3__________________              U_NA,              TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    KC_ALGR,           U_NA

// MIRYOKU_ALTERNATIVES_NUM
#define ___________________NUM_L1__________________              KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC
#define ___________________NUM_L2__________________              KC_SCLN,           KC_4,              KC_5,              KC_6,              KC_EQL
#define ___________________NUM_L3__________________              KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS

#define ___________________NUM_B6__________________              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA


// MIRYOKU_ALTERNATIVES_SYM
#define ___________________SYM_L1__________________              KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR
#define ___________________SYM_L2__________________              KC_COLN,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_PLUS
#define ___________________SYM_L3__________________              KC_TILD,           KC_EXLM,           KC_AT,             KC_HASH,           KC_PIPE

#define ___________________SYM_B6__________________              KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA

// MIRYOKU_ALTERNATIVES_FUN
#define ___________________FUN_L1__________________              KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR
#define ___________________FUN_L2__________________              KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SCRL
#define ___________________FUN_L3__________________              KC_F10,            KC_F1,             KC_F2,             KC_F3,             KC_PAUS

#define ___________________FUN_B6__________________              KC_APP,            KC_BSPC,           KC_TAB,            U_NA,              U_NA,              U_NA


// MIRYOKU_ALTERNATIVES_NAV_INVERTEDT
#define ___________________NAV_R1__________________              KC_INS,            KC_HOME,           KC_UP,             KC_END,            KC_PGUP
#define ___________________NAV_R2__________________              CW_TOGG,           KC_LEFT,           KC_DOWN,           KC_RGHT,           KC_PGDN
#define ___________________NAV_R3__________________              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND

#define ___________________NAV_B6__________________              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_SPC,            KC_DEL


// MIRYOKU_ALTERNATIVES_MOUSE_INVERTEDT
#define _________________MOUSE_R1__________________              U_NU,              KC_WH_L,           KC_MS_U,           KC_WH_R,           KC_WH_U
#define _________________MOUSE_R2__________________              U_NU,              KC_MS_L,           KC_MS_D,           KC_MS_R,           KC_WH_D
#define _________________MOUSE_R3__________________              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND

#define _________________MOUSE_B6__________________              U_NA,              U_NA,              U_NA,              KC_BTN2,           KC_BTN1,           KC_BTN3


// MIRYOKU_ALTERNATIVES_MEDIA_INVERTEDT
#define _________________MEDIA_R1__________________              RGB_TOG,           RGB_MOD,           KC_VOLU,           RGB_HUI,           RGB_SAI
#define _________________MEDIA_R2__________________              U_NU,              KC_MPRV,           KC_VOLD,           KC_MNXT,           RGB_VAI
#define _________________MEDIA_R3__________________              OU_AUTO,           U_NU,              U_NU,              U_NU,              U_NU

#define _________________MEDIA_B6__________________              U_NA,              U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE


extern const char *get_layer_name(uint8_t layer);
#ifdef RGB_MATRIX_ENABLE
extern void set_layer_rgb_indicator_keymap(uint8_t r, uint8_t g, uint8_t b);
extern void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
#endif // RGB_MATRIX_ENABLE
