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

#pragma once

#include "compose.h"
#include "delay.h"
#include "quantum.h"

enum layers_keymap {
  _BASE = 0,
  _LMOD,  // Left mods, right symbols.
  _RMOD,  // Right mods, left symbols.
  _NAV,   // Navigation.
  _WNAV,  // Workspace navigation.
  _NUM,   // Number pad.
  _FUN,   // Function keys.
  _PTR,   // Pointing device keys.
  _SPEC,  // Specials.
};

enum keycodes_keymap {
  CLEAR = SAFE_RANGE_KEYMAP,  // Clear all WORD, one-shots, and reset to BASE.
  // Shell shorthands.
  // Smart caps lock and num layer that turn off on certain keys.
  CAPWORD,
  // Use as starting range to extend the keycode list further.
  SAFE_RANGE_WITH_DEFAULT_KEYMAP,
};

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `layer_state_set_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
layer_state_t layer_state_set_keymap(layer_state_t state);

// Layers.
#define WNAV MO(_WNAV)
#define FUN OSL(_FUN)
#define LMOD OSL(_LMOD)
#define RMOD OSL(_RMOD)
#define SPECIAL OSL(_SPEC)
#define NUM_ENT LT(_NUM, KC_ENT)
#define NAV_SPC LT(_NAV, KC_SPC)

// Tap dances.
#define TD_SFT OSM(MOD_LSFT)

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Mod-taps.
#define CTL_DWN LCTL_T(KC_DOWN)

// Shorthands
#define ___x___ KC_NO

// clang-format off
/**
 * \brief Alternative Dvorak layout.
 *
 * Slightly modified versions of the original layout to surface high-frequency
 * keys on the base layer (namely, underscore `_`).  Also prevent quote `'`,
 * comma `,` and dot `.` from shifting (plays well with oneshot shift).
 */
#define DVORAK_ALT_3x5_3                                                                      \
    NS_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_UNDS,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                       TD_SFT, NAV_SPC,    LMOD,    RMOD, NUM_ENT,   KC_NO

/**
 * \brief Left-hand mods, right-hand symbols.
 */
#define LMOD_split_3x5_3                                                                      \
    SPECIAL,     FUN, ___x___, ___x___, ___x___, KC_AMPR, KC_LBRC, KC_RBRC,  KC_EQL, KC_PERC, \
    OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, ___x___, KC_QUES, KC_LCBR, KC_RCBR, KC_COLN, KC_PIPE, \
    ___x___, ___x___, ___x___, ___x___, ___x___, KC_CIRC, KC_LPRN, KC_RPRN,   KC_AT,  KC_DLR, \
                      ___x___, ___x___, _______,    WNAV,   CLEAR, ___x___

/**
 * \brief Right-hand mods, left-hand symbols.
 */
#define RMOD_split_3x5_3                                                                      \
    KC_DQUO,  KC_EQL, KC_LABK, KC_RABK,  KC_GRV, ___x___, ___x___, ___x___,     FUN, SPECIAL, \
    KC_HASH, KC_SCLN, KC_MINS, KC_PLUS, KC_EXLM, ___x___, OS_LGUI, OS_LCTL, OS_LSFT, OS_LALT, \
    KC_TILD, KC_BSLS, KC_ASTR, KC_SLSH, ___x___, ___x___, ___x___, ___x___, ___x___, OS_RALT, \
                       KC_TAB, ___x___, ___x___, _______,   CLEAR, ___x___

/**
 * \brief Numpad.
 */
#define NUM_split_3x5_3                                                                       \
     KC_EQL,    NS_7,    NS_8,    NS_9, KC_ASTR, ___x___, ___x___, ___x___, ___x___, ___x___, \
    KC_COLN,    NS_4,    NS_5,    NS_6, KC_PLUS, ___x___, ___x___, ___x___, ___x___, ___x___, \
    KC_SLSH,    NS_1,    NS_2,    NS_3, KC_MINS, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      KC_BSPC,  KC_ESC,    NS_0, ___x___, _______, ___x___

/**
 * \brief Function keys.
 */
#define FUN_split_3x5_3                                                                       \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      ___x___, ___x___, ___x___, ___x___, ___x___, ___x___

/**
 * \brief TODO.
 */
#define NAV_split_3x5_3                                                                       \
    WS_PREV, RCS_TAB,   KC_UP, CTL_TAB, WS_NEXT, ___x___, KC_HOME,   NS_UP,  KC_END, ___x___, \
    SC_SELA, KC_LEFT, CTL_DWN, KC_RGHT, ___x___, ___x___, NS_LEFT, NS_DOWN, NS_RGHT, ___x___, \
    ___x___, SC_PSTE, SC_COPY,  SC_CUT, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      ___x___, _______, ___x___, ___x___, ___x___, ___x___

/**
 * \brief TODO.
 */
#define WNAV_split_3x5_3                                                                      \
    WS_PREV,    WS_7,    WS_8,    WS_9, WS_NEXT, ___x___, WS_MPCI, WS_MPCD, ___x___, ___x___, \
    ___x___,    WS_4,    WS_5,    WS_6, ___x___, ___x___, WS_MPSH, WS_MPEX, ___x___, ___x___, \
       WS_0,    WS_1,    WS_2,    WS_3, ___x___, ___x___, WS_FPRV, WS_FNXT, ___x___, ___x___, \
                      KC_LSFT,  WS_MOD, WS_MPPR, _______, ___x___, ___x___

/**
 * \brief TODO.
 */
#define PTR_split_3x5_3                                                                       \
    WS_PREV, ___x___, ___x___, ___x___, WS_NEXT, ___x___, ___x___, ___x___, ___x___, ___x___, \
    SC_SELA, KC_BTN3, KC_BTN1, KC_BTN2, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
    ___x___, SC_PSTE, SC_COPY,  SC_CUT, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      _______, ___x___, ___x___, ___x___, ___x___, ___x___

/**
 * \brief TODO.
 */
#define SPEC_split_3x5_3                                                                      \
    ___x___, ___x___,   MACOS, ___x___, RGB_TOG, RGB_TOG, ___x___,   MACOS, ___x___, ___x___, \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
      RESET, EEP_RST, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, EEP_RST,   RESET, \
                      ___x___, RGB_MOD,RGB_RMOD,RGB_RMOD, RGB_MOD, ___x___
// clang-format on
