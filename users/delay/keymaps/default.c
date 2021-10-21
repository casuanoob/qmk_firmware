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
#include QMK_KEYBOARD_H
#include "keymaps/default.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"
#endif  // RGB_MATRIX_ENABLE

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif  // !MIN

static void _maybe_clear_oneshot_locked_mods(void) {
  const uint8_t locked_mods = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
  if (locked_mods) {
    // Clear any locked one-shot mod, if enabled.  The only one-shot layer in
    // this layout is the one-shot shift layer, so it is safe to clear all
    // locked mods.
    del_mods(locked_mods);
    clear_oneshot_locked_mods();
  }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ESC_SYM:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code(KC_ESC);
        } else {
          _maybe_clear_oneshot_locked_mods();
          unregister_code(KC_ESC);
        }
        // Do not continue with the default tap action if the LT was pressed or
        // released, but not held.
        return false;
      }
      break;
    case FX_ESCAPE:
      if (record->event.pressed) {
        register_code(KC_ESC);
      } else {
        _maybe_clear_oneshot_locked_mods();
        unregister_code(KC_ESC);
      }
      break;
    case KM_FIRST_DEFAULT_LAYER ... KM_LAST_DEFAULT_LAYER:
      if (record->event.pressed) {
        const uint8_t mods = mod_config(get_mods() | get_oneshot_mods());
#ifdef KEYMAP_DEFAULT_LITE
        // If ctrl is held, use the HR-less version of the layout.
        const uint8_t layer =
            keycode - KM_FIRST_DEFAULT_LAYER + LAYER_ALPHAS_FIRST;
#else
        // If ctrl is held, use the HR-less version of the layout.
        const uint8_t layer = keycode - KM_FIRST_DEFAULT_LAYER +
                              (mods & MOD_MASK_CTRL ? LAYER_NO_MODS_ALPHAS_FIRST
                                                    : LAYER_ALPHAS_FIRST);
#endif  // KEYMAP_DEFAULT_LITE
        if (mods & MOD_MASK_SHIFT) {
          // Permanently changes the layer if shifted.
          set_single_persistent_default_layer(layer);
        } else {
          // Temporarily changes the layer by default.
          default_layer_set((layer_state_t)1 << layer);
        }
      }
      break;
  }
  return true;
};

__attribute__((weak)) layer_state_t layer_state_set_keymap(
    layer_state_t state) {
  return state;
}

#if defined(RGB_MATRIX_ENABLE) && 0  // Disabled, but kept for example purposes.
/**
 * Called on layer change.
 *
 * This is called automatically by the QMK framework when the active layer
 * changes.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case LAYER_ALPHAS_FIRST ... LAYER_ALPHAS_LAST:
      rgb_matrix_reset_noeeprom();
      break;
    case LAYER_DEV:
    case LAYER_SYM:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
      rgb_matrix_sethsv_noeeprom(HSV_PINK);
      break;
  }
  return layer_state_set_keymap(state);
}

/**
 * Thin wrapper around rgb_matrix_set_color that takes a HSV instead of RGB,
 * and caps the value component to RGB_MATRIX_MAXIMUM_BRIGHTNESS if
 * `force_value` is `false`.  It uses the provided `v` otherwise.
 */
static void _rgb_matrix_sethsv_noeeprom(uint8_t index, uint8_t h, uint8_t s,
                                        uint8_t v, bool force_value) {
  const HSV hsv = {
      .h = h,
      .s = s,
      .v = force_value ? v : MIN(v, RGB_MATRIX_MAXIMUM_BRIGHTNESS),
  };
  const RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

/**
 * Called during every cycle.
 *
 * Per-key RGB configuration must go in this callback to be properly applied.
 */
void rgb_matrix_indicators_user(void) {
  switch (get_highest_layer(layer_state)) {
    case LAYER_NAV:
      _rgb_matrix_sethsv_noeeprom(22, HSV_YELLOW, /* force_value= */ true);
      _rgb_matrix_sethsv_noeeprom(25, HSV_YELLOW, /* force_value= */ true);
      _rgb_matrix_sethsv_noeeprom(26, HSV_YELLOW, /* force_value= */ true);
      _rgb_matrix_sethsv_noeeprom(28, HSV_YELLOW, /* force_value= */ true);
      break;
  }
}
#else   // !RGB_MATRIX_ENABLE
/**
 * Called on layer change.
 *
 * This is called automatically by the QMK framework when the active layer
 * changes.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
  return layer_state_set_keymap(state);
}
#endif  // RGB_MATRIX_ENABLE

#ifdef TAPPING_TERM_PER_KEY
/**
 * Define key-specific `TAPPING_TERM`.
 *
 * Tunes the `TAPPING_TERM` for both layer-taps and Home Row mods.  For Home Row
 * mods, this implementation assumes GACS home row order.
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX: {
      const uint8_t layer = (keycode >> 0x8) & 0xf;
      if (layer == LAYER_PTR) {
        return TAPPING_TERM + 150;
      }
      break;
    }
    case QK_MOD_TAP ... QK_MOD_TAP_MAX: {
      // Use the mod to distinguish between Home Row mod since the actual
      // alpha layout can vary.
      const uint8_t mod = mod_config((keycode >> 0x8) & 0x1f);
      if (mod & MOD_MASK_GUI) {
        // Pinkies.
        return TAPPING_TERM + 125;
      }
      if (mod & MOD_MASK_ALT) {
        // Ring fingers.
        return TAPPING_TERM + 100;
      }
      if (mod & MOD_MASK_CTRL) {
        // Middle fingers.
        return TAPPING_TERM;
      }
      if (mod & MOD_MASK_SHIFT) {
        // Index fingers.
        return TAPPING_TERM + 25;
      }
      break;
    }
  }
  return TAPPING_TERM;
}
#endif  // TAPPING_TERM_PER_KEY

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  return keycode != OSM_SFT && keycode != OSL_EXP;
}
#endif  // TAPPING_FORCE_HOLD_PER_KEY

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  // Only on Mod-tap (ie. not on Layer-tap).
  return QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX;
}
#endif  // PERMISSIVE_HOLD_PER_KEY

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  // Only on Layer-tap (ie. not on Mod-tap).
  return QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX;
}
#endif  // HOLD_ON_OTHER_KEY_PRESS_PER_KEY
