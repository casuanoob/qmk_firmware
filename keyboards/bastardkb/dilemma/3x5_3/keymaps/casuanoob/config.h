/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/* RGB stuff. */
// Change the default brightness.
#undef RGB_MATRIX_DEFAULT_VAL
#define RGB_MATRIX_DEFAULT_VAL 192
// Limit maximum brightness to prevent power spikes from tripping fuses.
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 192

/* Split Comms. */
#define SELECT_SOFT_SERIAL_SPEED 1
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_LED_STATE_ENABLE
//#define SPLIT_MODS_ENABLE
//#define SPLIT_WPM_ENABLE

/* Cirque defines. */
#define MOUSE_EXTENDED_REPORT
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_TAPPING_TERM 100
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

/* Dilemma DPI config. */
#define DILEMMA_MINIMUM_DEFAULT_DPI 200

/* Userspace keymap casuanoob/split34 option for when thumbs are tucky */
#define TUCKY_THUMBS

//debug stuff
#define DEBUG_MATRIX_SCAN_RATE
#define SERIAL_DEBUG

/* Encoder defines */
#define ENCODERS_PAD_A { GP25 }
#define ENCODERS_PAD_B { GP24 }
#define ENCODER_RESOLUTIONS { 2 }

//Via
#define DYNAMIC_KEYMAP_LAYER_COUNT 16