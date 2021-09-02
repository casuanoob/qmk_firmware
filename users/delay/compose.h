#pragma once

#include QMK_KEYBOARD_H

/** Default compose timeout at 1000ms. */
#ifndef COMPOSE_TERM
#define COMPOSE_TERM 1000
#endif  // COMPOSE_TERM

/** The size of the compose queue.  Defauts to 2 keycodes. */
#ifndef COMPOSE_KEYCODE_QUEUE_SIZE
#define COMPOSE_KEYCODE_QUEUE_SIZE 2
#endif

/**
 * The state required to handle composing.
 */
typedef struct {
  uint16_t keycode_queue[COMPOSE_KEYCODE_QUEUE_SIZE];
  int keycode_queue_index;
  bool is_composing;
  uint16_t timer;
} compose_state_t;

/**
 * Initialize the compose engine.
 *
 * Should be called in `keyboard_post_init_user()`.
 */
void keyboard_post_init_compose(compose_state_t *state);

/**
 * Process the input keycode.
 *
 * Should be called in `process_record_user(uint16_t, keyrecord_t)`.
 */
bool process_record_compose(compose_state_t *state, uint16_t keycode,
                            keyrecord_t *record);

/**
 * Trigger compose on timeout.
 *
 * Should be called in `matrix_scan_user()`.
 */
void matrix_scan_compose(compose_state_t *state);

/**
 * Create a sequence of keycode used for composition.
 *
 * This macro ensures that the array is of the correct size.
 */
#define COMPOSE_SEQUENCE(...) \
  ((uint16_t[COMPOSE_KEYCODE_QUEUE_SIZE]){__VA_ARGS__})

/**
 * Whether the compose queue contains all of the specified keycodes, in order.
 *
 * `COMPOSE_SEQUENCE` can be used to create the second argument to this
 * function, eg.
 *
 *     if (compose_queue_equal(state, COMPOSE_SEQUENCE(KC_QUOT, KC_E))) {
 *       send_unicode_string("é");
 *     }
 */
bool compose_queue_equal(compose_state_t *state,
                         uint16_t keycodes[COMPOSE_KEYCODE_QUEUE_SIZE]);

/**
 * Use this function to add support for more composition on a per-user/-keymap
 * basis.
 */
void compose_user(compose_state_t *state);
