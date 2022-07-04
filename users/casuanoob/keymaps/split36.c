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

#include "keymaps/split36.h"
#include "platform.h"

#ifdef RGB_MATRIX_ENABLE
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"
#endif  // RGB_MATRIX_ENABLE

#ifdef ONESHOT_MOD_ENABLE
#include "oneshot_mod.h"
#endif  // ONESHOT_MOD_ENABLE

#ifdef TAP_DANCE_ENABLE
#include "tap_dance.h"
#endif  // TAP_DANCE_ENABLE

#ifdef ONESHOT_MOD_ENABLE
bool is_oneshot_mod_cancel_key(uint16_t keycode) {
  switch (keycode) {
    case CLEAR:
    case LMOD:
    case RMOD:
      return true;
    default:
      return false;
  }
}

bool is_oneshot_mod_ignore_key(uint16_t keycode) {
  switch (keycode) {
    case CLEAR:
    case LMOD:
    case RMOD:
    case MOD_ESC:
    case MOD_TAB:
    case OS_LALT:
    case OS_LCTL:
    case OS_LGUI:
    case OS_LSFT:
    case OS_RALT:
      return true;
    default:
      return false;
  }
}
#endif  // ONESHOT_MOD_ENABLE

#if defined(TAP_DANCE_ENABLE) && defined(POINTING_DEVICE_ENABLE) && \
    defined(TD_ONESHOT_DRAGSCROLL_ENABLE) &&                        \
    defined(KEYBOARD_bastardkb_charybdis)
/**
 * \brief The state for the oneshot-shift tap-dance.
 *
 * This state is not meant to be accessed directly.  Instead, use the
 * `user_data` value that is passed to each callback.
 */
static oneshot_dragscroll_td_state_t g_oneshot_dragscroll_td_state = {
    .td_state = TD_NONE,
};

/**
 * \brief Define global tap-dance actions.
 */
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ONESHOT_DRAGSCROLL] =
        {
            .fn = {
                /* user_fn_on_each_tap= */ NULL,
                oneshot_dragscroll_td_on_dance_finished,
                oneshot_dragscroll_td_on_dance_reset,
            },
            .user_data = &g_oneshot_dragscroll_td_state,
            .custom_tapping_term = DELAY_TD_TAPPING_TERM,
        },
};
#endif  // TAP_DANCE_ENABLE && POINTING_DEVICE_ENABLE &&
        // TD_ONESHOT_DRAGSCROLL_ENABLE && KEYBOARD_bastardkb_charybdis

#ifdef RGB_MATRIX_ENABLE
void platform_inform_current(void) {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
  if (is_macos()) {
    rgb_matrix_sethsv_noeeprom(HSV_CYAN);
  } else {
    rgb_matrix_sethsv_noeeprom(HSV_GREEN);
  }
}
#endif  // RGB_MATRIX_ENABLE

bool process_record_user_keymap(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_keymap(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case CLEAR:
      clear_oneshot_mods();
      if (get_oneshot_layer() != 0) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      }
      layer_move(default_layer_state);
      return false;
    case KC_ESCAPE:
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
      del_mods(MOD_MASK_SHIFT);
      break;
#if defined(RGB_MATRIX_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    // Also gate on DEFERRED_EXEC_ENABLE being true since this is the mechanism
    // used to reset the RGB Matrix mode.
    // TODO(delay): find a better way to handle that.
    case MACOS:
      if (record->event.pressed) {
        platform_inform_current();
      }
      return false;
#endif  // RGB_MATRIX_ENABLE && DEFERRED_EXEC_ENABLE
  }
  return true;
};

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

void matrix_scan_user_keymap(void) { matrix_scan_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

#if defined(RGB_MATRIX_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
/**
 * Callback to defer reseting the RGB matrix to its default value.
 * This is useful when coming back from layers that use RGB matrix as indicator,
 * eg. the `SPECIAL` layer that hosts the `MACOS` keycode, which sets the RGB to
 * communicate which OS is currently selected.
 */
uint32_t reset_rgb_matrix_callback(uint32_t trigger_time, void *cb_arg) {
  rgb_matrix_reload_from_eeprom();
  return 0;
}

void schedule_rgb_matrix_reset(uint16_t delay_ms) {
  // Defer reseting the RGB matrix to its default value.
  //
  // TODO(delay): add a dedicated define for this feature, and make the
  // timeout configurable.
  static deferred_token reset_rgb_matrix_token = 0;
  if (reset_rgb_matrix_token != 0) {
    cancel_deferred_exec(reset_rgb_matrix_token);
  }
  reset_rgb_matrix_token = defer_exec(delay_ms, reset_rgb_matrix_callback,
                                      /* cb_arg= */ NULL);
}
#endif  // RGB_MATRIX_ENABLE && DEFERRED_EXEC_ENABLE

/** Called on layer change. */
layer_state_t layer_state_set_user_keymap(layer_state_t state) {
#if defined(RGB_MATRIX_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
  if (get_highest_layer(state) == _BASE) {
    // Reset the RGB matrix to its default value.
    schedule_rgb_matrix_reset(/* delay_ms= */ 1000);
  }
#endif  // RGB_MATRIX_ENABLE && DEFERRED_EXEC_ENABLE
  return layer_state_set_keymap(state);
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(
    layer_state_t state) {
  return state;
}

void keyboard_post_init_user_keymap(void) {
#ifdef RGB_MATRIX_ENABLE
  platform_inform_current();
  schedule_rgb_matrix_reset(/* delay_ms= */ 2000);
#endif  // RGB_MATRIX_ENABLE
  keyboard_post_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void oneshot_locked_mods_changed_user_keymap(uint8_t mods) {
  oneshot_locked_mods_changed_keymap(mods);
}

__attribute__((weak)) void oneshot_locked_mods_changed_keymap(uint8_t mods) {}

void shutdown_user_keymap(void) { shutdown_keymap(); }

__attribute__((weak)) void shutdown_keymap(void) {}

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUM_ENT:
    case NAV_SPC:
      return true;
  }
  return false;
}
#endif  // TAPPING_FORCE_HOLD_PER_KEY
