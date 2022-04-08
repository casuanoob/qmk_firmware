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

//#ifdef SPLIT_KEYBOARD
//#ifndef SPLIT_HAND_PIN
/**
 * \brief Flash each side with `-bl dfu-split-*` to set handedness in memory eg.
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
#undef SPLIT_HAND_PIN
#undef MASTER_RIGHT
#define EE_HANDS
#define SPLIT_USB_DETECT
//#endif  // SPLIT_HAND_PIN

// Enable split keyboards extensions, in order to sync state between the halves.
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR
//#endif  // SPLIT_KEYBOARD

// }}}
// Keymap {{{

#ifdef DELAY_KEYMAP_SPLIT36_HOMEROW_LITE
/** \brief Only uses 8 bits for layers.  Limits available layers to 8.  */
#define LAYER_STATE_8BIT
#else
/** \brief Only uses 16 bits for layers.  Limits available layers to 16.  */
#define LAYER_STATE_16BIT
#endif  // DELAY_KEYMAP_SPLIT36_HOMEROW_LITE

// }}}
// Via {{{
#ifdef VIA_ENABLE
/* VIA configuration. */
#define DYNAMIC_KEYMAP_LAYER_COUNT 9

#ifdef VIAL_ENABLE
/** Vial-specific configuration. */

#define VIAL_KEYBOARD_UID \
  { 0x44, 0x9F, 0x26, 0x53, 0xD9, 0x7B, 0x72, 0x4F }
#define VIAL_UNLOCK_COMBO_ROWS \
  { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS \
  { 0, 0 }

/** Disable unused vial features. */

// In addition to RGB Matrix effects, VialRGB also provides direct LED control
// with a script running on your computer.  Remove to reenable.
#define VIALRGB_NO_DIRECT
#endif  // VIAL_ENABLE
#endif  // VIA_ENABLE

// }}}
// One-Shot keys {{{

#ifndef NO_ACTION_ONESHOT
/**
 * \brief Tapping this number of times holds the key until tapped once again.
 *
 * https://beta.docs.qmk.fm/using-qmk/software-features/one_shot_keys
 */
#define ONESHOT_TAP_TOGGLE 2

/**
 * \brief Time (in ms) before the one shot key is released.
 *
 * https://beta.docs.qmk.fm/using-qmk/software-features/one_shot_keys
 */
#define ONESHOT_TIMEOUT 1500
#endif  // NO_ACTION_ONESHOT

// }}}
// Tap dances {{{

/**
 * \brief Configure the global tapping term (default: 200ms).
 *
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 * See
 *   https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 *   https://precondition.github.io/home-row-mods#tapping-term
 */
#ifndef TAPPING_TERM
#define TAPPING_TERM 175
#endif  // !TAPPING_TERM

/**
 * \brief Enable rapid switch from tap to hold.
 *
 * Note that a side-effect of this setting is to disable auto-repeat when
 * pressing key twice, except for one-shot keys.
 *
 * See
 *   https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-force-hold
 *   https://precondition.github.io/home-row-mods#tapping-force-hold
 */
#define TAPPING_FORCE_HOLD_PER_KEY

#ifdef DELAY_KEYMAP_SPLIT36_HOMEROW
/**
 * \brief Customize the TAPPING_TERM for specific keys.
 */
#define TAPPING_TERM_PER_KEY

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
 * \brief Faster layer-tap hold trigger.
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
 * \brief Faster tap-hold trigger.
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
 * \brief Prevent normal rollover on alphas from accidentally triggering mods.
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
 * \brief Prevent same-hand mod misfires.
 *
 * The last mod-tap hold will be converted to the corresponding mod-tap tap if
 * another key on the same hand is tapped during the hold, unless a key on the
 * other hand is tapped first.
 *
 * See precondition.github.io/home-row-mods#rolled-modifiers-cancellation.
 */
#define BILATERAL_COMBINATIONS 500
#endif  // DELAY_KEYMAP_SPLIT36_HOMEROW

// }}}
// RGB {{{

#ifdef RGB_MATRIX_ENABLE
#ifdef __arm__
// Enable all animations on ARM boards since they have plenty of memory
// available for it.
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

// Limit maximum brightness to keep power consumption reasonable, and avoid
// disconnects.
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 64

// Rainbow swirl as startup mode.
#ifndef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#endif  // ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON

// Slow swirl at startup.
#define RGB_MATRIX_STARTUP_SPD 32

// Startup values.
#define RGB_MATRIX_STARTUP_HUE 0
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_STARTUP_HSV \
  RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif  // RGB_MATRIX_ENABLE

// }}}

// Tacking on custom pointer dpi settings {{{

#ifdef POINTING_DEVICE_ENABLE
#    ifndef CHARYBDIS_MINIMUM_DEFAULT_DPI
#        define CHARYBDIS_MINIMUM_DEFAULT_DPI 700
#    endif  // CHARYBDIS_MINIMUM_DEFAULT_DPI

#    ifndef CHARYBDIS_MINIMUM_SNIPING_DPI
#        define CHARYBDIS_MINIMUM_SNIPING_DPI 200
#    endif  // CHARYBDIS_MINIMUM_SNIPER_MODE_DPI

// Fixed DPI for drag-scroll.
#    ifndef CHARYBDIS_DRAGSCROLL_DPI
#        define CHARYBDIS_DRAGSCROLL_DPI 100
#    endif  // CHARYBDIS_DRAGSCROLL_DPI

#    ifndef CHARYBDIS_DRAGSCROLL_BUFFER_SIZE
#        define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 6
#    endif  // !CHARYBDIS_DRAGSCROLL_BUFFER_SIZE

#    ifndef CHARYBDIS_POINTER_ACCELERATION_FACTOR
#        define CHARYBDIS_POINTER_ACCELERATION_FACTOR 24
#    endif  // !CHARYBDIS_POINTER_ACCELERATION_FACTOR
#endif  // POINTING_DEVICE_ENABLE && !NO_CHARYBDIS_KEYCODES

// }}}

// Defines for Locking caps and other {{{

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

// }}}

#define FORCE_NKRO