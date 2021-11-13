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
 * Custom keycodes.
 *
 * Use `SAFE_RANGE_KEYMAP` for keymap specific codes, instead of `SAFE_RANGE`.
 */
enum keycodes_user {
#ifdef VIA_ENABLE
  COMPOSE = USER00,
#else
  COMPOSE = SAFE_RANGE,
#endif
  // Custom version of these keycodes to add special effects.
  FX_RESET,  // Changes LEDs color, if any, before entering reset mode.
  // Custom version of these keycodes that can't be shifted.
  NS_0,
  NS_1,
  NS_2,
  NS_3,
  NS_4,
  NS_5,
  NS_6,
  NS_7,
  NS_8,
  NS_9,
  NS_BSLASH,
  NS_COMMA,
  NS_DOT,
  NS_GRAVE,
  NS_LBRACKET,
  NS_RBRACKET,
  NS_SCOLON,
  NS_SLASH,
  SAFE_RANGE_KEYMAP,
};

// Shorthands.
#define FX_RST FX_RESET

#define NS_BSLS NS_BSLASH
#define NS_COMM NS_COMMA
#define NS_GRV NS_GRAVE
#define NS_LBRC NS_LBRACKET
#define NS_RBRC NS_RBRACKET
#define NS_SCLN NS_SCOLON
#define NS_SLSH NS_SLASH

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `process_record_*` callback is necessary for each keymap
 * to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `matrix_scan_keymap_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void matrix_scan_keymap(void);

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `keyboard_post_init_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void keyboard_post_init_keymap(void);

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `eeconfig_init_*` callback is necessary for each keymap
 * to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void eeconfig_init_keymap(void);

#ifdef COMPOSE_ENABLE
/**
 * Use this function to add support for more composition on a per-keymap basis.
 */
void compose_keymap(compose_state_t *state);
#endif  // COMPOSE_ENABLE

#ifdef RGB_MATRIX_ENABLE
/**
 * Apply default/startup RGB matrix values.
 *
 * This is to replace the missing `rgb_matrix_reload_from_eeprom()`.
 */
void rgb_matrix_reset_noeeprom(void);
#endif  // RGB_MATRIX_ENABLE

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `oneshot_locked_mods_changed_*` callback is necessary
 * for each keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void oneshot_locked_mods_changed_keymap(uint8_t mods);
