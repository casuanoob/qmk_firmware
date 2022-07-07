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

#include QMK_KEYBOARD_H
#include "keymaps/split34.h"

#define LAYOUT_charybdis_3x5_delay(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_charybdis_3x5_delay(COLEMAKdhm_split_3x5_3),
  [_GAME] = LAYOUT_charybdis_3x5_delay(GAMING_split_3x5_3),
  [_APTm] = LAYOUT_charybdis_3x5_delay(APTmod_split_3x5_3),
  [_APT4] = LAYOUT_charybdis_3x5_delay(APTv4_split_3x5_3),
  [_CAN] = LAYOUT_charybdis_3x5_delay(Canary_split_3x5_3),
  [_NAV] = LAYOUT_charybdis_3x5_delay(NAV_split_3x5_3),
  [_SYM] = LAYOUT_charybdis_3x5_delay(SYM_split_3x5_3),
  [_NUM] = LAYOUT_charybdis_3x5_delay(NUMROW_split_3x5_3),
  [_NUMPD] = LAYOUT_charybdis_3x5_delay(NUMPAD_split_3x5_3),
  [_FUN] = LAYOUT_charybdis_3x5_delay(FUN_split_3x5_3),
  [_SPEC] = LAYOUT_charybdis_3x5_delay(SPEC_split_3x5_3),
};
// clang-format on
/**
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _GAME:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_TEAL);
        break;
    case _APT:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_TURQUOISE);
        break;
    case _NUMPD:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_AZURE);
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
*/
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state|default_layer_state) > 0) {
            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }
    } else {  /* Layer 0 */
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
    }
    return false;
}
#endif // ENCODER_ENABLE

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        if (active) {
            register_code(KC_A);
        } else {
            unregister_code(KC_A);
        }
    }
    return true;
}
#endif // DIP_SWITCH_ENABLE

// Triple nop delay thing lol
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}

void keyboard_post_init_user_keymap(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
  debug_matrix=false;
  //debug_keyboard=true;
  debug_mouse=false;
  rgb_matrix_sethsv_noeeprom(HSV_WHITE);
}