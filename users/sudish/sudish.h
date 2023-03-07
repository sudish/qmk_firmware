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
  VRSN = SAFE_RANGE
};


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


// Common layers
enum miryoku_layers {
#define MIRYOKU_X(LAYER, STRING) U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
  N_LAYERS  // Total number of layers
};

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

#ifdef TAP_DANCE_ENABLE
enum {
  TD_M_SYS = 0,
};

#define TD_MSYS TD(TD_M_SYS)
#endif // TAP_DANCE_ENABLE

#define TG_XTRA TG(U_EXTRA)
#define TO_BASE TO(U_BASE)

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
#define HROW_L(K1, K2, K3, K4, K5)           LGUI_T(K1), LALT_T(K2), LCTL_T(K3), LSFT_T(K4), K5
#define HROW_R(K1, K2, K3, K4, K5)           K1, RSFT_T(K2), RCTL_T(K3), RALT_T(K4), RGUI_T(K5)
// Bottom row
#define BROW(K1, K2, K3, K4, K5, K6)         LT(U_FUN, K1), LT(U_NUM, K2), LT(U_SYM, K3), LT(U_MOUSE, K4), LT(U_NAV, K5), LT(U_MEDIA, K6)
#define BROW_L3(K1, K2, K3)                  LT(U_FUN, K1), LT(U_NUM, K2), LT(U_SYM, K3)
#define BROW_R3(K4, K5, K6)                  LT(U_MOUSE, K4), LT(U_NAV, K5), LT(U_MEDIA, K6)

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

#define ___________________TAP_B6__________________              KC_DEL,            KC_BSPC,           KC_ENT,            KC_TAB,            KC_SPC,            KC_ESC


// MIRYOKU_ALTERNATIVES_TAP_QWERTY 
#define ___________________BASE_LNUM_______________              KC_1,              KC_2,              KC_3,              KC_4,              KC_5
#define ___________________BASE_L1_________________              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T
#define ___________________BASE_L2_________________       HROW_L(KC_A,              KC_S,              KC_D,              KC_F,              KC_G)
#define ___________________BASE_L3_________________              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B

#define ___________________BASE_RNUM_______________              KC_6,              KC_7,              KC_8,              KC_9,              KC_0
#define ___________________BASE_R1_________________              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P
#define ___________________BASE_R2_________________       HROW_R(KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT)
#define ___________________BASE_R3_________________              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH

#define ___________________BASE_B6_________________         BROW(KC_DEL,            KC_BSPC,           KC_ENT,            KC_TAB,            KC_SPC,            KC_ESC)
#define          __________BASE_B3_L______               BROW_L3(KC_DEL,            KC_BSPC,           KC_ENT)
#define          __________BASE_B3_R______               BROW_R3(KC_TAB,            KC_SPC,            KC_ESC)


// MIRYOKU_ALTERNATIVES_NUM_FLIP
#define ___________________NUM_L1__________________              TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA
#define ___________________NUM_L2__________________              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA
#define ___________________NUM_L3__________________              U_NA,              KC_ALGR,           TD(U_TD_U_NAV),    TD(U_TD_U_NUM),    U_NA

#define ___________________NUM_R1__________________              KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC
#define ___________________NUM_R2__________________              KC_EQL,            KC_4,              KC_5,              KC_6,              KC_SCLN
#define ___________________NUM_R3__________________              KC_BSLS,           KC_1,              KC_2,              KC_3,              KC_GRV

#define ___________________NUM_B6__________________              U_NA,              U_NA,              U_NA,              KC_MINS,           KC_0,              KC_DOT


// MIRYOKU_ALTERNATIVES_SYM_FLIP
#define ___________________SYM_L1__________________              TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA
#define ___________________SYM_L2__________________              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA
#define ___________________SYM_L3__________________              U_NA,              KC_ALGR,           TD(U_TD_U_MOUSE),  TD(U_TD_U_SYM),    U_NA

#define ___________________SYM_R1__________________              KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR
#define ___________________SYM_R2__________________              KC_PLUS,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_COLN
#define ___________________SYM_R3__________________              KC_PIPE,           KC_EXLM,           KC_AT,             KC_HASH,           KC_TILD

