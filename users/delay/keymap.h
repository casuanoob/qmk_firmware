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

#include "features/tap_dance.h"
#include "quantum.h"

/**
 * \brief Custom keycodes.
 *
 * Use `SAFE_RANGE_KEYMAP` for keymap specific codes, instead of `SAFE_RANGE`.
 */
enum keycodes_user {
#ifdef VIA_ENABLE
  KEYCODE_USER_BEGIN = USER00,
#else
  KEYCODE_USER_BEGIN = SAFE_RANGE,
#endif
  // Custom version of these keycodes that don't shift when only oneshot shift
  // mod is locked.
  NS_BSLASH = KEYCODE_USER_BEGIN,
  NS_COMMA,
  NS_DOT,
  NS_GRAVE,
  NS_QUOTE,
  NS_LBRACKET,
  NS_RBRACKET,
  NS_SCOLON,
  NS_SLASH,
  // Custom version of up/down/left/right keycodes that can't be shifted.
  NS_UP,
  NS_DOWN,
  NS_LEFT,
  NS_RIGHT,
  // Oneshot mods.
  OS_LALT,
  OS_LCTL,
  OS_LGUI,
  OS_LSFT,
  // Compose.
  COMPOSE,
  SAFE_RANGE_KEYMAP,
};

// This keymap uses home row mods. In addition to mods, I have home row
// layer-tap keys for the SYM layer. The key arrangement is a variation on
// "ASCG-order" home row mods:
//
//             Left hand                          Right hand
// ╭───────┬───────┬───────┬───────╮   ╭───────┬───────┬───────┬───────╮
// │  Sym  │ Shift │ Ctrl  │  Gui  │   │  Gui  │ Ctrl  │ Shift │  Sym  │
// ├───────┼───────┴───────┴───────╯   ╰───────┴───────┴───────┼───────┤
// │  Alt  │                                                   │  Alt  │
// ╰───────╯                                                   ╰───────╯

// Home row mods for Dvorak layer.
#define HOME_A LT(_SYMR, KC_A)
#define HOME_O LSFT_T(KC_O)
#define HOME_E LCTL_T(KC_E)
#define HOME_U LGUI_T(KC_U)
#define HOME_H RGUI_T(KC_H)
#define HOME_T RCTL_T(KC_T)
#define HOME_N LSFT_T(KC_N)
#define HOME_S LT(_SYML, KC_S)
#define HOME_SC LALT_T(KC_SCLN)
#define HOME_Z RALT_T(KC_Z)

#define VIM_DOWN LALT(KC_DOWN)
#define VIM_LEFT LALT(KC_LEFT)
#define VIM_RIGHT LALT(KC_RIGHT)
#define VIM_SHIFT_LEFT LALT(LSFT(KC_LEFT))
#define VIM_SHIFT_RIGHT LALT(LSFT(KC_RIGHT))
#define VIM_UP LALT(KC_UP)
#define VIM_TERMINAL LCTL(LALT(KC_T))
#define VIM_TERMINAL_ESCAPE LCTL(KC_ESC)

#define SC_CUT LGUI(KC_X)
#define SC_COPY LGUI(KC_C)
#define SC_PASTE LGUI(KC_V)
#define SC_PASTE_NO_FORMAT LGUI(S(KC_V))
#define SC_LAUNCHER LGUI(KC_SPACE)
#define WS_PREVIOUS LCTL(LALT(KC_LEFT))
#define WS_NEXT LCTL(LALT(KC_RIGHT))

#define CK_ELLIPSIS LALT(KC_SEMICOLON)

// Shorthands.
#define NS_BSLS NS_BSLASH
#define NS_COMM NS_COMMA
#define NS_GRV NS_GRAVE
#define NS_QUOT NS_QUOTE
#define NS_LBRC NS_LBRACKET
#define NS_RBRC NS_RBRACKET
#define NS_RGHT NS_RIGHT
#define NS_SCLN NS_SCOLON
#define NS_SLSH NS_SLASH
#define SC_PSTE SC_PASTE
#define LAUNCHR SC_LAUNCHER
#define WS_PREV WS_PREVIOUS
#define CK_ELPS CK_ELLIPSIS
#define VIM_D VIM_DOWN
#define VIM_L VIM_LEFT
#define VIM_R VIM_RIGHT
#define VIM_S_L VIM_SHIFT_LEFT
#define VIM_S_R VIM_SHIFT_RIGHT
#define VIM_U VIM_UP
#define VIMTERM VIM_TERMINAL
#define VIMTESC VIM_TERMINAL_ESCAPE

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
  _NAVL,  // Navigation.
  _NAVR,  // Navigation.
  _SYML,  // Symbols.
  _SYMR,  // Symbols.
  _NUM,   // Number pad.
  _SPEC,  // Specials.
};

