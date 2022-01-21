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
#include "compose.h"
#include "config.h"
#include "delay.h"
#include "platform.h"

#ifdef RGB_MATRIX_ENABLE
#include "timer.h"
#endif  // RGB_MATRIX_ENABLE

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"
#endif  // RGB_MATRIX_ENABLE

#ifdef ONESHOT_MOD_ENABLE
#include "oneshot_mod.h"

typedef struct {
  oneshot_mod_state_t lalt;
  oneshot_mod_state_t lctl;
  oneshot_mod_state_t lgui;
  oneshot_mod_state_t lsft;
  oneshot_mod_state_t ralt;
} osm_state_t;
#endif  // ONESHOT_MOD_ENABLE

#ifdef COMPOSE_ENABLE
/** Compose global state. */
static compose_state_t g_compose_state = {0};

/**
 * \brief Handle a 2-keycodes sequence.
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
 * \brief Add support for foreign language characters, such as é, à, etc…
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
 * \brief This is where compose sequences are matched.
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

/**
 * \brief Do not shift `keycode` if only oneshot-shift is locked.
 *
 * This effectively suppresses the effect of oneshot-shift locked mod for some
 * keycodes, allowing for better typing experience in all caps (eg. for
 * identifier names in some programming language/coding style).
 */
#ifndef NO_ONESHOT_SHIFT_LOCKED_CODE
#define NO_ONESHOT_SHIFT_LOCKED_CODE(keycode)                  \
  {                                                            \
    if (record->event.pressed) {                               \
      if (get_oneshot_locked_mods() & MOD_MASK_SHIFT) {        \
        const uint8_t mod_shift = get_mods() & MOD_MASK_SHIFT; \
        unregister_mods(mod_shift);                            \
        register_code(keycode);                                \
        register_mods(mod_shift);                              \
      } else {                                                 \
        register_code(keycode);                                \
      }                                                        \
    } else {                                                   \
      unregister_code(keycode);                                \
    }                                                          \
    break;                                                     \
  }
#endif  // NO_ONESHOT_SHIFT_LOCKED_CODE