#define ___________________SYM_B6__________________              U_NA,              U_NA,              U_NA,              KC_UNDS,           KC_LPRN,           KC_RPRN


// MIRYOKU_ALTERNATIVES_FUN_FLIP
#define ___________________FUN_L1__________________              TD(U_TD_BOOT),     TD(U_TD_U_TAP),    TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA
#define ___________________FUN_L2__________________              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA
#define ___________________FUN_L3__________________              U_NA,              KC_ALGR,           TD(U_TD_U_MEDIA),  TD(U_TD_U_FUN),    U_NA

#define ___________________FUN_R1__________________              KC_PSCR,           KC_F7,             KC_F8,             KC_F9,             KC_F12
#define ___________________FUN_R2__________________              KC_SCRL,           KC_F4,             KC_F5,             KC_F6,             KC_F11
#define ___________________FUN_R3__________________              KC_PAUS,           KC_F1,             KC_F2,             KC_F3,             KC_F10

#define ___________________FUN_B6__________________              U_NA,              U_NA,              U_NA,              KC_TAB,            KC_SPC,            KC_APP


// MIRYOKU_ALTERNATIVES_NAV_INVERTEDT_FLIP
#define ___________________NAV_L1__________________              KC_PGUP,           KC_HOME,           KC_UP,             KC_END,            KC_INS
#define ___________________NAV_L2__________________              KC_PGDN,           KC_LEFT,           KC_DOWN,           KC_RGHT,           CW_TOGG
#define ___________________NAV_L3__________________              U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO

#define ___________________NAV_R1__________________              U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT)
#define ___________________NAV_R2__________________              U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI
#define ___________________NAV_R3__________________              U_NA,              TD(U_TD_U_NAV),    TD(U_TD_U_NUM),    KC_ALGR,           U_NA

#define ___________________NAV_B6__________________              KC_DEL,            KC_BSPC,           KC_ENT,            U_NA,              U_NA,              U_NA


// MIRYOKU_ALTERNATIVES_MOUSE_INVERTEDT_FLIP
#define _________________MOUSE_L1__________________              KC_WH_U,           KC_WH_L,           KC_MS_U,           KC_WH_R,           U_NU
#define _________________MOUSE_L2__________________              KC_WH_D,           KC_MS_L,           KC_MS_D,           KC_MS_R,           U_NU
#define _________________MOUSE_L3__________________              U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO

#define _________________MOUSE_R1__________________              U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT)
#define _________________MOUSE_R2__________________              U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI
#define _________________MOUSE_R3__________________              U_NA,              TD(U_TD_U_MOUSE),  TD(U_TD_U_SYM),    KC_ALGR,           U_NA

#define _________________MOUSE_B6__________________              KC_BTN3,           KC_BTN1,           KC_BTN2,           U_NA,              U_NA,              U_NA


// MIRYOKU_ALTERNATIVES_MEDIA_INVERTEDT_FLIP
#define _________________MEDIA_L1__________________              RGB_HUI,           RGB_SAI,           KC_VOLU,           RGB_VAI,           RGB_TOG
#define _________________MEDIA_L2__________________              RGB_MOD,           KC_MPRV,           KC_VOLD,           KC_MNXT,           U_NU
#define _________________MEDIA_L3__________________              U_NU,              U_NU,              U_NU,              U_NU,              OU_AUTO

#define _________________MEDIA_R1__________________              U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT)
#define _________________MEDIA_R2__________________              U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI
#define _________________MEDIA_R3__________________              U_NA,              TD(U_TD_U_MEDIA),  TD(U_TD_U_FUN),    KC_ALGR,           U_NA

#define _________________MEDIA_B6__________________              KC_MUTE,           KC_MPLY,           KC_MSTP,           U_NA,              U_NA,              U_NA


extern const char *get_layer_name(uint8_t layer);
#ifdef RGB_MATRIX_ENABLE
extern void set_layer_rgb_indicator_keymap(uint8_t r, uint8_t g, uint8_t b);
extern void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type);
#endif // RGB_MATRIX_ENABLE
