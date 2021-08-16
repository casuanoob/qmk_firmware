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

#include "keymaps/split34.h"

#ifdef RGB_MATRIX_ENABLE
#    include "quantum/rgb_matrix/rgb_matrix.h"
#    include "quantum/rgblight/rgblight_list.h"
#endif // RGB_MATRIX_ENABLE

#ifdef ONESHOT_MOD_ENABLE
#    include "oneshot_mod.h"
#endif // ONESHOT_MOD_ENABLE

#ifdef ONESHOT_MOD_ENABLE
bool is_oneshot_mod_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case NAV:
        case SYM:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_mod_ignore_key(uint16_t keycode) {
    switch (keycode) {
        case NAV:
        case SYM:
        case OS_LALT:
        case OS_LCTL:
        case OS_LGUI:
        case OS_LSFT:
            return true;
        default:
            return false;
    }
}
#endif // ONESHOT_MOD_ENABLE

#ifdef TAP_DANCE_ENABLE
#    include "tap_dance.h"
#endif // TAP_DANCE_ENABLE

#ifdef TAP_DANCE_ENABLE
#    ifdef TD_ONESHOT_SHIFT_ENABLE
/**
 * \brief The state for the oneshot-shift tap-dance.
 *
 * This state is not meant to be accessed directly.  Instead, use the
 * `user_data` value that is passed to each callback.
 */
static oneshot_shift_td_state_t g_oneshot_shift_td_state = {
    .td_state = TD_NONE,
};
#    endif // TD_ONESHOT_SHIFT_ENABLE

/**
 * \brief Define global tap-dance actions.
 */
qk_tap_dance_action_t tap_dance_actions[] = {
#    ifdef TD_ONESHOT_SHIFT_ENABLE
    [TD_ONESHOT_SHIFT] =
        {
            .fn = {
                /* user_fn_on_each_tap= */ NULL,
                oneshot_shift_td_on_dance_finished,
                oneshot_shift_td_on_dance_reset,
            },
            .user_data = &g_oneshot_shift_td_state,
        },
#    endif // TD_ONESHOT_SHIFT_ENABLE
};
#endif // TAP_DANCE_ENABLE

#if defined(TAP_DANCE_ENABLE) && defined(TD_ONESHOT_SHIFT_ENABLE) && defined(TAPPING_TERM_PER_KEY)
/**
 * \brief Define key-specific `TAPPING_TERM`.
 *
 * Tunes the `TAPPING_TERM` for both layer-taps and Home Row mods.  For Home Row
 * mods, this implementation assumes GACS home row order.
 */
uint16_t get_tapping_term_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_SFT:
            return TAPPING_TERM + 125;
    }
    return TAPPING_TERM;
}
#endif // TAP_DANCE_ENABLE && TD_ONESHOT_SHIFT_ENABLE && TAPPING_TERM_PER_KEY

bool process_record_user_keymap(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case KC_ESCAPE:
            clear_oneshot_mods();
            clear_oneshot_locked_mods();
            del_mods(MOD_MASK_SHIFT);
            break;
    }
    return true;
};

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_scan_user_keymap(void) {
    matrix_scan_keymap();
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

/** Called on layer change. */
layer_state_t layer_state_set_user_keymap(layer_state_t state) {
    return layer_state_set_keymap(update_tri_layer_state(state, _NAV, _SYM, _NUM));
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

void keyboard_post_init_user_keymap(void) {
    keyboard_post_init_keymap();
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void oneshot_locked_mods_changed_user_keymap(uint8_t mods) {
    oneshot_locked_mods_changed_keymap(mods);
}

__attribute__((weak)) void oneshot_locked_mods_changed_keymap(uint8_t mods) {}

void shutdown_user_keymap(void) {
    shutdown_keymap();
}

__attribute__((weak)) void shutdown_keymap(void) {}
