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
#include "compose.h"
#include "config.h"
#include "delay.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"
#endif  // RGB_MATRIX_ENABLE

/**
 * User specific config.
 *
 * Currently contains:
 *   - The targeted platform (used to adjust some keycodes at runtime).
 */
typedef union {
  uint32_t raw;
  struct {
    platform_t platform : 2;
  } __attribute__((packed));
} eeconfig_user_t;

/** User configuration global state. */
static eeconfig_user_t g_eeconfig_user = {0};

/** Set the value of `config` from EEPROM. */
static void _read_eeconfig_user_from_eeprom(eeconfig_user_t *config) {
  config->raw = eeconfig_read_user();
}

/** Persist the value of `config` to EEPROM. */
static void _write_eeconfig_user_to_eeprom(eeconfig_user_t *config) {
  eeconfig_update_user(config->raw);
}

static platform_t _eeconfig_user_get_platform(eeconfig_user_t *eeconfig_user) {
  return eeconfig_user->platform;
}

static void _eeconfig_user_set_platform(eeconfig_user_t *eeconfig_user,
                                        platform_t platform) {
  eeconfig_user->platform = platform;
}

static void _eeconfig_user_set_platform_and_save_to_eeprom(
    eeconfig_user_t *eeconfig_user, platform_t platform) {
  _eeconfig_user_set_platform(&g_eeconfig_user, platform);
  _write_eeconfig_user_to_eeprom(&g_eeconfig_user);
}

platform_t get_platform(void) {
  return _eeconfig_user_get_platform(&g_eeconfig_user);
}

void set_platform(platform_t platform) {
  _eeconfig_user_set_platform_and_save_to_eeprom(&g_eeconfig_user, platform);
}

void set_platform_noeeprom(platform_t platform) {
  _eeconfig_user_set_platform(&g_eeconfig_user, platform);
}

#ifdef COMPOSE_ENABLE
/** Compose global state. */
static compose_state_t g_compose_state = {0};

/**
 * Handle a 2-keycodes sequence.
 *
 * Checks whether the first, unmodded, keycode is the key is equal to
 * `prefix_modifier_keycode`.  If so, sends `actual_modifier_keycode` followed
 * by the second, unchanged, keycode in the queue.
 *
 * Note that mods are temporarily disabled for sending `actual_modifier_keycode`
 * to allow for shorthands such as "AA" to send "À".
 * For example, consider the following:
 *
 *   _handle_modifier_sequence(state, KC_A, ALGR(KC_GRAVE));
 *
 * With this mapping, the sequence `{ COMPOSE, S(KC_A), S(KC_A) }` prints "À" by
 * sending `ALGR(KC_A)` followed by `S(KC_A)`.  If mods were not disabled, it
 * would send `S(ALGR(KC_A))` first, which would not be interpreted as an intl
 * sequence prefix by the host system.
 *
 * Note that this function only looks at the first 2 keycodes in the queue, and
 * ignores the rest.  It's also a no-op if the queue is not large enough (less
 * than 2 in size).
 */
static bool _handle_modifier_sequence(compose_state_t *state,
                                      uint8_t prefix_modifier_keycode,
                                      uint16_t actual_modifier_keycode) {
#if COMPOSE_KEYCODE_QUEUE_SIZE >= 2
  if (state->keycode_queue[0] == KC_NO || state->keycode_queue[1] == KC_NO) {
    return false;
  }
  const uint8_t unshifted_first_keycode = state->keycode_queue[0] & 0xff;
  if (unshifted_first_keycode != prefix_modifier_keycode) {
    return false;
  }
  // Temporary disable all mods to send the modifier keycode.
  const uint16_t mods = mod_config(get_mods() | get_oneshot_mods());
  clear_mods();
  tap_code16(actual_modifier_keycode);
  set_mods(mods);
  // Sends the composed keycode.
  tap_code16(state->keycode_queue[1]);
  return true;
#else   // COMPOSE_KEYCODE_QUEUE_SIZE < 2
  return false;
#endif  // COMPOSE_KEYCODE_QUEUE_SIZE >= 2
}

