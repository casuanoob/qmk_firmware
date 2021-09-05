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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  GMEET,
  MEDIA,
};

// Sends RCS(KC_M) on tab, MEDIA layer on hold.
#define MUTE_MEDIA LT(MEDIA, KC_NO)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [GMEET] = LAYOUT_1x5(
        MUTE_MEDIA, RCS(KC_C), RCS(KC_R), RCS(KC_F), RCS(KC_E)
    ),

    [MEDIA] = LAYOUT_1x5(
        _______,    KC_MPRV,   KC_MPLY,   KC_MNXT,   RESET
    ),
};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MUTE_MEDIA:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(RCS(KC_M));
        } else {
          unregister_code16(RCS(KC_M));
        }
        // Do not continue with the default tap action if the LT was pressed or
        // released, but not held.
        return false;
      }
      break;
  }
  return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  tap_code(clockwise ? KC_VOLU : KC_VOLD);
  return true;
}
#endif
