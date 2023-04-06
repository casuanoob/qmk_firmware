/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "delay.h"
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#endif  // RGB_MATRIX_ENABLE

#include "features/repeat_key.h"
#include "features/oneshot_mod.h"

typedef struct {
    oneshot_mod_state_t lalt;
    oneshot_mod_state_t lctl;
    oneshot_mod_state_t lgui;
    oneshot_mod_state_t lsft;
} osm_state_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //Custom repeat key handler.
    if (!process_repeat_key_with_alt(keycode, record, REPEAT, ALTREP)) {
        return false;
    }

    // Custom oneshot mods handler.
    static osm_state_t osm_state = {
        .lalt = ONESHOT_UP_UNQUEUED,
        .lctl = ONESHOT_UP_UNQUEUED,
        .lgui = ONESHOT_UP_UNQUEUED,
        .lsft = ONESHOT_UP_UNQUEUED,
    };
    oneshot_mod_pre(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
    oneshot_mod_pre(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
    oneshot_mod_pre(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
    oneshot_mod_pre(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);

    const bool result = process_record_user_keymap(keycode, record);
    
    oneshot_mod_post(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
    oneshot_mod_post(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
    oneshot_mod_post(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
    oneshot_mod_post(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);
    
    return result;
}

__attribute__((weak)) bool process_record_user_keymap(uint16_t keycode,
                                                      keyrecord_t *record) {
  return true;
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_reset(void) {
  rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
  rgb_matrix_sethsv(RGB_MATRIX_DEFAULT_HSV);
  rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
}
#endif  // RGB_MATRIX_ENABLE

void matrix_scan_user(void) { matrix_scan_user_keymap(); }

__attribute__((weak)) void matrix_scan_user_keymap(void) {}

/** Called on layer change. */
layer_state_t layer_state_set_user(layer_state_t state) {
  return layer_state_set_user_keymap(state);
}

__attribute__((weak)) layer_state_t layer_state_set_user_keymap(
    layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  oneshot_enable();
  keyboard_post_init_user_keymap();
}

__attribute__((weak)) void keyboard_post_init_user_keymap(void) {}

/*void eeconfig_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
  eeconfig_update_rgb_matrix_default();
#endif  // RGB_MATRIX_ENABLE
}*/

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif  // RGB_MATRIX_ENABLE

void shutdown_user(void) {
#ifdef RGB_MATRIX_ENABLE
  //rgb_matrix_set_color_all(RGB_RED);
  rgb_matrix_set_color_all(rgb_matrix_get_val(), 0x00, 0x00);
  rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
#ifdef OLED_ENABLE
  oled_off();
#endif  // OLED_ENABLE
  shutdown_user_keymap();
}

__attribute__((weak)) void shutdown_user_keymap(void) {}

bool get_repeat_key_eligible(uint16_t keycode,
                                                   keyrecord_t* record) {
  switch (keycode) {
    // Also ignore Tri Layer keys
    case QK_TRI_LAYER_LOWER:
    case QK_TRI_LAYER_UPPER:
    // Also ignore custom Callum mods
    case OS_LALT ... OS_LSFT:
    // Ignore MO, TO, TG, and TT layer switch keys.
    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
    case QK_TO ... QK_TO_MAX:
    case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
    // Ignore mod keys.
    case KC_LCTL ... KC_RGUI:
    case KC_HYPR:
    case KC_MEH:
      // Ignore one-shot keys.
#ifndef NO_ACTION_ONESHOT
    case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
    case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#endif  // NO_ACTION_ONESHOT
      return false;

      // Ignore hold events on tap-hold keys.
#ifndef NO_ACTION_TAPPING
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
#ifndef NO_ACTION_LAYER
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#endif  // NO_ACTION_LAYER
      if (record->tap.count == 0) {
        return false;
      }
      break;
#endif  // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
    case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
      if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
        return false;
      }
      break;
#endif  // SWAP_HANDS_ENABLE
  }

  return true;
}