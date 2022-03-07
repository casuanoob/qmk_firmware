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

typedef enum {
  ONESHOT_UP_UNQUEUED = 0,
  ONESHOT_UP_QUEUED,
  ONESHOT_DOWN_UNUSED,
  ONESHOT_DOWN_USED,
} oneshot_mod_state_t;

void oneshot_mod_pre(oneshot_mod_state_t* state, uint16_t mod, uint16_t trigger,
                     uint16_t keycode, keyrecord_t* record);

void oneshot_mod_post(oneshot_mod_state_t* state, uint16_t mod,
                      uint16_t trigger, uint16_t keycode, keyrecord_t* record);

bool is_oneshot_mod_cancel_key(uint16_t keycode);
bool is_oneshot_mod_ignore_key(uint16_t keycode);
