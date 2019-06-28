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

#include QMK_KEYBOARD_H
#include "sudish.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  NOT_A_TAP
};

/* How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /* DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  // Assumes no one is trying to type the same letter three times (at least not quickly).
  // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return NOT_A_TAP;
}

// An instance of 'tap' for the 'n' tap dance.
static tap mtap_state = {
  .is_press_action = true,
  .state = 0
};

void m_finished (qk_tap_dance_state_t *state, void *user_data) {
  mtap_state.state = cur_dance(state);
  switch (mtap_state.state) {
    case SINGLE_TAP:
    case DOUBLE_HOLD: // Allow autorepeat on double tap and hold
      register_code(KC_M); break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RSFT)); layer_on(_SYSTEM); break;
    case TRIPLE_TAP:
      register_code(KC_M); unregister_code(KC_M);
      /* FALL THROUGH */
    case DOUBLE_TAP:
    case DOUBLE_SINGLE_TAP:
      register_code(KC_M); unregister_code(KC_M); register_code(KC_M); break;
  }
}

void m_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (mtap_state.state) {
    case SINGLE_TAP:
    case DOUBLE_HOLD:
    case TRIPLE_TAP:
    case DOUBLE_TAP:
    case DOUBLE_SINGLE_TAP:
      unregister_code(KC_M); break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RSFT)); layer_off(_SYSTEM); break;
  }
  mtap_state.state = 0;
}

// Tap dance
qk_tap_dance_action_t tap_dance_actions[] = {
  // 'm' normally, System + Shift when held (for easy cut and paste)
  [TD_M_SYS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, m_finished, m_reset)
};
