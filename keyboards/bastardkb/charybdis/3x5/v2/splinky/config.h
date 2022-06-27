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

#include "config_common.h"

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP26, GP5, GP4, GP9 }
#define MATRIX_COL_PINS \
    { GP28, GP15, GP6, GP7, GP8 }

/* Handedness. */
//#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the adapter PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
#define SPLIT_HAND_PIN GP13
#define SPLIT_HAND_PIN_LOW_IS_LEFT // High -> right, Low -> left.

/* serial.c configuration (for split keyboard). */

// Uncommend for half duplex.
//#define SOFT_SERIAL_PIN GP1

// Full-duplex configuration.  Requires bodge wire from GP10 (bottom row on the
// Splinky) to the TRRS connector's second serial pin.  Also requires the use of
// a TRRS cable.
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP1  // USART TX pin.
#define SERIAL_USART_RX_PIN GP10 // USART RX pin.
#define SERIAL_USART_PIN_SWAP    // Auto-swap TX and RX on master to properly setup full-duplex.

#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* RGB settings. */
#define RGB_DI_PIN GP0

/* Falcon encoder (https://docs.qmk.fm/#/feature_encoders). */

// Available pins on the v2 adapter:
//  - GP27, GP29 (for < 4x6 only): extra col/row pin available exclusively on
//    3x5 and 3x6 (3x5 has both available, 3x6 only has GP29 available).
//  - GP18, GP19, GP20 (replaces SPI): used for SCK/MOSI/MISO.  Only available
//    if SPI is not used, which is typically the case on regular Charybdis
//    because the Falcon encoder is installed where the SPI device (trackball)
//    would be.
//  - GP14 (replaces trackball): used for Trackball SS.  Only available if SPI
//    is not used, which is typically the case on regular Charybdis because the
//    Falcon encoder is installed where the SPI device (trackball) would be.
//    Note: this only works if the half where the rotary encoder is installed is
//    primary.
//  - GP2, GP3 (replaces I2C): used for SDA/SCL.  Only available if I2C is not
//    used, which is typically the case on regular Charybdis because the Falcon
//    encoder is installed where the I2C device (trackpad) would be.
//  - GP10, GP11, GP12: unused pin from the Splinky bottom pinout row.  These
//    are not broken out on the v2 adapter, and require a bodge wire.

// Encoder R1 and R2.
#define ENCODERS_PAD_A \
    { GP18 }
#define ENCODERS_PAD_B \
    { GP19 }
#define ENCODER_RESOLUTION 2

// Uncomment if R1 and R2 are flipped.  (ie. if "clockwise" is actually
// "counter-clockwise".)
#define ENCODER_DIRECTION_FLIP

// Direct access pin for the encoder button.  Bridge PCB pads accordingly.  Use
// if encoder is not integrated with the key matrix.
#define DIP_SWITCH_PINS \
    { GP14 }

#if 0
/* SPI & PMW3360 settings. */
#    define SPI_DRIVER SPID0
#    define SPI_SCK_PIN GP18
#    define SPI_MOSI_PIN GP19
#    define SPI_MISO_PIN GP20
#    define PMW3360_CS_PIN GP14
#endif // 0

/* I2C & Cirque trackpad settings. */
//#define CIRQUE_PINNACLE_ADDR 0x2A
//#define I2C_DRIVER I2CD2
//#define I2C1_SCL_PIN GP2
//#define I2C1_SDA_PIN GP3
//#define I2C1_CLOCK_SPEED 400000
//#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
//#define SPLIT_POINTING_ENABLE
//#define POINTING_DEVICE_COMBINED
#undef POINTING_DEVICE_TASK_THROTTLE_MS
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

//#define POINTING_DEVICE_ROTATION_180
//#define POINTING_DEVICE_ROTATION_180_RIGHT

//#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_CONFIG_SYNC, RPC_ID_SYNC_STATE_KB
//#define SPLIT_MAX_CONNECTION_ERRORS 10

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
