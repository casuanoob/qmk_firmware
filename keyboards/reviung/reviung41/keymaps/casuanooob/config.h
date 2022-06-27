/* Copyright 2021 @Ciutadellla
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
#define RGBLIGHT_LAYERS
#ifdef RGB_DI_PIN
    // /*== all animations enable ==*/
    //#define RGBLIGHT_ANIMATIONS
    // /*== or choose animations ==*/
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
#endif

#define TAPPING_TERM 150
/**
 * \brief Tapping this number of times holds the key until tapped once again.
 *
 * https://beta.docs.qmk.fm/using-qmk/software-features/one_shot_keys
 */
#undef ONESHOT_TAP_TOGGLE
#define ONESHOT_TAP_TOGGLE 1
// Caps Word config.
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD