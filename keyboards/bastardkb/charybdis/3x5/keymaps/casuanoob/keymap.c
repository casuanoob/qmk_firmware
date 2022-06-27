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

//#define CHARYBDIS_AUTO_SNIPING_ON_LAYER _NAV

#define LAYOUT_charybdis_3x5_delay(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_charybdis_3x5_delay(COLEMAKdhm_cnano_3x5_3),
  [_GAME] = LAYOUT_charybdis_3x5_delay(GAMING_cnano_3x5_3),
  [_APT] = LAYOUT_charybdis_3x5_delay(APTmod_cnano_3x5_3),
  [_NAV] = LAYOUT_charybdis_3x5_delay(NAV_cnano_3x5_3),
  [_SYM] = LAYOUT_charybdis_3x5_delay(SYM_cnano_3x5_3),
  [_NUM] = LAYOUT_charybdis_3x5_delay(NUMROW_cnano_3x5_3),
  [_NUMPD] = LAYOUT_charybdis_3x5_delay(NUMPAD_cnano_3x5_3),
  [_FUN] = LAYOUT_charybdis_3x5_delay(FUN_cnano_3x5_3),
  [_SPEC] = LAYOUT_charybdis_3x5_delay(SPEC_cnano_3x5_3),
};
// clang-format on