/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> @0xcharly
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

/* General configuration. */

/**
 * Only uses 16 bits for layers.  Limits available layers to 16.
 */
#define LAYER_STATE_16BIT

/* Split keyboards. */

#ifdef SPLIT_KEYBOARD
/**
 * Flash each side with `-bl dfu-split-{left,right}` to set handedness in memory
 * eg.
 *
 *     `qmk flash -bl dfu-split-left -kb <keyboard> -km delay`
 *     `qmk flash -bl dfu-split-right -kb <keyboard> -km delay`
 *
 * The handedness needs only be set once.  The actual firmware image is
 * unchanged.  This means that even though the commands above will keep working,
 * the flashing process can be simplified by using the same flash command for
 * both halves once the handedness has been set once to EEPROM, ie.
 *
 *     `qmk flash -kb <keyboard> -km delay`
 */
#define EE_HANDS

// Left is primary.
#undef MASTER_RIGHT
#define MASTER_LEFT

// Enable split keyboards extensions, in order to sync state between the halves.
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#endif  // SPLIT_KEYBOARD

/* RGB. */

#ifdef RGB_MATRIX_ENABLE
// Unload all animations but the one used for idle, reduces memory footprint.
#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_VAL
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_CYCLE_ALL
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_HUE_BREATHING
#define DISABLE_RGB_MATRIX_HUE_PENDULUM
#define DISABLE_RGB_MATRIX_HUE_WAVE
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

// Disable control of RGB matrix by keycodes (must use firmware implementation
// to control the feature).
#define RGB_MATRIX_DISABLE_KEYCODES

// Limit maximum brightness to keep power consumption reasonable, and avoid
// disconnects.
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 64

// Rainbow swirl as startup mode.
#undef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT

// Slow swirl at startup.
#define RGB_MATRIX_STARTUP_SPD 32

// Startup values.
#define RGB_MATRIX_STARTUP_HUE 0
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_STARTUP_HSV \
  RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif  // RGB_MATRIX_ENABLE

#ifndef NO_ACTION_ONESHOT
/* One-Shot keys. */

/**
 * Tapping this number of times holds the key until tapped once again.
 * https://beta.docs.qmk.fm/using-qmk/software-features/one_shot_keys
 */
#define ONESHOT_TAP_TOGGLE 2

/**
 * Time (in ms) before the one shot key is released.
 * https://beta.docs.qmk.fm/using-qmk/software-features/one_shot_keys
 */
#define ONESHOT_TIMEOUT 1500
#endif  // NO_ACTION_ONESHOT

/* Tap dances. */

/**
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 * See
 *   https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 *   https://precondition.github.io/home-row-mods#tapping-term
 */
#ifndef TAPPING_TERM
#define TAPPING_TERM 175
#endif  // TAPPING_TERM

/**
 * Customize the TAPPING_TERM for specific keys.
 */
#define TAPPING_TERM_PER_KEY

/**
 * Enable rapid switch from tap to hold.  Disable auto-repeat when pressing key
 * twice, except for one-shot keys.
 *
 * See
 *   https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-force-hold
 *   https://precondition.github.io/home-row-mods#tapping-force-hold
 */
#define TAPPING_FORCE_HOLD_PER_KEY

/*
 * Tap-or-Hold decision modes.
 *
 * Note that the following flags behave differently when combined (ie. when 2 or
 * more are enabled).
 *
 * See bit.ly/tap-or-hold for a visual explanation of the following tap-or-hold
 * decision modes.
 */

/**
 * Faster tap-hold trigger.
 *
 * Without `PERMISSIVE_HOLD`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 e🠕 Mod(a)🠕 ➞ ae
 * With `PERMISSIVE_HOLD`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 e🠕 Mod(a)🠕 ➞ Mod+e
 *
 * https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#permissive-hold
 *
 * See precondition.github.io/home-row-mods#permissive-hold.
 *
 * NOTE: `PERMISIVE_HOLD_PER_KEY` is used to enable this only on mod-tap keys
 * (not on layer-tap keys).
 */
#define PERMISSIVE_HOLD_PER_KEY

/**
 * Faster layer-tap hold trigger.
 *
 * Without `HOLD_ON_OTHER_KEY_PRESS`, within `TAPPING_TERM`:
 *     LT(2, a)🠗 e🠗 LT(2, a)🠕 e🠕 ➞ ae
 * With `HOLD_ON_OTHER_KEY_PRESS`, within `TAPPING_TERM`:
 *     LT(2, a)🠗 e🠗 LT(2, a)🠕 e🠕 ➞ <mapping of e on layer>
 *
 * https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#hold-on-other-key-press
 */
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

/**
 * Prevent normal rollover on alphas from accidentally triggering mods.
 *
 * Ignores key presses that interrupt a mod-tap.  Must-have for Home Row mod.
 *
 * Without `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ Mod+e
 * With `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ ae
 *
 * https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#ignore-mod-tap-interrupt
 *
 * See https://precondition.github.io/home-row-mods#ignore-mod-tap-interrupt.
 */
#define IGNORE_MOD_TAP_INTERRUPT

/**
 * The last mod-tap hold will be converted to the corresponding mod-tap tap if
 * another key on the same hand is tapped during the hold, unless a key on the
 * other hand is tapped first.
 *
 * See precondition.github.io/home-row-mods#rolled-modifiers-cancellation.
 */
#define BILATERAL_COMBINATIONS 500
