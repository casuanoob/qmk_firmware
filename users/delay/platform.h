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

bool is_macos(void);
void toggle_macos(void);
void set_is_macos(bool is_macos);

void process_record_cut(const keyrecord_t *record);
void process_record_copy(const keyrecord_t *record);
void process_record_paste(const keyrecord_t *record);
void process_record_paste_no_format(const keyrecord_t *record);

void process_record_select_all(const keyrecord_t *record);
void process_record_close(const keyrecord_t *record);

void process_record_space_goto_index(const keyrecord_t *record, uint8_t index);
void process_record_space_goto_previous(const keyrecord_t *record);
void process_record_space_goto_next(const keyrecord_t *record);
void process_record_space_focus_previous(const keyrecord_t *record);
void process_record_space_focus_next(const keyrecord_t *record);
void process_record_space_main_pane_expand(const keyrecord_t *record);
void process_record_space_main_pane_shrink(const keyrecord_t *record);
void process_record_space_main_pane_count_increase(const keyrecord_t *record);
void process_record_space_main_pane_count_decrease(const keyrecord_t *record);
void process_record_space_main_pane_promote(const keyrecord_t *record);
void process_record_space_cycle_mode(const keyrecord_t *record);