/**
 * Add support for foreign language characters, such as é, à, etc…
 *
 * Supported sequences are:
 *   e [letter] -> AltGr-e [letter] -> acute (eg., á)
 *   a [letter] -> AltGr-` [letter] -> grave (eg., è)
 *   i [letter] -> AltGr-i [letter] -> circumflex (eg., ô)
 *   u [letter] -> AltGr-u [letter] -> umlaut or dieresis (eg., ï)
 *   n [letter] -> AltGr-n [letter] -> tilde (eg.,  ñ)
 *
 * Also adds support for uppercase shorthands, ie. "AA" and "aA" both produce
 * "À", "eA" and "EA" produce "Á", etc…
 */
static bool _handle_intl_compose_sequences(compose_state_t *state) {
  return _handle_modifier_sequence(state, KC_E, ALGR(KC_E)) ||
         _handle_modifier_sequence(state, KC_A, ALGR(KC_GRAVE)) ||
         _handle_modifier_sequence(state, KC_I, ALGR(KC_I)) ||
         _handle_modifier_sequence(state, KC_U, ALGR(KC_U)) ||
         _handle_modifier_sequence(state, KC_N, ALGR(KC_N));
}

/**
 * This is where compose sequences are matched.
 *
 * Checks the compose queue for known sequences.  If found, sends the
 * appropriate unicode character(s) as hexadecimal string.
 */
void compose_user(compose_state_t *state) {
  if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_D, KC_D))) {
    tap_code16(ALGR(KC_SCOLON));
  } else if (!_handle_intl_compose_sequences(state)) {
    compose_keymap(state);
  }
}

__attribute__((weak)) void compose_keymap(compose_state_t *state) {}
#endif  // COMPOSE_ENABLE

#ifndef NO_SHIFT_CODE
#define NO_SHIFT_CODE(keycode)                                           \
  {                                                                      \
    if (record->event.pressed) {                                         \
      const uint8_t mod_shift = mod_config(get_mods()) & MOD_MASK_SHIFT; \
      if (mod_shift) {                                                   \
        del_mods(mod_shift);                                             \
        register_code(keycode);                                          \
        add_mods(mod_shift);                                             \
      } else {                                                           \
        register_code(keycode);                                          \
      }                                                                  \
    } else {                                                             \
      unregister_code(keycode);                                          \
    }                                                                    \
    break;                                                               \
  }
#endif  // NO_SHIFT_CODE

static void _process_platform_update(platform_t platform, keyrecord_t *record,
                                     eeconfig_user_t *config) {
  if (record->event.pressed) {
    _eeconfig_user_set_platform_and_save_to_eeprom(config, platform);
  }
}

