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
#include "keymaps/split36.h"

#define LAYOUT_charybdis_3x5_delay(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_charybdis_3x5_delay(DVORAK_ALT_3x5_3),
  [_LMOD] = LAYOUT_charybdis_3x5_delay(LMOD_split_3x5_3),
  [_RMOD] = LAYOUT_charybdis_3x5_delay(RMOD_split_3x5_3),
  [_NAV] = LAYOUT_charybdis_3x5_delay(NAV_split_3x5_3),
  [_WNAV] = LAYOUT_charybdis_3x5_delay(WNAV_split_3x5_3),
  [_NUM] = LAYOUT_charybdis_3x5_delay(NUM_split_3x5_3),
  [_FUN] = LAYOUT_charybdis_3x5_delay(FUN_split_3x5_3),
  [_SPEC] = LAYOUT_charybdis_3x5_delay(SPEC_split_3x5_3),
};
// clang-format on
