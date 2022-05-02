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
  _GAME,  // Gaming layer.
  _LMOD,  // Left mods, right symbols.
  _RMOD,  // Right mods, left symbols.
  _NAV,   // Navigation.
  _WNAV,  // Workspace navigation.
  _NUM,   // Number pad.
  _FUN,   // Function keys.
  _SPEC,  // Specials.
  _PTR,   // Pointer layer.
  _EXT,   // Extended layer.
};

enum keycodes_keymap {
  CLEAR = SAFE_RANGE_KEYMAP,  // Clear all WORD, one-shots, and reset to BASE.
  // Shell shorthands.
  // Smart caps lock and num layer that turn off on certain keys.
  CAPWORD,
  // Use as starting range to extend the keycode list further.
  SAFE_RANGE_WITH_DEFAULT_KEYMAP,
};

// Layers.
#define NAV OSL(_NAV)
#define WNAV MO(_WNAV)
#define FUN OSL(_FUN)
#define LMOD OSL(_LMOD)
#define RMOD OSL(_RMOD)
#define SPECIAL OSL(_SPEC)
#define GAME TG(_GAME)
#define NUM_ENT LT(_NUM, KC_ENT)
#define NAV_SPC LT(_NAV, KC_SPC)
#define MOD_TAB LT(_LMOD, KC_TAB)
#define MOD_ESC LT(_RMOD, KC_ESC)

// Tap dances.
#define TD_SFT OSM(MOD_LSFT)
// One-shot keys.
#if defined(TAP_DANCE_ENABLE) && defined(TD_ONESHOT_SHIFT_ENABLE)
#define OSM_SFT TD(TD_ONESHOT_SHIFT)
#else
#define OSM_SFT OSM(MOD_LSFT)
#endif  // TAP_DANCE_ENABLE && TD_ONESHOT_SHIFT_ENABLE

#if defined(TAP_DANCE_ENABLE) && defined(POINTING_DEVICE_ENABLE) && \
    defined(TD_ONESHOT_DRAGSCROLL_ENABLE) &&                        \
    defined(KEYBOARD_bastardkb_charybdis)
#define TD_DRG TD(TD_ONESHOT_DRAGSCROLL)
#else
#define TD_DRG KC_NO
#endif  // TAP_DANCE_ENABLE && POINTING_DEVICE_ENABLE &&
        // TD_ONESHOT_DRAGSCROLL_ENABLE && KEYBOARD_bastardkb_charybdis

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Mod-taps.
#define CTL_DWN LCTL_T(KC_DOWN)
#define GUI_RGH LGUI_T(KC_RIGHT)
#define SFT_LFT LSFT_T(KC_LEFT)

// Shorthands for readability.
#define ___x___ KC_NO
/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ ___x___, ___x___, ___x___, ___x___, ___x___
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, ___x___
#define ______________HOME_ROW_GACS_R______________ ___x___, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define ______________ONESHROW_GACS_L______________ OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___
#define ______________ONESHROW_GACS_R______________ ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI
#define ______________ONESHROW_ASCG_L______________ OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, ___x___
#define ______________ONESHROW_ASCG_R______________ ___x___, OS_LGUI, OS_LCTL, OS_LSFT, OS_LALT

/**
 * \brief Alternative Dvorak layout.
 *
 * Slightly modified versions of the original layout to surface high-frequency
 * keys on the base layer (namely, underscore `_`).  Also prevent quote `'`,
 * comma `,` and dot `.` from shifting (plays well with oneshot shift).
 */
// clang-format off
#define DVORAK_ALT_3x5_3                                                                      \
    NS_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
     TD_SFT,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                         LMOD, NAV_SPC, MOD_TAB, MOD_ESC, NUM_ENT,    RMOD
// clang-format on
/** 
 * \brief COLEMAK-dhm layout.
 * 
 * quote `'` replaces `;` on base layer to accommodate reduced keys.
 * Also prevent quote `'`, comma `,` and dot `.` from shifting 
 * (plays well with oneshot shift).
 */
// clang-format off
#define COLEMAKdhm_ALT_3x5_3                                                                  \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, NS_QUOT, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, NS_COMM,  NS_DOT,  TD_SFT, \
                         LMOD, NAV_SPC, MOD_TAB, MOD_ESC, NUM_ENT,    RMOD
// clang-format on
/** 
 * \brief Gaming layout (3 rows, 10 columns). 
 */
// clang-format off
#define GAMING_ALT_3x5_3                                                                     \
       KC_T,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
    KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_J,    KC_K,    KC_L, NS_QUOT, \
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_N,    KC_M, NS_COMM,  NS_DOT,  TD_SFT, \
                         LMOD, NAV_SPC, MOD_TAB, MOD_ESC, NUM_ENT,    RMOD
// clang-format on
/**
 * \brief Left-hand mods, right-hand symbols.
 */
