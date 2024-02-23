/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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
#define RGB_MATRIX_DEFAULT_VAL 128
// Limit maximum brightness to prevent power spikes from tripping fuses.
//#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 192
// Turn off LEDs after 2 minutes inactivity.
#define RGB_MATRIX_TIMEOUT 120000

/* Encoder defines. */
#define ENCODER_RESOLUTION { 2 }

/* Split Comms. */
//#define SELECT_SOFT_SERIAL_SPEED 1
#define SPLIT_TRANSPORT_MIRROR
//#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_ACTIVITY_ENABLE
//#define SPLIT_LED_STATE_ENABLE
//#define SPLIT_MODS_ENABLE
//#define SPLIT_WPM_ENABLE

/* Cirque defines. */
#undef MOUSE_EXTENDED_REPORT
#define CIRQUE_PINNACLE_SPI_DIVISOR 8
#define CIRQUE_PINNACLE_SPI_CS_PIN POINTING_DEVICE_CS_PIN
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

//Via
#define DYNAMIC_KEYMAP_LAYER_COUNT 16

//Quantum Painter
#define LCD_CS_PIN GP13
#define LCD_DC_PIN GP12
#define LCD_RST_PIN GP11
#define LCD_SPI_DIVISOR 0
#define LCD_SPI_MODE 3
#define QUANTUM_PAINTER_TASK_THROTTLE 10
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT RGB_MATRIX_TIMEOUT
#define BACKLIGHT_PIN GP15
#define BACKLIGHT_PWM_DRIVER PWMD7
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define BACKLIGHT_LEVELS 12
#define BACKLIGHT_DEFAULT_ON true
#define BACKLIGHT_DEFAULT_LEVEL 7
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE	134400
//#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS true
