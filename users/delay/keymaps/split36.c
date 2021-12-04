/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "keymaps/split36.h"
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
    case CLEAR:
    case LMOD:
    case RMOD:
      return true;
    default:
      return false;
  }
}

bool is_oneshot_mod_ignore_key(uint16_t keycode) {
  switch (keycode) {
    case CLEAR:
    case LMOD:
    case RMOD:
    case OS_LALT:
    case OS_LCTL:
    case OS_LGUI:
    case OS_LSFT:
    case OS_RALT:
      return true;
    default:
      return false;
  }
}
#endif  // ONESHOT_MOD_ENABLE

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CLEAR:
      clear_oneshot_mods();
      if (get_oneshot_layer() != 0) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      }
      layer_move(default_layer_state);
      return false;
    case KC_ESCAPE:
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
      del_mods(MOD_MASK_SHIFT);
      break;
    case MACOS:
      if (record->event.pressed) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        if (is_macos()) {
          rgb_matrix_sethsv_noeeprom(HSV_CYAN);
        } else {
          rgb_matrix_sethsv_noeeprom(HSV_GREEN);
        }
      }
      return false;
  }
  return true;
};

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUM_ENT:
    case NAV_SPC:
      return true;
  }
  return false;
}
#endif  // TAPPING_FORCE_HOLD_PER_KEY
