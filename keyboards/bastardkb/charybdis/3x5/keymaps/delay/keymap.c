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
#include "keymaps/default.h"

#define LAYOUT_charybdis_3x5_delay(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [LAYER_ALPHAS_DVORAK] = LAYOUT_charybdis_3x5_delay(
    HOME_ROW_MOD_GACS(LAYER_ALPHAS_DVORAK_3x10, LAYER_ALPHAS_THUMBS_1x6)
  ),
  [LAYER_ALPHAS_COLEMAK_DHM] = LAYOUT_charybdis_3x5_delay(
    HOME_ROW_MOD_GACS(LAYER_ALPHAS_COLEMAK_DHM_3x10, LAYER_ALPHAS_THUMBS_1x6)
  ),

#ifndef KEYMAP_DEFAULT_LITE
  [LAYER_NO_MODS_ALPHAS_DVORAK] = LAYOUT_charybdis_3x5_delay(
    LAYER_ALPHAS_DVORAK_3x10, LAYER_NO_MODS_ALPHAS_THUMBS_1x6
  ),
  [LAYER_NO_MODS_ALPHAS_COLEMAK_DHM] = LAYOUT_charybdis_3x5_delay(
    LAYER_ALPHAS_COLEMAK_DHM_3x10, LAYER_NO_MODS_ALPHAS_THUMBS_1x6
  ),
#endif  // !KEYMAP_DEFAULT_LITE

  [LAYER_DEV] = LAYOUT_charybdis_3x5_delay(LAYER_DEV_split_3x5_3),
  [LAYER_NAV] = LAYOUT_charybdis_3x5_delay(LAYER_NAV_split_3x5_3),
  [LAYER_NUM] = LAYOUT_charybdis_3x5_delay(LAYER_NUM_split_3x5_3),
  [LAYER_SYM] = LAYOUT_charybdis_3x5_delay(LAYER_SYM_split_3x5_3),
  [LAYER_EXP] = LAYOUT_charybdis_3x5_delay(LAYER_EXP_split_3x5_3),
};
// clang-format on

/** Called on layer change. */
layer_state_t layer_state_set_keymap(layer_state_t state) {
  const layer_state_t current_layer = get_highest_layer(state);
  charybdis_set_pointer_dragscroll_enabled(current_layer == LAYER_DEV ||
                                           current_layer == LAYER_SYM);
  return state;
}
