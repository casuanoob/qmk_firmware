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

// Split keyboards {{{

#ifdef SPLIT_KEYBOARD
// Enable split keyboards extensions, in order to sync state between the halves.
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#endif  // SPLIT_KEYBOARD

// }}}
// Keymap {{{

/** \brief Only uses 16 bits for layers.  Limits available layers to 16.  */
#define LAYER_STATE_16BIT

/** \brief Tri Layer settings NAV SYM NUM  */
#define TRI_LAYER_LOWER_LAYER 9
#define TRI_LAYER_UPPER_LAYER 10
#define TRI_LAYER_ADJUST_LAYER 11

// One-Shot keys {{{

#ifndef NO_ACTION_ONESHOT
/**
 * \brief Time (in ms) before the one shot key is released.
 */
#define ONESHOT_TIMEOUT 1500
#endif  // NO_ACTION_ONESHOT

/**
 * \brief Configure the global tapping term (default: 200ms).
 *
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 */
#ifndef TAPPING_TERM
#define TAPPING_TERM 175
#endif  // !TAPPING_TERM

#ifdef COMBO_ENABLE
/**
 * \brief Combo configurations
 */
#define COMBO_TERM 20
#define COMBO_TERM_PER_COMBO
#define COMBO_STRICT_TIMER
#define COMBO_ONLY_FROM_LAYER 1
#define COMBO_SHOULD_TRIGGER
#endif  // COMBO_ENABLE

// RGB {{{

#ifdef RGB_MATRIX_ENABLE
#ifdef __arm__
// Enable all animations on ARM boards since they have plenty of memory
// available for it.
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#else
// Disable control of RGB matrix by keycodes (must use firmware implementation
// to control the feature).
#define RGB_MATRIX_DISABLE_KEYCODES
#endif

// Limit maximum brightness to prevent power spikes from tripping fuses.
//#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 72
// limit in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#undef RGB_MATRIX_LED_FLUSH_LIMIT
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 

// Rainbow swirl as startup mode.
#ifndef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#endif  // ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON

// Slow swirl at startup.
#undef RGB_MATRIX_DEFAULT_SPD
#define RGB_MATRIX_DEFAULT_SPD 32

// Startup values.
#undef RGB_MATRIX_DEFAULT_HUE
#define RGB_MATRIX_DEFAULT_HUE 0
#undef RGB_MATRIX_DEFAULT_SAT
#define RGB_MATRIX_DEFAULT_SAT 255
#undef RGB_MATRIX_DEFAULT_VAL
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#undef RGB_MATRIX_DEFAULT_HSV
#define RGB_MATRIX_DEFAULT_HSV \
  RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
#endif  // RGB_MATRIX_ENABLE