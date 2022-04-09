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

// clang-format off
#define _LAYOUT_split_3x5_to_3x6(                                   \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09,        \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19,        \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29,        \
                     k32, k33, k34, k35, k36, k37)                  \
  LAYOUT_split_3x6_3(                                               \
    KC_NO, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, KC_NO, \
    KC_NO, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, KC_NO, \
    KC_NO, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, KC_NO, \
                     k32, k33, k34, k35, k36, k37)
#define LAYOUT_split_3x5_to_3x6(...) _LAYOUT_split_3x5_to_3x6(__VA_ARGS__)
#define LAYOUT_tbkmini(...) LAYOUT_split_3x5_to_3x6(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_tbkmini(DVORAK_ALT_3x5_3),
  [_LMOD] = LAYOUT_tbkmini(LMOD_split_3x5_3),
  [_RMOD] = LAYOUT_tbkmini(RMOD_split_3x5_3),
  [_NAV] = LAYOUT_tbkmini(NAV_split_3x5_3),
  [_WNAV] = LAYOUT_tbkmini(WNAV_split_3x5_3),
  [_NUM] = LAYOUT_tbkmini(NUM_split_3x5_3),
  [_FUN] = LAYOUT_tbkmini(FUN_split_3x5_3),
  [_SPEC] = LAYOUT_tbkmini(SPEC_split_3x5_3),
};
// clang-format on
