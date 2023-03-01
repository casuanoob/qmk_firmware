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

#include "config.h"
#include "quantum.h"

#ifdef TAP_DANCE_ENABLE

/**
 * Tap-dance possible state.  Supports:
 *   - single tap
 *   - double tap
 *   - hold
 *   - double hold (ie. double tap and hold)
 */
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_DOUBLE_TAP,
  TD_TRIPLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_HOLD,
  TD_TRIPLE_HOLD,
} td_state_t;

/** One-shot shift tap-dance state. */
typedef struct {
  td_state_t td_state;
} oneshot_shift_td_state_t;

/** Tap-dance `on_dance_finished_fn` callback for one-shot shift implementation.
 */
void oneshot_shift_td_on_dance_finished(qk_tap_dance_state_t *state,
                                        void *user_data);

/** Tap-dance `on_dance_reset_fn` callback for one-shot shift implementation. */
void oneshot_shift_td_on_dance_reset(qk_tap_dance_state_t *state,
                                     void *user_data);

/** Tap-dance keycodes. */
enum tap_dances_user {
  TD_ONESHOT_SHIFT,  // Custom OSM Shift with layer on hold.
};
#endif  // TAP_DANCE_ENABLE