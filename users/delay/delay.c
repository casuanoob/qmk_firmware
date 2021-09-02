#include QMK_KEYBOARD_H
#include "compose.h"
#include "delay.h"

#ifdef COMPOSE_ENABLE
/** Compose global state.  */
static compose_state_t compose_state = {0};

__attribute__((weak)) void compose_keymap(compose_state_t *state) {}

/**
 * This is where compose sequences are matched.
 *
 * Checks the compose queue for known sequences.  If found, sends the
 * appropriate unicode character(s) as hexadecimal string.
 */
void compose_user(compose_state_t *state) {
  if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, KC_A))) {
    send_unicode_string("á");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, S(KC_A)))) {
    send_unicode_string("Á");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, KC_O))) {
    send_unicode_string("ó");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, S(KC_O)))) {
    send_unicode_string("Ó");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, KC_E))) {
    send_unicode_string("é");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, S(KC_E)))) {
    send_unicode_string("É");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, KC_U))) {
    send_unicode_string("ú");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, S(KC_U)))) {
    send_unicode_string("Ú");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, KC_I))) {
    send_unicode_string("í");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_E, S(KC_I)))) {
    send_unicode_string("Í");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, KC_A))) {
    send_unicode_string("ä");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, S(KC_A)))) {
    send_unicode_string("Ä");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, KC_O))) {
    send_unicode_string("ö");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, S(KC_O)))) {
    send_unicode_string("Ö");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, KC_E))) {
    send_unicode_string("ë");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, S(KC_E)))) {
    send_unicode_string("Ë");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, KC_U))) {
    send_unicode_string("ü");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, S(KC_U)))) {
    send_unicode_string("Ü");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, KC_I))) {
    send_unicode_string("ï");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_U, S(KC_I)))) {
    send_unicode_string("Ï");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, KC_A))) {
    send_unicode_string("â");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, S(KC_A)))) {
    send_unicode_string("Â");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, KC_O))) {
    send_unicode_string("ô");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, S(KC_O)))) {
    send_unicode_string("Ô");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, KC_E))) {
    send_unicode_string("ê");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, S(KC_E)))) {
    send_unicode_string("Ê");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, KC_U))) {
    send_unicode_string("û");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, S(KC_U)))) {
    send_unicode_string("Û");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, KC_I))) {
    send_unicode_string("î");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_I, S(KC_I)))) {
    send_unicode_string("Î");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, KC_A))) {
    send_unicode_string("à");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, S(KC_A)))) {
    send_unicode_string("À");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, KC_O))) {
    send_unicode_string("ò");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, S(KC_O)))) {
    send_unicode_string("Ò");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, KC_E))) {
    send_unicode_string("è");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, S(KC_E)))) {
    send_unicode_string("È");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, KC_U))) {
    send_unicode_string("ù");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, S(KC_U)))) {
    send_unicode_string("Ù");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, KC_I))) {
    send_unicode_string("ì");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_A, S(KC_I)))) {
    send_unicode_string("Ì");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_O, KC_E))) {
    send_unicode_string("œ");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_O, S(KC_E)))) {
    send_unicode_string("Œ");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_C, KC_C))) {
    send_unicode_string("ç");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_C, S(KC_C)))) {
    send_unicode_string("Ç");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_T, KC_T))) {
    send_unicode_string("…");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_T, KC_F))) {
    send_unicode_string("(╯°□°)╯︵ ┻━┻");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_F, KC_T))) {
    send_unicode_string("┬─┬ノ( º _ ºノ)");
  } else if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_S, KC_H))) {
    send_unicode_string("¯\\_(ツ)_/¯");
  } else {
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
