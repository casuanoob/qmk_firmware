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
#include "quantum.h"
#include "tap_dance.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(TD_ONESHOT_DRAGSCROLL_ENABLE)
#    if defined(KEYBOARD_bastardkb_charybdis)
#        include "charybdis.h"
#    elif defined(KEYBOARD_bastardkb_dilemma
#        include "dilemma.h"
#    endif
#endif // POINTING_DEVICE_ENABLE && TD_ONESHOT_DRAGSCROLL_ENABLE &&
       // KEYBOARD_bastardkb_charybdis

#ifdef TAP_DANCE_ENABLE
static td_state_t get_current_state(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        return state->interrupted || !state->pressed ? TD_SINGLE_TAP : TD_SINGLE_HOLD;
    }
    if (state->count == 2) {
        return state->interrupted || !state->pressed ? TD_DOUBLE_TAP : TD_DOUBLE_HOLD;
    }
    if (state->count == 3) {
        return state->interrupted || !state->pressed ? TD_TRIPLE_TAP : TD_TRIPLE_HOLD;
    }
    return TD_UNKNOWN;
}

#    ifdef TD_ONESHOT_SHIFT_ENABLE
void oneshot_shift_td_on_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    oneshot_shift_td_state_t *const oneshot_shift_td_state = user_data;
    oneshot_shift_td_state->td_state                       = get_current_state(state);

    const uint8_t mod = MOD_LSFT;
    switch (oneshot_shift_td_state->td_state) {
        case TD_SINGLE_TAP:
            if (get_oneshot_locked_mods() & mod) {
                clear_oneshot_locked_mods();
                clear_oneshot_mods();
                del_mods(mod);
            } else {
                set_oneshot_mods(mod);
            }
            break;
        case TD_SINGLE_HOLD:
            add_mods(mod);
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            clear_oneshot_mods();
            caps_word_on();
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
            clear_oneshot_mods();
            set_oneshot_locked_mods(mod);
            add_mods(mod);
            break;
        default:
            break;
    }
}

void oneshot_shift_td_on_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    oneshot_shift_td_state_t *const oneshot_shift_td_state = user_data;
    if (oneshot_shift_td_state->td_state == TD_SINGLE_HOLD) {
        del_mods(MOD_LSFT);
    }
    oneshot_shift_td_state->td_state = TD_NONE;
}
#    endif // TD_ONESHOT_SHIFT_ENABLE

#    if defined(POINTING_DEVICE_ENABLE) && defined(TD_ONESHOT_DRAGSCROLL_ENABLE)
void oneshot_dragscroll_td_on_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    oneshot_dragscroll_td_state_t *const oneshot_dragscroll_td_state = user_data;
    oneshot_dragscroll_td_state->td_state                            = get_current_state(state);

    switch (oneshot_dragscroll_td_state->td_state) {
        case TD_SINGLE_TAP:
            oneshot_dragscroll_td_state->set_pointer_dragscroll_enabled(!oneshot_dragscroll_td_state->get_pointer_dragscroll_enabled());
            break;
        case TD_SINGLE_HOLD:
            oneshot_dragscroll_td_state->set_pointer_dragscroll_enabled(true);
            break;
        default:
            break;
    }
}

void oneshot_dragscroll_td_on_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    oneshot_dragscroll_td_state_t *const oneshot_dragscroll_td_state = user_data;
    if (oneshot_dragscroll_td_state->td_state == TD_SINGLE_HOLD) {
        oneshot_dragscroll_td_state->set_pointer_dragscroll_enabled(false);
    }
    oneshot_dragscroll_td_state->td_state = TD_NONE;
}
#    endif // POINTING_DEVICE_ENABLE && TD_ONESHOT_DRAGSCROLL_ENABLE
#endif     // TAP_DANCE_ENABLE
