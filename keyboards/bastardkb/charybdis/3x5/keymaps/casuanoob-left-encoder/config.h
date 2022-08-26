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

// Disable unused keycodes.
//#define NO_CHARYBDIS_KEYCODES

// Speed test
#define DEBUG_MATRIX_SCAN_RATE
//#define FORCE_NKRO

/* This is specific to Casuanoob's WIP blackpill charybdis 3x5 falcon encoder build.
* \ TODO remove this once DIP switch split transport and dual pin WS2812 driver are implemented
*/
#if defined(KEYBOARD_bastardkb_charybdis_3x5_blackpill) || defined(KEYBOARD_bastardkb_charybdis_4x6_blackpill)
    /* Serial baudrate configuration*/
    #define SERIAL_USART_SPEED 921600

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

/* This is specific to Casuanoob's WIP Splinky charybdis 3x5 falcon encoder build.
* \ 
*/
#if defined(KEYBOARD_bastardkb_charybdis_3x5_v2_splinky)
    // To use the handedness pin, resistors need to be installed on the adapter PCB.
    // If so, uncomment the following code, and undefine MASTER_RIGHT above.
    #undef MASTER_RIGHT
    #define SPLIT_HAND_PIN GP13
    #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.
    // Full-duplex configuration.  Requires bodge wire from GP10 (bottom row on the
    // Splinky) to the TRRS connector's second serial pin.  Also requires the use of
    // a TRRS cable.
    //#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
    //#define SERIAL_USART_TX_PIN GP1  // USART TX pin.
    //#define SERIAL_USART_RX_PIN GP10 // USART RX pin.
    //#define SERIAL_USART_PIN_SWAP    // Auto-swap TX and RX on master to properly setup full-duplex.
    //uncomment for full duplex

    /* Serial baudrate configuration*/
    //#define SERIAL_USART_SPEED 921600
    #define SERIAL_USART_SPEED 345600 // PIO half-duplex max stable speed 460800
    /* CRC. */
    #define CRC8_USE_TABLE
    #define CRC8_OPTIMIZE_SPEED
    // Encoder R1 and R2.
    #define ENCODERS_PAD_A \
        { GP18 }
    #define ENCODERS_PAD_B \
        { GP19 }
    #define ENCODER_RESOLUTION 4
    #define ENCODERS_PAD_A_RIGHT {  }
    #define ENCODERS_PAD_B_RIGHT {  }
    #define ENCODER_RESOLUTIONS_RIGHT {  }
    #define ENCODER_DEFAULT_POS 0x3

    // Uncomment if R1 and R2 are flipped.  (ie. if "clockwise" is actually
    // "counter-clockwise".)
    #define ENCODER_DIRECTION_FLIP

    // Direct access pin for the encoder button.  Bridge PCB pads accordingly.  Use
    // if encoder is not integrated with the key matrix.
    #define DIP_SWITCH_PINS \
        { GP14 }
    #define DIP_SWITCH_PINS_RIGHT { NO_PIN }
#endif // KEYBOARD_bastardkb_charybdis_3x5_v2_splinky

//#define COMBO_COUNT 5
#define SERIAL_DEBUG

#define CHARYBDIS_CONFIG_SYNC
#define MOUSE_EXTENDED_REPORT
#define PMW33XX_LIFTOFF_DISTANCE 0x15