static bool process_record_user_internal(uint16_t keycode,
                                         keyrecord_t *record) {
#ifdef COMPOSE_ENABLE
  if (!process_record_compose(&g_compose_state, keycode, record)) {
    return false;
  }
#endif  // COMPOSE_ENABLE
  switch (keycode) {
    case MACOS:
      if (record->event.pressed) {
        toggle_macos();
      }
      break;
    case NS_1 ... NS_0:
      NO_ONESHOT_SHIFT_LOCKED_CODE(keycode - NS_1 + KC_1);
    case NS_BSLASH:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_BSLASH);
    case NS_COMMA:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_COMMA);
    case NS_DOT:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_DOT);
    case NS_GRAVE:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_GRAVE);
    case NS_QUOTE:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_QUOTE);
    case NS_LBRACKET:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_LBRC);
    case NS_RBRACKET:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_RBRC);
    case NS_SCOLON:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_SCOLON);
    case NS_SLASH:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_SLASH);
    case NS_UP:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_UP);
    case NS_DOWN:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_DOWN);
    case NS_LEFT:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_LEFT);
    case NS_RIGHT:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_RIGHT);
    case SC_CUT:
      process_record_cut(record);
      break;
    case SC_COPY:
      process_record_copy(record);
      break;
    case SC_PASTE:
      process_record_paste(record);
      break;
    case SC_PASTE_NO_FORMAT:
      process_record_paste_no_format(record);
      break;
    case SC_CLOSE:
      process_record_close(record);
      break;
    case SC_NEW_TAB:
      process_record_new_tab(record);
      break;
    case SC_NEW_WINDOW:
      process_record_new_window(record);
      break;
    case SC_SELECT_ALL:
      process_record_select_all(record);
      break;
    case WS_GOTO_1 ... WS_GOTO_0:
      process_record_space_goto_index(record, keycode - WS_GOTO_1);
    case WS_CYCLE_MODE:
      process_record_space_cycle_mode(record);
      break;
    case WS_FOCUS_PREVIOUS:
      process_record_space_focus_previous(record);
      break;
    case WS_FOCUS_NEXT:
      process_record_space_focus_next(record);
      break;
    case WS_GOTO_PREVIOUS:
      process_record_space_goto_previous(record);
      break;
    case WS_GOTO_NEXT:
      process_record_space_goto_next(record);
      break;
    case WS_MAIN_PANE_EXPAND:
      process_record_space_main_pane_expand(record);
      break;
    case WS_MAIN_PANE_SHRINK:
      process_record_space_main_pane_shrink(record);
      break;
    case WS_MAIN_PANE_COUNT_DECREASE:
      process_record_space_main_pane_count_decrease(record);
      break;
    case WS_MAIN_PANE_COUNT_INCREASE:
      process_record_space_main_pane_count_increase(record);
      break;
    case WS_MAIN_PANE_PROMOTE:
      process_record_space_main_pane_promote(record);
      break;
  }
  return process_record_user_keymap(keycode, record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ONESHOT_MOD_ENABLE
  static osm_state_t osm_state = {
      .lalt = ONESHOT_UP_UNQUEUED,
      .lctl = ONESHOT_UP_UNQUEUED,
      .lgui = ONESHOT_UP_UNQUEUED,
      .lsft = ONESHOT_UP_UNQUEUED,
      .ralt = ONESHOT_UP_UNQUEUED,
  };
  oneshot_mod_pre(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
  oneshot_mod_pre(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
  oneshot_mod_pre(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
  oneshot_mod_pre(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);
  oneshot_mod_pre(&osm_state.ralt, KC_RALT, OS_RALT, keycode, record);
#endif  // ONESHOT_MOD_ENABLE
  const bool result = process_record_user_internal(keycode, record);
#ifdef ONESHOT_MOD_ENABLE
  oneshot_mod_post(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
  oneshot_mod_post(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
  oneshot_mod_post(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
  oneshot_mod_post(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);
  oneshot_mod_post(&osm_state.ralt, KC_RALT, OS_RALT, keycode, record);
#endif  // ONESHOT_MOD_ENABLE
  return result;
}

__attribute__((weak)) bool process_record_user_keymap(uint16_t keycode,
                                                      keyrecord_t *record) {
  return true;
}

#ifdef RGB_MATRIX_ENABLE
/**
 * \brief Apply default/startup RGB matrix values.
 *
 * This is to replace the missing `rgb_matrix_reload_from_eeprom()`.
 */
void rgb_matrix_reset_noeeprom(void) {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv_noeeprom(RGB_MATRIX_STARTUP_HSV);
  rgb_matrix_set_speed_noeeprom(RGB_MATRIX_STARTUP_SPD);
}
#endif  // RGB_MATRIX_ENABLE

void matrix_scan_user(void) {
#ifdef COMPOSE_ENABLE
  // Compose callback, used to handle compose sequence timeout.
  matrix_scan_compose(&g_compose_state);
#endif  // COMPOSE_ENABLE
  matrix_scan_user_keymap();
}

__attribute__((weak)) void matrix_scan_user_keymap(void) {}

/** Called on layer change. */
layer_state_t layer_state_set_user(layer_state_t state) {
  return layer_state_set_user_keymap(state);
}

__attribute__((weak)) layer_state_t layer_state_set_user_keymap(
    layer_state_t state) {
  return state;
}

/**
 * Init the host platform (whether host is macOS or not).
 *
 * This relies on a macOS oddity to detect whether the host platform is macOS
 * or another system: macOS does not support some features (in this case,
 * numlock), so by manually setting numlock, and checking for its value, it's
 * possible to guess the host OS.
 */
static void _init_host_platform(void) {
  add_key(KC_NUM_LOCK);
  send_keyboard_report();
  set_is_macos(!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)));
  del_key(KC_NUM_LOCK);
  send_keyboard_report();
}

void keyboard_post_init_user(void) {
  _init_host_platform();
#ifdef COMPOSE_ENABLE
  keyboard_post_init_compose(&g_compose_state);
#endif  // COMPOSE_ENABLE
  keyboard_post_init_user_keymap();
}

__attribute__((weak)) void keyboard_post_init_user_keymap(void) {}

/**
 * \brief Called when a one-shot layer "lock" status changes.
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
  oneshot_locked_mods_changed_user_keymap(mods);
}

__attribute__((weak)) void oneshot_locked_mods_changed_user_keymap(
    uint8_t mods) {}

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
  shutdown_user_keymap();
}

__attribute__((weak)) void shutdown_user_keymap(void) {}
