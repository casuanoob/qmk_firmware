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

#ifdef TAP_DANCE_ENABLE
#ifndef DELAY_TD_TAPPING_TERM
/** TODO(delay) */
#define DELAY_TD_TAPPING_TERM TAPPING_TERM + 125
#endif  // DELAY_TD_TAPPING_TERM

/** TODO(delay) */
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_DOUBLE_TAP,
  TD_HOLD,
  TD_DOUBLE_HOLD,
} td_state_t;

#ifdef TD_ONESHOT_SHIFT_ENABLE
/** TODO(delay) */
typedef struct {
  const uint8_t single_hold_layer;
  const uint8_t double_hold_layer;
  td_state_t td_state;
} oneshot_shift_td_state_t;

/** TODO(delay) */
void oneshot_shift_td_on_dance_finished(qk_tap_dance_state_t *state,
                                        void *user_data);

/** TODO(delay) */
void oneshot_shift_td_on_dance_reset(qk_tap_dance_state_t *state,
                                     void *user_data);
#endif  // TD_ONESHOT_SHIFT_ENABLE

/** TODO(delay) */
enum tap_dances_user {
#ifdef TD_ONESHOT_SHIFT_ENABLE
  TD_ONESHOT_SHIFT,  // Custom OSM Shift with layer on hold.
#endif               // TD_ONESHOT_SHIFT_ENABLE
};
#endif  // TAP_DANCE_ENABLE
