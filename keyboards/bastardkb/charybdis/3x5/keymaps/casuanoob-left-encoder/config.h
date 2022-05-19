/**
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

// Trackball angle adjustment.
#undef ROTATIONAL_TRANSFORM_ANGLE
#define ROTATIONAL_TRANSFORM_ANGLE -25
#define POINTING_DEVICE_INVERT_X

// Custom DPI.
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1000
#define CHARYBDIS_MINIMUM_SNIPING_DPI 500

/* Override RGB settings. 
 * \brief 12 LEDs are added by the falcon PCB to the original 36
*/
#undef RGBLED_NUM 
#undef RGBLED_SPLIT
#define RGBLED_NUM 48
#define RGBLED_SPLIT \
    { 30, 18 }

/* Define encoder pads. 
 * \brief Encoder pads wired to MISO and MOSI
*/
#define ENCODER_DEFAULT_POS 0x3
#define ENCODERS_PAD_A { A6 }
#define ENCODERS_PAD_B { A7 }
//Encoders right define is required to prevent the trackball SPI pins from being overridden
#define ENCODERS_PAD_A_RIGHT { B12 } //completely unused pin
#define ENCODERS_PAD_B_RIGHT { B13 } //completely unused pin

// Disable unused keycodes.
//#define NO_CHARYBDIS_KEYCODES