static void _process_platform_shortcut(uint16_t keycode, keyrecord_t *record,
                                       eeconfig_user_t *eeconfig_user) {
  const uint16_t keycode16 = _eeconfig_user_get_platform(eeconfig_user) == MACOS
                                 ? LGUI(keycode)
                                 : LCTL(keycode);
  if (record->event.pressed) {
    register_code16(keycode16);
  } else {
    unregister_code16(keycode16);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef COMPOSE_ENABLE
  if (!process_record_compose(&g_compose_state, keycode, record)) {
    return false;
  }
#endif  // COMPOSE_ENABLE
  switch (keycode) {
    case FX_PLATFORM_LINUX:
      _process_platform_update(LINUX, record, &g_eeconfig_user);
      break;
    case FX_PLATFORM_MACOS:
      _process_platform_update(MACOS, record, &g_eeconfig_user);
      break;
    case FX_PLATFORM_WINDOWS:
      _process_platform_update(WINDOWS, record, &g_eeconfig_user);
      break;
    case NS_0:
      NO_SHIFT_CODE(KC_0);
    case NS_1:
      NO_SHIFT_CODE(KC_1);
    case NS_2:
      NO_SHIFT_CODE(KC_2);
    case NS_3:
      NO_SHIFT_CODE(KC_3);
    case NS_4:
      NO_SHIFT_CODE(KC_4);
    case NS_5:
      NO_SHIFT_CODE(KC_5);
    case NS_6:
      NO_SHIFT_CODE(KC_6);
    case NS_7:
      NO_SHIFT_CODE(KC_7);
    case NS_8:
      NO_SHIFT_CODE(KC_8);
    case NS_9:
      NO_SHIFT_CODE(KC_9);
    case NS_BSLASH:
      NO_SHIFT_CODE(KC_BSLASH);
    case NS_COMMA:
      NO_SHIFT_CODE(KC_COMMA);
    case NS_DOT:
      NO_SHIFT_CODE(KC_DOT);
    case NS_GRAVE:
      NO_SHIFT_CODE(KC_GRAVE);
    case NS_LBRACKET:
      NO_SHIFT_CODE(KC_LBRC);
    case NS_RBRACKET:
      NO_SHIFT_CODE(KC_RBRC);
    case NS_SCOLON:
      NO_SHIFT_CODE(KC_SCOLON);
    case NS_SLASH:
      NO_SHIFT_CODE(KC_SLASH);
    case PL_CUT:
      _process_platform_shortcut(KC_X, record, &g_eeconfig_user);
      break;
    case PL_COPY:
      _process_platform_shortcut(KC_C, record, &g_eeconfig_user);
      break;
    case PL_PASTE:
      _process_platform_shortcut(KC_V, record, &g_eeconfig_user);
      break;
  }
  return process_record_keymap(keycode, record);
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

void matrix_scan_user(void) {
#ifdef COMPOSE_ENABLE
  // Compose callback, used to handle compose sequence timeout.
  matrix_scan_compose(&g_compose_state);
#endif  // COMPOSE_ENABLE
  matrix_scan_keymap();
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

void keyboard_post_init_user(void) {
  g_eeconfig_user.raw = eeconfig_read_user();
#ifdef COMPOSE_ENABLE
  keyboard_post_init_compose(&g_compose_state);
#endif  // COMPOSE_ENABLE
  keyboard_post_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

#ifdef RGB_MATRIX_ENABLE
/**
 * Apply default/startup RGB matrix values.
 *
 * This is to replace the missing `rgb_matrix_reload_from_eeprom()`.
 */
void rgb_matrix_reset_noeeprom(void) {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv_noeeprom(RGB_MATRIX_STARTUP_HSV);
  rgb_matrix_set_speed_noeeprom(RGB_MATRIX_STARTUP_SPD);
}
#endif  // RGB_MATRIX_ENABLE

/**
 * Called when a one-shot layer "lock" status changes.
 *
 * This is called automatically by the QMK framework when a one-shot layer is
 * activated and deactivated.
 * The only one-shot layer in this layout is the one-shot shift layer.  Turns
 * the RGBs solid blue when this layer is activated, and back to default when
 * deactivated.
 */
void oneshot_locked_mods_changed_user(uint8_t mods) {
#ifdef RGB_MATRIX_ENABLE
  if (mods & MOD_MASK_SHIFT) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  } else if (!mods) {
    rgb_matrix_reset_noeeprom();  // Load default values.
  }
#endif  // RGB_MATRIX_ENABLE
  oneshot_locked_mods_changed_keymap(mods);
}

void oneshot_locked_mods_changed_keymap(uint8_t mods) {}

void eeconfig_init_user(void) {
  g_eeconfig_user.raw = 0;
  _read_eeconfig_user_from_eeprom(&g_eeconfig_user);
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_mode(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv(RGB_MATRIX_STARTUP_HSV);
  rgb_matrix_set_speed(RGB_MATRIX_STARTUP_SPD);
#endif  // RGB_MATRIX_ENABLE
  eeconfig_init_keymap();
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(1);
  rgblight_setrgb_red();
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_set_color_all(RGB_RED);
  rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
#ifdef OLED_ENABLE
  oled_off();
#endif  // OLED_ENABLE
  shutdown_keymap();
}

__attribute__((weak)) void shutdown_keymap(void) {}
