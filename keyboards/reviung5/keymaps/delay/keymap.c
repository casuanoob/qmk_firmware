/**
 * Copyright 2021 gtips
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap.
enum layer_names {
  LAYER_GMEET,
  LAYER_RGB,
};

// Sends RCS(KC_M) on tab, MEDIA layer on hold.
#define MUTE_RGB LT(LAYER_RGB, KC_NO)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_GMEET] = LAYOUT_reviung5(
    RCS(KC_E), RCS(KC_R), RCS(KC_F), RCS(KC_C), MUTE_RGB
  ),
  [LAYER_RGB] = LAYOUT_reviung5(
    RESET, RGB_RMOD, RGB_TOG, RGB_MOD, _______
  )
};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MUTE_RGB:
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
  if (index != 0) {
    return true;
  }
  switch (get_highest_layer(layer_state)) {
    case LAYER_RGB:
      clockwise ? rgblight_increase_val() : rgblight_decrease_val();
      break;
    default:
      tap_code(clockwise ? KC_VOLU : KC_VOLD);
      break;
  }
  return true;
}
#endif  // ENCODER_ENABLE

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_keymap(layer_state_t state) {
  switch (get_highest_layer(state)) {
    default:  // For any other layers, or the default layer
      rgblight_reload_from_eeprom();
      break;
  }
  return state;
}
#endif  // RGBLIGHT_ENABLE
