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

#ifdef MCU_RP
#    undef MASTER_RIGHT
#    define SPLIT_HAND_PIN GP29
#endif

// Full-duplex configuration.  Requires bodge wire from GP0 to the TRRS connector
// Also requires the use of a TRRS cable.
#    undef SOFT_SERIAL_PIN
#    define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#    define SERIAL_USART_TX_PIN GP1  // USART TX pin.
#    define SERIAL_USART_RX_PIN GP0 // USART RX pin.
#    define SERIAL_USART_PIN_SWAP    // Auto-swap TX and RX on master to properly setup full-duplex.
#    define SERIAL_USART_SPEED (1024 * 1280)
//uncomment for full duplex

/* OLED config. */
//#define I2C1_CLOCK_SPEED 400000
#define I2C1_CLOCK_SPEED 1000000
//#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define OLED_DISPLAY_HEIGHT 128
#define OLED_TIMEOUT 60000 //test, oled should sleep after 1 minute
#define OLED_BRIGHTNESS 128

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE

#define MOUSE_EXTENDED_REPORT
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_TAPPING_TERM 100
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

#define TUCKY_THUMBS

#define DEBUG_MATRIX_SCAN_RATE