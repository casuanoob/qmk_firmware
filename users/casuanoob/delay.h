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
  // Oneshot mods.
  OS_LALT = QK_USER,
  OS_LCTL,
  OS_LGUI,
  OS_LSFT,
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
//void oneshot_locked_mods_changed_user_keymap(uint8_t mods);
void shutdown_user_keymap(void);
