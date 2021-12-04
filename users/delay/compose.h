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

#include "quantum.h"

/** \brief Default compose timeout at 1000ms. */
#ifndef COMPOSE_TERM
#define COMPOSE_TERM 1000
#endif  // COMPOSE_TERM

/** \brief The size of the compose queue.  Defauts to 2 keycodes. */
#ifndef COMPOSE_KEYCODE_QUEUE_SIZE
#define COMPOSE_KEYCODE_QUEUE_SIZE 2
#endif

/**
 * \brief The state required to handle composing.
 */
typedef struct {
  uint16_t keycode_queue[COMPOSE_KEYCODE_QUEUE_SIZE];
  int keycode_queue_index;
  bool is_composing;
  uint16_t timer;
} compose_state_t;

/**
 * \brief Initialize the compose engine.
 *
 * Should be called in `keyboard_post_init_user()`.
 */
void keyboard_post_init_compose(compose_state_t *state);

/**
 * \brief Process the input keycode.
 *
 * Should be called in `process_record_user(uint16_t, keyrecord_t)`.
 */
bool process_record_compose(compose_state_t *state, uint16_t keycode,
                            keyrecord_t *record);

/**
 * \brief Trigger compose on timeout.
 *
 * Should be called in `matrix_scan_user()`.
 */
void matrix_scan_compose(compose_state_t *state);

/**
 * \brief Create a sequence of keycode used for composition.
 *
 * This macro ensures that the array is of the correct size.
 */
#define COMPOSE_SEQUENCE(...) \
  ((uint16_t[COMPOSE_KEYCODE_QUEUE_SIZE]){__VA_ARGS__})

/**
 * \brief Whether the compose queue contains all of the specified keycodes, in
 * order.
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
 * \brief User level callback.
 *
 * Use this function to add support for more composition on a per-user/-keymap
 * basis.
 */
void compose_user(compose_state_t *state);
