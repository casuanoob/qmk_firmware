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
#include "keymap.h"
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"
#endif  // RGB_MATRIX_ENABLE

#include "features/achordion.h"
#include "features/compose.h"
#include "features/custom_shift_keys.h"
#include "features/oneshot_mod.h"
#include "features/tap_dance.h"

typedef struct {
  oneshot_mod_state_t lalt;
  oneshot_mod_state_t lctl;
  oneshot_mod_state_t lgui;
  oneshot_mod_state_t lsft;
} osm_state_t;

bool is_oneshot_mod_cancel_key(uint16_t keycode) {
  switch (keycode) {
    case NAVL:
    case NAVR:
      return true;
    default:
      return false;
  }
}

bool is_oneshot_mod_ignore_key(uint16_t keycode) {
  switch (keycode) {
    case NAVL:
    case NAVR:
    case OS_LALT:
    case OS_LCTL:
    case OS_LGUI:
    case OS_LSFT:
      return true;
    default:
      return false;
  }
}

/**
 * \brief The state for the oneshot-shift tap-dance.
 *
 * This state is not meant to be accessed directly.  Instead, use the
 * `user_data` value that is passed to each callback.
 */
static oneshot_shift_td_state_t g_oneshot_shift_td_state = {
    .td_state = TD_NONE,
};

/**
 * \brief Define global tap-dance actions.
 */
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ONESHOT_SHIFT] =
        {
            .fn = {
                /* user_fn_on_each_tap= */ NULL,
                oneshot_shift_td_on_dance_finished,
                oneshot_shift_td_on_dance_reset,
            },
            .user_data = &g_oneshot_shift_td_state,
        },
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT, KC_QUES},   // Shift . is ?
    {KC_COMM, KC_EXLM},  // Shift , is !
    {KC_EQL, KC_EQL},    // Don't shift =
    {KC_SLSH, KC_SLSH},  // Don't shift /
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

enum combo_events {
  CAPS_COMBO,  // . and C => activate Caps Word.
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t caps_combo[] PROGMEM = {KC_DOT, KC_C, COMBO_END};

combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO_ACTION(caps_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  if (pressed) {
    switch (combo_index) {
      case CAPS_COMBO:
        caps_word_on();
        break;
    }
  }
}

__attribute__((weak)) uint16_t get_tapping_term_keymap(uint16_t keycode,
                                                       keyrecord_t *record) {
  return TAPPING_TERM;
}

/**
 * \brief Define key-specific `TAPPING_TERM`.
 *
 * Tunes the `TAPPING_TERM` for both layer-taps and Home Row mods.  For Home Row
 * mods, this implementation assumes GACS home row order.
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TD_SFT:
      return TAPPING_TERM + 25;  // Thumb is a slow finger.
  }
  return get_tapping_term_keymap(keycode, record);
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning true means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    // Repeating is useful for Vim navigation keys.
    case HOME_U:
    case HOME_H:
    // Repeating Z is useful for spamming undo.
    case HOME_Z:
      return false;  // Enable key repeating.
    default:
      return true;  // Otherwise, force hold and disable key repeating.
  }
}

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    // I have a dedicated underscore key, so no need to shift KC_MINS.
    case KC_MINS:
    case KC_UNDS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                     uint16_t other_keycode, keyrecord_t *other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand in Dvorak.
  switch (tap_hold_keycode) {
    case HOME_A:  // A + U.
      if (other_keycode == HOME_U) {
        return true;
      }
      break;

    case HOME_S:  // S + H and S + G.
      if (other_keycode == HOME_H || other_keycode == KC_G) {
        return true;
      }
      break;
  }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) {
    return true;
  }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
    case HOME_SC:
    case HOME_Z:
      return 0;  // Bypass Achordion for these keys.
  }

  return 500;  // Otherwise use a timeout of 800 ms.
}

/**
 * \brief Do not shift `keycode` if only oneshot-shift is locked.
 *
 * This effectively suppresses the effect of oneshot-shift locked mod for some
 * keycodes, allowing for better typing experience in all caps (eg. for
 * identifier names in some programming language/coding style).
 */
#ifndef NO_ONESHOT_SHIFT_LOCKED_CODE
#define NO_ONESHOT_SHIFT_LOCKED_CODE(keycode)                  \
  {                                                            \
    if (record->event.pressed) {                               \
      if (get_oneshot_locked_mods() & MOD_MASK_SHIFT) {        \
        const uint8_t mod_shift = get_mods() & MOD_MASK_SHIFT; \
        unregister_mods(mod_shift);                            \
        register_code(keycode);                                \
        register_mods(mod_shift);                              \
      } else {                                                 \
        register_code(keycode);                                \
      }                                                        \
    } else {                                                   \
      unregister_code(keycode);                                \
    }                                                          \
    break;                                                     \
  }
#endif  // NO_ONESHOT_SHIFT_LOCKED_CODE

static bool process_record_user_internal(uint16_t keycode,
                                         keyrecord_t *record) {
  if (!process_record_keymap(keycode, record)) {
    return false;
  }
  if (!process_custom_shift_keys(keycode, record)) {
    return false;
  }
  if (!process_achordion(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case NS_BSLASH:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_BSLASH);
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
    case NS_SCOLON:
      NO_ONESHOT_SHIFT_LOCKED_CODE(KC_SCOLON);
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
    case KC_ESCAPE:
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
      del_mods(MOD_MASK_SHIFT);
      break;
  }
  return true;
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

  const bool result = process_record_user_internal(keycode, record);

  oneshot_mod_post(&osm_state.lalt, KC_LALT, OS_LALT, keycode, record);
  oneshot_mod_post(&osm_state.lctl, KC_LCTL, OS_LCTL, keycode, record);
  oneshot_mod_post(&osm_state.lgui, KC_LGUI, OS_LGUI, keycode, record);
  oneshot_mod_post(&osm_state.lsft, KC_LSFT, OS_LSFT, keycode, record);

  return result;
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_reset(void) {
  rgb_matrix_mode(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv(RGB_MATRIX_STARTUP_HSV);
  rgb_matrix_set_speed(RGB_MATRIX_STARTUP_SPD);
}
#endif  // RGB_MATRIX_ENABLE

void matrix_scan_user(void) {
  achordion_task();
  matrix_scan_keymap();
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

/** Called on layer change. */
layer_state_t layer_state_set_user(layer_state_t state) {
  return layer_state_set_keymap(
      update_tri_layer_state(state, _NAVL, _NAVR, _NUM));
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(
    layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  oneshot_enable();
  keyboard_post_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

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
  oneshot_locked_mods_changed_keymap(mods);
}

__attribute__((weak)) void oneshot_locked_mods_changed_keymap(uint8_t mods) {}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif  // RGB_MATRIX_ENABLE

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(1);
  rgblight_setrgb_red();
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_set_color_all(RGB_RED);
  rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
#ifdef OLED_ENABLE
  oled_off();
#endif  // OLED_ENABLE
  shutdown_keymap();
}

__attribute__((weak)) void shutdown_keymap(void) {}
