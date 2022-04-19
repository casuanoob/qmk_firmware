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

#pragma once

#include "compose.h"
#include "delay.h"
#include "quantum.h"

#ifdef TAP_DANCE_ENABLE
#include "tap_dance.h"
#endif  // TAP_DANCE_ENABLE

/**
 * \brief Similar to `_kb`, `_user`, `_user_keymap`, and other variants, but for
 * keymaps.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
void keyboard_post_init_keymap(void);
void oneshot_locked_mods_changed_keymap(uint8_t mods);
void shutdown_keymap(void);

enum layers_keymap {
  _BASE = 0,
  _NAV,   // Navigation.
  _SYM,   // Symbols.
  _WNAV,  // Workspace navigation.
  _NUM,   // Number pad.
  _SPEC,  // Specials.
};

// Layers.
#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define WNAV TG(_WNAV)
#define SPECIAL OSL(_SPEC)

// Tap dances.
#define TD_SFT OSM(MOD_LSFT)

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Shorthands for readability.
#define ___x___ KC_NO

/**
 * \brief Alternative Dvorak layout.
 *
 * Slightly modified versions of the original layout that also prevents quote
 * `'`, comma `,` and dot `.` from shifting (plays well with oneshot shift).
 */
// clang-format off
#define DVORAK_split_3x5_2                                                                    \
    NS_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_UNDS,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                                   NAV,  TD_SFT,   KC_SPC,    SYM
// clang-format on

/**
 * \brief Navigation layer, with convenience one-hand shortcuts.
 *
 * Shortcuts on the left side for use with the mouse in the right hand.
 * Inverted T navigation cluster on the right side to combine with left side
 * home row mods.
 */
// clang-format off
#define NAV_split_3x5_2                                                                       \
    WS_PREV, WS_NEXT, RCS_TAB, CTL_TAB,    WNAV,    WNAV, KC_HOME,   NS_UP,  KC_END, KC_BSPC, \
    OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, ___x___, ___x___, NS_LEFT, NS_DOWN, NS_RGHT,  KC_ENT, \
    SPECIAL,  SC_CUT, SC_COPY, SC_PSTE, ___x___, ___x___, KC_BTN3, KC_BTN1, KC_BTN2,  KC_TAB, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYM_split_3x5_2                                                                       \
     KC_ESC, KC_PERC, KC_QUES, KC_COLN,   KC_AT, KC_CIRC, KC_LPRN, KC_RPRN, NS_SCLN,  NS_GRV, \
    KC_EXLM, KC_PLUS, KC_MINS,  KC_EQL, KC_HASH, ___x___, OS_LGUI, OS_LCTL, OS_LSFT, OS_LALT, \
    KC_TILD,  KC_DLR, KC_ASTR, KC_SLSH, KC_AMPR, KC_PIPE, KC_LCBR, KC_RCBR, NS_BSLS, SPECIAL, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Numrow.
 */
// clang-format off
#define NUM_split_3x5_2                                                                       \
       NS_7,    NS_5,    NS_3,    NS_1,    NS_9,    NS_8,    NS_0,    NS_2,    NS_4,    NS_6, \
    OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, ___x___, ___x___, OS_LGUI, OS_LCTL, OS_LSFT, OS_LALT, \
    ___x___, ___x___, NS_COMM,  NS_DOT, ___x___, ___x___, NS_LBRC, NS_RBRC, ___x___, ___x___, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Workspace navigation layers.
 *
 * Contains platform-dependent shortcuts for moving between virtual workspaces
 * and interacting with tiling window managers.
 */
// clang-format off
#define WNAV_split_3x5_2                                                                      \
    ___x___,  WS_MOD, WS_MPCD, WS_MPCI,    WNAV,    WNAV, WS_MPCI, WS_MPCD,  WS_MOD, ___x___, \
    ___x___, WS_MPPR, WS_MPEX, WS_MPSH, ___x___, ___x___, WS_MPSH, WS_MPEX, WS_MPPR, ___x___, \
    ___x___, ___x___, WS_FNXT, WS_FPRV, ___x___, ___x___, WS_FPRV, WS_FNXT, ___x___, ___x___, \
                               _______, KC_LSFT, KC_LSFT, _______
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_2                                                                      \
    ___x___, ___x___, ___x___, ___x___, RGB_TOG, RGB_TOG, ___x___, ___x___, ___x___, ___x___, \
    ___x___, SC_NWIN, SC_NTAB, ___x___, EEP_RST, EEP_RST, ___x___, SC_NTAB, SC_NWIN, ___x___, \
    ___x___, ___x___, SC_CLSE, ___x___, QK_BOOT, QK_BOOT, ___x___, SC_CLSE, ___x___, ___x___, \
                               LAUNCHR, ___x___, ___x___, LAUNCHR
// clang-format on

// clang-format off
/**
 * \brief Converts a 3x5_2 layout into the more common 3x5_3 layout.
 *
 * In other words, converts a split-34 keymap into a split-36 one.
 */
#define _LAYOUT_split_3x5_2_to_split_3x5_3(                  \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                          k33, k34, k35, k36)                \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                   k33, k34, KC_NO, KC_NO, k35, k36

#define LAYOUT_split_3x5_2_to_split_3x5_3(...) _LAYOUT_split_3x5_2_to_split_3x5_3(__VA_ARGS__)

/* Converts the 3x5_2 layouts into 3x5_3 layouts. */
#define DVORAK_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(DVORAK_split_3x5_2)
#define NAV_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NAV_split_3x5_2)
#define SYM_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SYM_split_3x5_2)
#define NUM_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NUM_split_3x5_2)
#define WNAV_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(WNAV_split_3x5_2)
#define SPEC_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SPEC_split_3x5_2)
// clang-format on
