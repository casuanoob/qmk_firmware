/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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

#define VENDOR_ID 0xA8F8
#define PRODUCT_ID 0x1832
#define DEVICE_VER 0x0001
#define MANUFACTURER Bastard Keyboards

/* Key matrix configuration. */

// Rows are doubled-up.
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DIODE_DIRECTION ROW2COL

/* Disable action features. */
#define NO_ACTION_MACRO     // Disable old-style macro handling.
#define NO_ACTION_FUNCTION  // Disable old-style function handling.

// Trackball angle adjustment.
#define ROTATIONAL_TRANSFORM_ANGLE -25

/* RGB settings. */

#define RGBLED_NUM 35
#define RGBLED_SPLIT \
  { 18, 17 }

/* RGB matrix support. */
#ifdef RGB_MATRIX_ENABLE
#define SPLIT_TRANSPORT_MIRROR
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_SPLIT RGBLED_SPLIT
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_KEYPRESSES
#endif
