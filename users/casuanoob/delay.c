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

#include <stdint.h>
#include "config.h"
#include "delay.h"
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#endif  // RGB_MATRIX_ENABLE

#include "features/oneshot_mod.h"
#include "features/combos.h"

typedef struct {
    oneshot_mod_state_t lalt;
    oneshot_mod_state_t lctl;
    oneshot_mod_state_t lgui;
    oneshot_mod_state_t lsft;
} osm_state_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case OS_LALT ... OS_LSFT:
            return false;  // Ignore backspace.
    }

    return true;  // Other keys can be repeated.
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        // I have a dedicated underscore key, so no need to shift KC_MINS.
        case KC_UNDS:
        case KC_MINS:
        // Also ignore Tri Layer keys
        case QK_TRI_LAYER_LOWER:
        case QK_TRI_LAYER_UPPER:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}