// Layers.
#define NAVL MO(_NAVL)
#define NAVR MO(_NAVR)
#define SPECIAL OSL(_SPEC)

// Tap dances.
#define TD_SFT TD(TD_ONESHOT_SHIFT)

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
    NS_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
     HOME_A,  HOME_O,  HOME_E,  HOME_U,    KC_I,    KC_D,  HOME_H,  HOME_T,  HOME_N,  HOME_S, \
    HOME_SC,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,  HOME_Z, \
                                  NAVL,  KC_SPC,  TD_SFT,    NAVR
// clang-format on

/**
 * \brief Navigation layer, with convenience one-hand shortcuts.
 *
 * Shortcuts on the left side for use with the mouse in the right hand.
 * Inverted T navigation cluster on the right side to combine with left side
 * home row mods.
 */
// clang-format off
#define NAVL_split_3x5_2                                                                      \
    SPECIAL, RCS_TAB,  KC_TAB, CTL_TAB, ___x___, ___x___, KC_HOME,   NS_UP,  KC_END, KC_BSPC, \
    OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, ___x___, ___x___, NS_LEFT, NS_DOWN, NS_RGHT,  KC_ENT, \
    SC_COPY, WS_PREV, LAUNCHR, WS_NEXT, SC_PSTE, ___x___, ___x___, ___x___, ___x___, ___x___, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Navigation layer, with convenience one-hand shortcuts.
 *
 * Shortcuts on the left side for use with the mouse in the right hand.
 * Inverted T navigation cluster on the right side to combine with left side
 * home row mods.
 */
// clang-format off
#define NAVR_split_3x5_2                                                                      \
    ___x___,  KC_ESC, ___x___, KC_COLN, ___x___, VIMTESC, VIM_S_L,   VIM_U, VIM_S_R, SPECIAL, \
    OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, ___x___, ___x___,   VIM_L,   VIM_D,   VIM_R, VIMTERM, \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Numrow.
 */
// clang-format off
#define NUM_split_3x5_2                                                                       \
    ___x___,    KC_7,    KC_8,    KC_9, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
    ___x___,    KC_4,    KC_5,    KC_6, ___x___, ___x___, OS_LGUI, OS_LCTL, OS_LSFT, OS_LALT, \
    ___x___,    KC_1,    KC_2,    KC_3, ___x___, ___x___, NS_LBRC,    KC_0, NS_RBRC, ___x___, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYML_split_3x5_2                                                                      \
    KC_DQUO,   KC_LT,   KC_GT, KC_COLN,   KC_AT, ___x___, ___x___, ___x___, ___x___, ___x___, \
    KC_EXLM, KC_PLUS, KC_MINS,  KC_EQL, KC_HASH, ___x___, ___x___, ___x___, ___x___, _______, \
    KC_TILD,  KC_DLR, KC_ASTR, KC_SLSH, KC_AMPR, ___x___, ___x___, ___x___, ___x___, ___x___, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYMR_split_3x5_2                                                                      \
    ___x___, ___x___, ___x___, ___x___, ___x___, KC_CIRC, KC_LPRN, NS_SCLN, KC_RPRN, KC_PERC, \
    _______, ___x___, ___x___, ___x___, ___x___, CK_ELPS, ___x___, KC_UNDS, ___x___, ___x___, \
    ___x___, ___x___, ___x___, ___x___, ___x___, KC_PIPE, KC_LCBR, NS_BSLS, KC_RCBR,  NS_GRV, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_2                                                                      \
    ___x___, ___x___, ___x___, ___x___, RGB_TOG, RGB_TOG, ___x___, ___x___, ___x___, ___x___, \
    ___x___, ___x___, ___x___, ___x___, EEP_RST, EEP_RST, ___x___, ___x___, ___x___, ___x___, \
    ___x___, ___x___, ___x___, ___x___, QK_BOOT, QK_BOOT, ___x___, ___x___, ___x___, ___x___, \
                               ___x___, ___x___, ___x___, ___x___
// clang-format on

// clang-format off
/**
 * \brief Converts a 3x5_2 layout into the more community 3x5_3 layout.
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
// clang-format on

#define LAYOUT_split_3x5_2_to_split_3x5_3(...) \
  _LAYOUT_split_3x5_2_to_split_3x5_3(__VA_ARGS__)

/* Converts the 3x5_2 layouts into 3x5_3 layouts. */
#define DVORAK_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(DVORAK_split_3x5_2)
#define NAVL_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NAVL_split_3x5_2)
#define NAVR_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NAVR_split_3x5_2)
#define SYML_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SYML_split_3x5_2)
#define SYMR_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SYMR_split_3x5_2)
#define NUM_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NUM_split_3x5_2)
#define SPEC_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SPEC_split_3x5_2)