// clang-format off
#define LMOD_split_3x5_3                                                                      \
    SPECIAL,     FUN,   KC_F2, C(KC_D), ___x___, KC_AMPR, KC_LCBR,  KC_EQL, KC_RCBR, KC_PERC, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, KC_CIRC, KC_LPRN, KC_QUES, KC_RPRN,  KC_DLR, \
     KC_APP, KC_BTN2, KC_BTN1, KC_BTN3,  TD_DRG, KC_PIPE, KC_LBRC,   KC_AT, KC_RBRC, KC_SCLN, \
                      _______, ___x___, _______, ___x___,   CLEAR, ___x___
// clang-format on

/**
 * \brief Right-hand mods, left-hand symbols.
 */
// clang-format off
#define RMOD_split_3x5_3                                                                      \
    KC_DQUO, KC_LABK,  KC_EQL, KC_RABK,  KC_GRV, ___x___, ___x___, ___x___,     FUN, SPECIAL, \
    KC_HASH, KC_PLUS, KC_MINS, KC_COLN, KC_EXLM, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    KC_TILD, KC_BSLS, KC_ASTR, KC_SLSH, KC_UNDS,  TD_DRG, KC_BTN3, KC_BTN1, KC_BTN2,  KC_APP, \
                      ___x___, ___x___, _______, _______,   CLEAR, _______

// clang-format on

/**
 * \brief Numpad.
 */
// clang-format off
#define NUM_split_3x5_3                                                                       \
     NS_DOT,    NS_7,    NS_8,    NS_9, NS_COMM, ___x___, ___x___, ___x___, ___x___, ___x___, \
     KC_EQL,    NS_4,    NS_5,    NS_6, KC_PLUS, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    KC_SLSH,    NS_1,    NS_2,    NS_3, KC_ASTR, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      KC_BSPC,    NS_0, KC_MINS, ___x___, _______, ___x___
// clang-format on

/**
 * \brief Function keys.
 */
// clang-format off
#define FUN_split_3x5_3                                                                       \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, ___x___, KC_CAPS, KC_NUM,  KC_INS,  KC_SCRL, KC_PAUS, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      ___x___, ___x___, ___x___, ___x___, ___x___, ___x___
// clang-format on

/**
 * \brief Navigation layer, with convenience one-hand shortcuts.
 *
 * Shortcuts on the left side for use with the mouse in the right hand.
 * Inverted T navigation cluster on the right side to combine with left side
 * home row mods.
 */
// clang-format off
#define NAV_split_3x5_3                                                                       \
    WS_PREV, RCS_TAB, LAUNCHR, CTL_TAB, WS_NEXT,  KC_DEL, KC_HOME,   NS_UP,  KC_END, KC_PGUP, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, SC_NTAB, ___x___, NS_LEFT, NS_DOWN, NS_RGHT, KC_PGDN, \
    SC_CLSE,  SC_CUT, SC_COPY, SC_PSTE, SC_NWIN, ___x___, ___x___, ___x___, ___x___, ___x___, \
                      ___x___, _______, ___x___, ___x___,    WNAV, ___x___
// clang-format on

/**
 * \brief Workspace navigation layers.
 *
 * Contains platform-dependent shortcuts for moving between virtual workspaces
 * and interacting with tiling window managers.
 */
// clang-format off
#define WNAV_split_3x5_3                                                                      \
    ___x___,    WS_7,    WS_8,    WS_9, ___x___, ___x___, WS_MPCI, WS_MPPR, WS_MPCD, ___x___, \
    ___x___,    WS_4,    WS_5,    WS_6, ___x___, ___x___, WS_MPSH, ___x___, WS_MPEX, ___x___, \
    ___x___,    WS_1,    WS_2,    WS_3, ___x___, ___x___, WS_FPRV,  WS_MOD, WS_FNXT, ___x___, \
                      KC_LSFT, ___x___, ___x___, ___x___, ___x___, _______
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_3                                                                      \
       GAME, ___x___,   MACOS, ___x___, RGB_TOG, RGB_TOG, ___x___,   MACOS, ___x___,    GAME, \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
      RESET, EEP_RST, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, EEP_RST,   RESET, \
                      ___x___, RGB_MOD,RGB_RMOD,RGB_RMOD, RGB_MOD, ___x___
// clang-format on


/** 
 * \brief Mouse emulation and pointer functions. 
 */
// clang-format off
#define POINT_split_3x5_3                                                                   \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    _______,  TD_DRG, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,  TD_DRG, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN1, ___x___
// clang-format on

/** 
 * \brief Extra layer for doubletap hold
 */
// clang-format off
#define EXT_split_3x5_3                                                                    \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    _______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, _______, \
                      ___x___, ___x___, ___x___, ___x___, ___x___, ___x___
// clang-format on