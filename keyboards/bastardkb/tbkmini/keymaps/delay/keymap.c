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

// clang-format off
#define _LAYOUT_split_3x5_to_3x6(                                     \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09,          \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19,          \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29,          \
                     k32, k33, k34, k35, k36, k37)                    \
  XXXXXXX, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, XXXXXXX, \
  XXXXXXX, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, XXXXXXX, \
  XXXXXXX, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, XXXXXXX, \
                     k32, k33, k34, k35, k36, k37
#define LAYOUT_split_3x5_to_3x6(...) _LAYOUT_split_3x5_to_3x6(__VA_ARGS__)
#define LAYOUT_tbkmini(...) LAYOUT_split_3x6_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [LAYER_ALPHAS_DVORAK] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(
    HOME_ROW_MOD_GACS(LAYER_ALPHAS_DVORAK_3x10, LAYER_ALPHAS_THUMBS_1x6)
  )),
  [LAYER_ALPHAS_COLEMAK_DHM] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(
    HOME_ROW_MOD_GACS(LAYER_ALPHAS_COLEMAK_DHM_3x10, LAYER_ALPHAS_THUMBS_1x6)
  )),

#ifndef KEYMAP_DEFAULT_LITE
  [LAYER_NO_MODS_ALPHAS_DVORAK] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(
    LAYER_ALPHAS_DVORAK_3x10, LAYER_NO_MODS_ALPHAS_THUMBS_1x6
  )),
  [LAYER_NO_MODS_ALPHAS_COLEMAK_DHM] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(
    LAYER_ALPHAS_COLEMAK_DHM_3x10, LAYER_NO_MODS_ALPHAS_THUMBS_1x6
  )),
#endif  // KEYMAP_DEFAULT_LITE

  [LAYER_DEV] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(LAYER_DEV_split_3x5_3)),
  [LAYER_NAV] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(LAYER_NAV_split_3x5_3)),
  [LAYER_NUM] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(LAYER_NUM_split_3x5_3)),
  [LAYER_SYM] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(LAYER_SYM_split_3x5_3)),
  [LAYER_PTR] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(LAYER_PTR_split_3x5_3)),

#ifndef KEYMAP_DEFAULT_LITE
  [LAYER_EXP] = LAYOUT_tbkmini(LAYOUT_split_3x5_to_3x6(LAYER_EXP_split_3x5_3)),
#endif  // !KEYMAP_DEFAULT_LITE
};
// clang-format on
