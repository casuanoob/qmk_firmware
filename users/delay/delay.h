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

/**
 * \brief Custom keycodes.
 *
 * Use `SAFE_RANGE_KEYMAP` for keymap specific codes, instead of `SAFE_RANGE`.
 */
enum keycodes_user {
#ifdef VIA_ENABLE
  COMPOSE = USER00,
#else
  COMPOSE = SAFE_RANGE,
#endif
  // Keycodes to change the target platform (changes some keycodes at runtime).
  MACOS,
  // Cut/copy/paste shortcuts that change at runtime based on the current
  // platform.
  SC_CUT,              // ^X or Cmd+X based on the platform.
  SC_COPY,             // ^C or Cmd+C based on the platform.
  SC_PASTE,            // ^V or Cmd+V based on the platform.
  SC_PASTE_NO_FORMAT,  // Shifted ^V or Cmd+V based on the platform.
  // Other platform-specific shortcuts.
  SC_CLOSE,       // ^W or Cmd+W based on the platform.
  SC_NEW_TAB,     // ^T or Cmd+T based on the platform.
  SC_NEW_WINDOW,  // ^N or Cmd+N based on the platform.
  SC_SELECT_ALL,  // ^A or Cmd+A based on the platform.
  // Custom version of these keycodes that don't shift when only oneshot shift
  // mod is locked.
  NS_1,
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
  OS_RALT,
  // Workspace navigation.
  WS_GOTO_1,
  WS_GOTO_2,
  WS_GOTO_3,
  WS_GOTO_4,
  WS_GOTO_5,
  WS_GOTO_6,
  WS_GOTO_7,
  WS_GOTO_8,
  WS_GOTO_9,
  WS_GOTO_0,
  WS_CYCLE_MODE,
  WS_FOCUS_PREVIOUS,
  WS_FOCUS_NEXT,
  WS_GOTO_PREVIOUS,
  WS_GOTO_NEXT,
  WS_MAIN_PANE_COUNT_DECREASE,
  WS_MAIN_PANE_COUNT_INCREASE,
  WS_MAIN_PANE_EXPAND,
  WS_MAIN_PANE_SHRINK,
  WS_MAIN_PANE_PROMOTE,
  SAFE_RANGE_KEYMAP,
};

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
#define SC_CLSE SC_CLOSE
#define SC_NTAB SC_NEW_TAB
#define SC_NWIN SC_NEW_WINDOW
#define SC_SELA SC_SELECT_ALL
#define WS_1 WS_GOTO_1
#define WS_2 WS_GOTO_2
#define WS_3 WS_GOTO_3
#define WS_4 WS_GOTO_4
#define WS_5 WS_GOTO_5
#define WS_6 WS_GOTO_6
#define WS_7 WS_GOTO_7
#define WS_8 WS_GOTO_8
#define WS_9 WS_GOTO_9
#define WS_0 WS_GOTO_0
#define WS_MOD WS_CYCLE_MODE
#define WS_FPRV WS_FOCUS_PREVIOUS
#define WS_FNXT WS_FOCUS_NEXT
#define WS_PREV WS_GOTO_PREVIOUS
#define WS_NEXT WS_GOTO_NEXT
#define WS_MPCD WS_MAIN_PANE_COUNT_DECREASE
#define WS_MPCI WS_MAIN_PANE_COUNT_INCREASE
#define WS_MPEX WS_MAIN_PANE_EXPAND
#define WS_MPSH WS_MAIN_PANE_SHRINK
#define WS_MPPR WS_MAIN_PANE_PROMOTE

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `process_record_*` callback is necessary for each keymap
 * to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `matrix_scan_keymap_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void matrix_scan_keymap(void);

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `keyboard_post_init_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void keyboard_post_init_keymap(void);

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `eeconfig_init_*` callback is necessary for each keymap
 * to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void eeconfig_init_keymap(void);

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `shutdown_*` callback is necessary for each keymap to
 * add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void shutdown_keymap(void);

#ifdef COMPOSE_ENABLE
/**
 * \brief Augment COMPOSE composition at the keymap level.
 */
void compose_keymap(compose_state_t *state);
#endif  // COMPOSE_ENABLE

#ifdef RGB_MATRIX_ENABLE
/**
 * \brief Apply default/startup RGB matrix values.
 *
 * This is to replace the missing `rgb_matrix_reload_from_eeprom()`.
 */
void rgb_matrix_reset_noeeprom(void);
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
