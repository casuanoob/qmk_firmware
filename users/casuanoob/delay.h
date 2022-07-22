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

#include "quantum.h"
#if defined (KEYBOARD_bastardkb_charybdis)
#   include "charybdis.h"
#elif defined (KEYBOARD_bastardkb_dilemma)
#   include "dilemma.h"
#endif

/**
 * \brief Custom keycodes.
 *
 * Use `SAFE_RANGE_KEYMAP` for keymap specific codes, instead of `SAFE_RANGE`.
 */
enum keycodes_user {
#if defined (KEYBOARD_bastardkb_charybdis)
  KEYCODE_USER_BEGIN = CHARYBDIS_SAFE_RANGE,
# elif defined (KEYBOARD_bastardkb_dilemma)
  KEYCODE_USER_BEGIN = DILEMMA_SAFE_RANGE,
# elif defined(VIA_ENABLE)
  KEYCODE_USER_BEGIN = USER00,
# else
  KEYCODE_USER_BEGIN = SAFE_RANGE,
# endif 
  // Custom version of these keycodes that don't shift when only oneshot shift
  // mod is locked.
  NS_1 = KEYCODE_USER_BEGIN,
  NS_2,
  NS_3,
  NS_4,
  NS_5,
  NS_6,
  NS_7,
  NS_8,
  NS_9,
  NS_0,
  NS_BSLASH,
  NS_COMMA,
  NS_DOT,
  NS_GRAVE,
  NS_QUOTE,
  NS_LBRACKET,
  NS_RBRACKET,
  NS_SCOLON,
  NS_SLASH,
  NS_MINUS,

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
  REPEAT,
  SAFE_RANGE_KEYMAP,
};

#define SC_CUT LCTL(KC_X)
#define SC_COPY LCTL(KC_C)
#define SC_PASTE LCTL(KC_V)
#define SC_PASTE_NO_FORMAT LCTL(S(KC_V))
#define SC_LAUNCHER LGUI(KC_TAB)
#define SC_CLOSE LCTL(KC_W)
#define SC_NEW_TAB LCTL(KC_T)
#define SC_NEW_WINDOW LCTL(KC_N)
#define WS_PREVIOUS LCTL(LGUI(KC_LEFT))
#define WS_NEXT LCTL(LGUI(KC_RIGHT))

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
#define NS_MINS NS_MINUS
#define SC_PSTE SC_PASTE
#define SC_CLSE SC_CLOSE
#define SC_NTAB SC_NEW_TAB
#define SC_NWIN SC_NEW_WINDOW
#define SC_SELA SC_SELECT_ALL
#define WS_PREV WS_PREVIOUS
#define LAUNCHR SC_LAUNCHER

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for
 * userspace-defined keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * new versions of these callbacks are necessary for each keymap
 * to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
bool process_record_user_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user_keymap(void);
layer_state_t layer_state_set_user_keymap(layer_state_t state);
void keyboard_post_init_user_keymap(void);
void oneshot_locked_mods_changed_user_keymap(uint8_t mods);
void shutdown_user_keymap(void);

#ifdef RGB_MATRIX_ENABLE
/**
 * \brief Apply default/startup RGB matrix values.
 *
 * This is to replace the missing `rgb_matrix_reload_from_eeprom()`.
 */
void rgb_matrix_reset(void);
#endif  // RGB_MATRIX_ENABLE

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `oneshot_locked_mods_changed_*` callback is necessary
 * for each keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void oneshot_locked_mods_changed_keymap(uint8_t mods);
