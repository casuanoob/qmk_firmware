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

#include "config.h"
#include "delay.h"
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#endif  // RGB_MATRIX_ENABLE

#ifdef ONESHOT_MOD_ENABLE
#include "oneshot_mod.h"

typedef struct {
  oneshot_mod_state_t lalt;
  oneshot_mod_state_t lctl;
  oneshot_mod_state_t lgui;
  oneshot_mod_state_t lsft;
} osm_state_t;
#endif  // ONESHOT_MOD_ENABLE

/**
 * \brief Do not shift `keycode` if only oneshot-shift is locked.
 *
 * This effectively suppresses the effect of oneshot-shift locked mod for some
 * keycodes, allowing for better typing experience in all caps (eg. for
 * identifier names in some programming language/coding style).
 */
#ifndef NO_ONESHOT_SHIFT_LOCKED_CODE
#    define NO_ONESHOT_SHIFT_LOCKED_CODE(keycode)                          \
        {                                                                  \
            if (record->event.pressed) {                                   \
                if (get_oneshot_locked_mods() & MOD_MASK_SHIFT) {          \
                    const uint8_t mod_shift = get_mods() & MOD_MASK_SHIFT; \
                    unregister_mods(mod_shift);                            \
                    register_code(keycode);                                \
                    register_mods(mod_shift);                              \
                } else {                                                   \
                    register_code(keycode);                                \
                }                                                          \
            } else {                                                       \
                unregister_code(keycode);                                  \
            }                                                              \
            break;                                                         \
        }
#endif // NO_ONESHOT_SHIFT_LOCKED_CODE

static bool process_record_user_internal(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NS_1 ... NS_0:
            NO_ONESHOT_SHIFT_LOCKED_CODE(keycode - NS_1 + KC_1);
        case NS_BSLS:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_BSLS);
        case NS_COMMA:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_COMMA);
        case NS_DOT:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_DOT);
        case NS_GRAVE:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_GRAVE);
        case NS_QUOTE:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_QUOTE);
        case NS_LBRACKET:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_LBRC);
        case NS_RBRACKET:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_RBRC);
        case NS_SCLN:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_SCLN);
        case NS_SLASH:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_SLASH);
        case NS_UP:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_UP);
        case NS_DOWN:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_DOWN);
        case NS_LEFT:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_LEFT);
        case NS_RIGHT:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_RIGHT);
        case NS_MINUS:
            NO_ONESHOT_SHIFT_LOCKED_CODE(KC_MINUS);
    }
    return process_record_user_keymap(keycode, record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ONESHOT_MOD_ENABLE
  static osm_state_t osm_state = {
      .lalt = ONESHOT_UP_UNQUEUED,
      .lctl = ONESHOT_UP_UNQUEUED,
      .lgui = ONESHOT_UP_UNQUEUED,
      .lsft = ONESHOT_UP_UNQUEUED,
  };
  oneshot_mod_pre(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
  oneshot_mod_pre(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
  oneshot_mod_pre(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
  oneshot_mod_pre(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);
#endif  // ONESHOT_MOD_ENABLE
  const bool result = process_record_user_internal(keycode, record);
#ifdef ONESHOT_MOD_ENABLE
  oneshot_mod_post(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
  oneshot_mod_post(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
  oneshot_mod_post(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
  oneshot_mod_post(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);
#endif  // ONESHOT_MOD_ENABLE
  return result;
}

__attribute__((weak)) bool process_record_user_keymap(uint16_t keycode,
                                                      keyrecord_t *record) {
  return true;
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_reset(void) {
  rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
  rgb_matrix_sethsv(RGB_MATRIX_DEFAULT_HSV);
  rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
}
#endif  // RGB_MATRIX_ENABLE

void matrix_scan_user(void) { matrix_scan_user_keymap(); }

__attribute__((weak)) void matrix_scan_user_keymap(void) {}

/** Called on layer change. */
layer_state_t layer_state_set_user(layer_state_t state) {
  return layer_state_set_user_keymap(state);
}

__attribute__((weak)) layer_state_t layer_state_set_user_keymap(
    layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  oneshot_enable();
  keyboard_post_init_user_keymap();
}

__attribute__((weak)) void keyboard_post_init_user_keymap(void) {}

void eeconfig_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
  eeconfig_update_rgb_matrix_default();
#endif  // RGB_MATRIX_ENABLE
}

/**
 * \brief Called when a one-shot layer "lock" status changes.
 *
 * This is called automatically by the QMK framework when a one-shot layer is
 * activated and deactivated.
 * The only one-shot layer in this layout is the one-shot shift layer.  Turns
 * the RGBs solid blue when this layer is activated, and back to default when
 * deactivated.
 */
void oneshot_locked_mods_changed_user(uint8_t mods) {
#ifdef RGB_MATRIX_ENABLE
  if (mods & MOD_MASK_SHIFT) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  } else if (!mods) {
    rgb_matrix_reload_from_eeprom();  // Load default values.
  }
#endif  // RGB_MATRIX_ENABLE
  oneshot_locked_mods_changed_user_keymap(mods);
}

__attribute__((weak)) void oneshot_locked_mods_changed_user_keymap(
    uint8_t mods) {}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif  // RGB_MATRIX_ENABLE

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(1);
  //rgblight_setrgb_red();
  rgblight_setrgb(rgblight_get_val(), 0x00, 0x00);
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
  //rgb_matrix_set_color_all(RGB_RED);
  rgb_matrix_set_color_all(rgb_matrix_get_val(), 0x00, 0x00);
  rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
#ifdef OLED_ENABLE
  oled_off();
#endif  // OLED_ENABLE
  shutdown_user_keymap();
}

__attribute__((weak)) void shutdown_user_keymap(void) {}
