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
 * \brief Supported platforms.
 *
 * Used to adjust the binding of some keycodes at runtime (eg. cut/copy/paste).
 */
typedef enum {
  UNKNOWN = 0,
  LINUX,
  MACOS,
  WINDOWS,
} platform_t;

/** \brief Return the platform currently targeted. */
platform_t get_platform(void);

/** \brief Set the platform to target. */
void set_platform(platform_t platform);

/** \brief Set the platform to target.  Do not persist the change to EEPROM. */
void set_platform_noeeprom(platform_t platform);

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
  FX_PLATFORM_LINUX,
  FX_PLATFORM_MACOS,
  FX_PLATFORM_WINDOWS,
  // Cut/copy/paste keycodes that change at runtime based on the current
  // platform.  See `get_platform()` and `set_platform*(…)`.
  PL_CUT,    // ^X or Cmd+X based on the platform.
  PL_COPY,   // ^C or Cmd+C based on the platform.
  PL_PASTE,  // ^V or Cmd+V based on the platform.
  // Custom version of these keycodes that don't shift when only oneshot shift
  // mod is locked.
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
  // Custom version of up/down/left/right keycodes that can't be shifted.
  NS_UP,
  NS_DOWN,
  NS_LEFT,
  NS_RIGHT,
  SAFE_RANGE_KEYMAP,
};

// Shorthands.
#define FX_PL_L FX_PLATFORM_LINUX
#define FX_PL_M FX_PLATFORM_MACOS
#define FX_PL_W FX_PLATFORM_WINDOWS

#define PL_PSTE PL_PASTE

#define NS_BSLS NS_BSLASH
#define NS_COMM NS_COMMA
#define NS_GRV NS_GRAVE
#define NS_LBRC NS_LBRACKET
#define NS_RBRC NS_RBRACKET
#define NS_SCLN NS_SCOLON
#define NS_SLSH NS_SLASH
#define NS_RGHT NS_RIGHT

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
