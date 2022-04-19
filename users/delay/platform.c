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

#include "platform.h"

static void _process_record_space_shortcut(const keyrecord_t *record,
                                           uint16_t keycode) {
  const uint16_t keycode16 = LCTL(LOPT(keycode));
  if (record->event.pressed) {
    register_code16(keycode16);
  } else {
    unregister_code16(keycode16);
  }
}

void process_record_space_goto_previous(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_LEFT);
}

void process_record_space_goto_next(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_RIGHT);
}

void process_record_space_focus_previous(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_J);
}

void process_record_space_focus_next(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_K);
}

void process_record_space_main_pane_expand(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_L);
}

void process_record_space_main_pane_shrink(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_H);
}

void process_record_space_main_pane_count_increase(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_DOT);
}

void process_record_space_main_pane_count_decrease(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_COMM);
}

void process_record_space_main_pane_promote(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_ENT);
}

void process_record_space_cycle_mode(const keyrecord_t *record) {
  _process_record_space_shortcut(record, KC_SPACE);
}
