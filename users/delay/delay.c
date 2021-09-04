#include QMK_KEYBOARD_H
#include "compose.h"
#include "delay.h"

#ifdef COMPOSE_ENABLE
/** Compose global state.  */
static compose_state_t compose_state = {0};

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
bool _handle_modifier_sequence(compose_state_t *state,
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
bool _handle_intl_compose_sequences(compose_state_t *state) {
  return _handle_modifier_sequence(state, KC_E, ALGR(KC_E)) ||
         _handle_modifier_sequence(state, KC_A, ALGR(KC_GRAVE)) ||
         _handle_modifier_sequence(state, KC_I, ALGR(KC_I)) ||
         _handle_modifier_sequence(state, KC_U, ALGR(KC_U)) ||
         _handle_modifier_sequence(state, KC_N, ALGR(KC_N));
}

__attribute__((weak)) void compose_keymap(compose_state_t *state) {}

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
#endif  // COMPOSE_ENABLE

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef COMPOSE_ENABLE
  if (!process_record_compose(&compose_state, keycode, record)) {
    return false;
  }
#endif  // COMPOSE_ENABLE
  return process_record_keymap(keycode, record);
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
#ifdef COMPOSE_ENABLE
  // Compose callback, used to handle compose sequence timeout.
  matrix_scan_compose(&compose_state);
#endif  // COMPOSE_ENABLE
  matrix_scan_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#ifdef COMPOSE_ENABLE
  keyboard_post_init_compose(&compose_state);
#endif  // COMPOSE_ENABLE
  keyboard_post_init_keymap();
}
