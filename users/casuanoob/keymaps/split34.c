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

#include "keymaps/split34.h"
#include "platform.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"
#endif  // RGB_MATRIX_ENABLE

#ifdef ONESHOT_MOD_ENABLE
#include "oneshot_mod.h"
#endif  // ONESHOT_MOD_ENABLE

#ifdef ONESHOT_MOD_ENABLE
bool is_oneshot_mod_cancel_key(uint16_t keycode) {
  switch (keycode) {
    case NAV:
    case SYM:
      return true;
    default:
      return false;
  }
}

bool is_oneshot_mod_ignore_key(uint16_t keycode) {
  switch (keycode) {
    case NAV:
    case SYM:
    case OS_LALT:
    case OS_LCTL:
    case OS_LGUI:
    case OS_LSFT:
      return true;
    default:
      return false;
  }
}
#endif  // ONESHOT_MOD_ENABLE

bool process_record_user_keymap(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case KC_ESCAPE:
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
      del_mods(MOD_MASK_SHIFT);
      break;
  }
  return true;
};

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

void matrix_scan_user_keymap(void) { matrix_scan_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

#ifdef RGB_MATRIX_ENABLE
static void maybe_update_rgb_matrix(state | default_layer_state) {
  get_highest_layer(state | default_layer_state);
}
/** Called on layer change. */
layer_state_t layer_state_set_user_keymap(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
    switch (maybe_update_rgb_matrix(state | default_layer_state)) {
      case _GAME:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_TEAL);
        break;
      case _APT:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_AZURE);
        break;
      case _NUMPD:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_SPRINGGREEN);
        break;
      case _FUN:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_CORAL);
        break;
      case _SPEC:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_GOLDENROD);
        break;
      default: //  for any other layers, or the default layer
        rgb_matrix_reload_from_eeprom();  // Load default values.
        break;
    }
  return state;
}

#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
  if (active) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  } else {
    maybe_update_rgb_matrix(state | default_layer_state)
    //rgb_matrix_reload_from_eeprom();  // Load default values.
  }
#endif  // CAPS_WORD_ENABLE

#endif // RGB_MATRIX_ENABLE

__attribute__((weak)) layer_state_t layer_state_set_keymap(
    layer_state_t state) {
  return state;
}

void keyboard_post_init_user_keymap(void) { keyboard_post_init_keymap(); }

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void oneshot_locked_mods_changed_user_keymap(uint8_t mods) {
  oneshot_locked_mods_changed_keymap(mods);
}

__attribute__((weak)) void oneshot_locked_mods_changed_keymap(uint8_t mods) {}

void shutdown_user_keymap(void) { shutdown_keymap(); }

__attribute__((weak)) void shutdown_keymap(void) {}
