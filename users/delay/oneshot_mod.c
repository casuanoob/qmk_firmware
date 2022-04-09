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

#include "oneshot_mod.h"

void oneshot_mod_pre(oneshot_mod_state_t* state, uint16_t mod, uint16_t trigger,
                     uint16_t keycode, keyrecord_t* record) {
  if (keycode == trigger) {
    if (record->event.pressed) {
      // Trigger keydown.
      if (*state == ONESHOT_UP_UNQUEUED) {
        register_code(mod);
      }
      *state = ONESHOT_DOWN_UNUSED;
    } else {
      // Trigger keyup.
      switch (*state) {
        case ONESHOT_DOWN_UNUSED:
          // If we didn't use the mod while trigger was held, queue it.
          *state = ONESHOT_UP_QUEUED;
          break;
        case ONESHOT_DOWN_USED:
          // If we did use the mod while trigger was held, unregister it.
          *state = ONESHOT_UP_UNQUEUED;
          unregister_code(mod);
          break;
        default:
          break;
      }
    }
  } else {
    if (record->event.pressed) {
      if (is_oneshot_mod_cancel_key(keycode) && *state != ONESHOT_UP_UNQUEUED) {
        // Cancel oneshot on designated cancel keydown.
        *state = ONESHOT_UP_UNQUEUED;
        unregister_code(mod);
      }
    }
  }
}

void oneshot_mod_post(oneshot_mod_state_t* state, uint16_t mod,
                      uint16_t trigger, uint16_t keycode, keyrecord_t* record) {
  if (keycode != trigger && !record->event.pressed) {
    if (!is_oneshot_mod_ignore_key(keycode)) {
      // On non-ignored keyup, consider the oneshot used.
      switch (*state) {
        case ONESHOT_DOWN_UNUSED:
          *state = ONESHOT_DOWN_USED;
          break;
        case ONESHOT_UP_QUEUED:
          *state = ONESHOT_UP_UNQUEUED;
          unregister_code(mod);
          break;
        default:
          break;
      }
    }
  }
}
