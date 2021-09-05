/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> @0xcharly
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
#include "delay.h"

/**
 * Resets the compose state, clears the queue.
 */
void _compose_reset(compose_state_t *state) {
  for (int i = 0; i < COMPOSE_KEYCODE_QUEUE_SIZE; ++i) {
    state->keycode_queue[i] = KC_NO;
  }
  state->keycode_queue_index = 0;
  state->is_composing = false;
  state->timer = 0;
}

/**
 * Process the queue.
 *
 * Resets the compose state regardless of whether a compose sequence was
 * matched.
 */
void _compose_process_queue(compose_state_t *state) {
  compose_user(state);
  _compose_reset(state);
}

/**
 * Push a new keycode to the queue.
 */
void _compose_push_keycode(compose_state_t *state, uint16_t keycode) {
  state->keycode_queue[state->keycode_queue_index++] = keycode;
  state->timer = timer_read();
}

/**
 * Whether the compose queue is full.
 */
bool _compose_queue_is_full(compose_state_t *state) {
  return state->keycode_queue_index >= COMPOSE_KEYCODE_QUEUE_SIZE;
}

/**
 * Handle a keypress when composing is active.
 *
 * If the keycode is eligible, push it into the compose queue.  When the queue
 * is full, trigger composing (see `_compose_process_queue(…)`).
 */
bool _compose_handle_keypress(compose_state_t *state, uint16_t keycode,
                              keyrecord_t *record) {
  // Get the base keycode of a mod or layer tap key.
  switch (keycode) {
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      // Early return if this has not been considered tapped yet.
      if (record->tap.count == 0) {
        return true;
      }
      keycode = keycode & 0xff;
  }
  // Force compose on Enter.
  if (keycode == KC_ENT) {
    _compose_process_queue(state);
    return false;
  }
  // Process eligible keycodes (ie. basic keycodes and mods).
  switch (keycode) {
    case KC_A ... KC_CAPSLOCK:
    case QK_MODS ... QK_MODS_MAX:
      // Shift keycode if necessary, ignores other mods.
      if (mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        keycode = S(keycode);
      }
      // Push keycode into the queue, and compose if the queue is full.
      _compose_push_keycode(state, keycode);
      if (_compose_queue_is_full(state)) {
        _compose_process_queue(state);
      }
      return false;
  }
  return true;
}

void keyboard_post_init_compose(compose_state_t *state) {
  _compose_reset(state);
}

bool process_record_compose(compose_state_t *state, uint16_t keycode,
                            keyrecord_t *record) {
  switch (keycode) {
    case COMPOSE:
      if (record->event.pressed) {
        state->is_composing = true;
        state->timer = timer_read();
      }
      return false;
    default:
      if (state->is_composing && record->event.pressed) {
        return _compose_handle_keypress(state, keycode, record);
      }
      break;
  }
  return true;
}

void matrix_scan_compose(compose_state_t *state) {
  if (state->is_composing &&
      timer_elapsed(state->timer) > (uint16_t)COMPOSE_TERM) {
    _compose_process_queue(state);
  }
}

bool compose_queue_equal(compose_state_t *state,
                         uint16_t keycodes[COMPOSE_KEYCODE_QUEUE_SIZE]) {
  for (int i = 0; i < COMPOSE_KEYCODE_QUEUE_SIZE; ++i) {
    if (state->keycode_queue[i] != keycodes[i]) {
      return false;
    }
  }
  return true;
}

/**
 * This is where compose combos should defined.
 */
__attribute__((weak)) void compose_user(compose_state_t *state) {}
