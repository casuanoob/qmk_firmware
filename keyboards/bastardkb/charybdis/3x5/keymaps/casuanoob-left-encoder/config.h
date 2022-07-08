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

// Caps Word config.
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Disable unused keycodes.
//#define NO_CHARYBDIS_KEYCODES

// Speed test
#define DEBUG_MATRIX_SCAN_RATE
//#define FORCE_NKRO

/* This is specific to Casuanoob's WIP blackpill charybdis 3x5 falcon encoder build.
* \ TODO remove this once DIP switch split transport and dual pin WS2812 driver are implemented
*/
#if defined(KEYBOARD_bastardkb_charybdis_3x5_blackpill) || defined(KEYBOARD_bastardkb_charybdis_4x6_blackpill)
    /* Override RGB settings. 
    * \brief 12 LEDs are added by the falcon PCB to the original 36
    */

    /* RGB settings. */
    #undef RGBLED_NUM 
    #undef RGBLED_SPLIT
    #define RGBLED_NUM 48
    #define RGBLED_SPLIT \
        { 30, 18 }
    /* RGB matrix support. */
    #undef DRIVER_LED_TOTAL
    #undef RGB_MATRIX_SPLIT
    #define DRIVER_LED_TOTAL RGBLED_NUM
    #define RGB_MATRIX_SPLIT RGBLED_SPLIT

    /* Define encoder pads. 
    * \brief Encoder pads wired to MISO and MOSI
    */
    #define ENCODER_DEFAULT_POS 0x3
    #define ENCODERS_PAD_A { A6 }
    #define ENCODERS_PAD_B { A7 }
    //Encoders right define is required to prevent the trackball SPI pins from being overridden
    #define ENCODERS_PAD_A_RIGHT {  }
    #define ENCODERS_PAD_B_RIGHT {  }
#endif // KEYBOARD_bastardkb_charybdis_3x5_blackpill || KEYBOARD_bastardkb_charybdis_4x6_blackpill