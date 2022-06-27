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

#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    _BASE = 0,
    _APT,
//    _GAME,
    _NAV,
    _SYM,
    _NUM,
    _FUN,
    _SPEC,
};

// Layers.
#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define WNAV TG(_WNAV)
#define NUMPD TG(_NUMPD)
#define FUN OSL(_FUN)
#define SPECIAL OSL(_SPEC)
//#define GAME DF(_GAME)
#define APT DF(_APT)
#define BASE DF(_BASE)

// Tap dance
#define TD_SFT OSM(MOD_LSFT)

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Shorthands for readability.
#define ___x___ KC_NO

//tri layer
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return state;
}

/** 
 * \brief COLEMAK-dhm layout.
 * 
 * quote `'` replaces `;` on base layer to accommodate reduced keys.
 * Also prevent quote `'`, comma `,` and dot `.` from shifting 
 * (plays well with oneshot shift).
 */
// clang-format off
#define COLEMAKdhm_split_3x5_3                                                                  \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, NS_COMM,  NS_DOT, NS_QUOT, \
                            NAV,  KC_SPC, TD_SFT,  TD_SFT,    SYM
// clang-format on

/** 
 * \brief APTv3 modified layout.
 * 
 * Slightly modified APTv3, ZX switch, GDF rotated
 * Also prevent quote `'`, comma `,` and dot `.` from shifting 
 * (plays well with oneshot shift).
 */
// clang-format off
#define APTmod_split_3x5_3                                                                     \
       KC_W,    KC_C,    KC_G,    KC_D,    KC_K,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I, \
       KC_Z,    KC_V,    KC_M,    KC_F,    KC_P,    KC_X,  NS_DOT, NS_COMM, NS_QUOT, KC_UNDS, \
                            NAV,  KC_SPC, TD_SFT,  TD_SFT,    SYM
// clang-format on

/** 
 * \brief Gaming layout (3 rows, 10 columns). 
 */
// clang-format off
/**#define GAMING_split_3x5_3                                                                     \
       KC_T,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
    KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_J,    KC_K,    KC_L, NS_QUOT, \
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V, DRGSCRL, KC_BTN3, KC_BTN1, KC_BTN2, SNIPING, \
                            NAV,  KC_SPC, TD_SFT,  TD_SFT,    SYM*/
// clang-format on

/**
 * \brief Navigation layer, with convenience one-hand shortcuts.
 *
 * Shortcuts on the left side for use with the mouse in the right hand.
 * Inverted T navigation cluster on the right side to combine with left side
 * home row mods.
 */
// clang-format off
#define NAV_split_3x5_3                                                                      \
    SPECIAL, RCS_TAB,  KC_TAB, CTL_TAB,   NUMPD,   NUMPD, KC_HOME,   NS_UP,  KC_END,  KC_DEL, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT,   KC_F2, KC_BSPC, NS_LEFT, NS_DOWN, NS_RGHT,  KC_ENT, \
    WS_PREV, WS_NEXT, SC_COPY, SC_PSTE, LAUNCHR, DRG_TOG, KC_BTN3, KC_BTN1, KC_BTN2, SNIPING, \
                      _______, _______, _______, _______, _______
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYM_split_3x5_3                                                                       \
     KC_ESC, KC_PERC, KC_QUES, KC_COLN,   KC_AT, KC_CIRC, KC_LPRN, KC_RPRN, NS_SCLN, SPECIAL, \
    KC_EXLM, KC_PLUS, NS_MINS,  KC_EQL, KC_HASH, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    KC_TILD,  KC_DLR, KC_ASTR, NS_SLSH, KC_AMPR, KC_PIPE, KC_LCBR, KC_RCBR, NS_BSLS,  NS_GRV, \
                       _______, _______, _______, _______, _______
// clang-format on

/**
 * \brief Numrow. 
 * 
 * 43215 90678, with the inner keys dropped to bottom index position.
 */
// clang-format off
#define NUMROW_split_3x5_3                                                                       \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
       NS_4,    NS_3,    NS_2,    NS_1, ___x___, KC_BSPC,    NS_0,    NS_6,    NS_7,    NS_8, \
        FUN, NS_COMM,  NS_DOT,    NS_5, ___x___, ___x___,    NS_9, NS_LBRC, NS_RBRC,     FUN, \
                       _______, _______, _______, _______, _______
// clang-format on

/**
 * \brief Function keys.
 */
// clang-format off
#define FUN_split_3x5_3                                                                       \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_CAPS, KC_CAPS, KC_NUM,  KC_INS,  KC_SCRL, KC_PAUS, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, ___x___, ___x___, ___x___, ___x___, ___x___,     FUN, \
                               ___x___, ___x___, ___x___, ___x___, ___x___
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_3                                                                      \
    SPECIAL,   BASE,  ___x___,     APT, RGB_TOG, RGB_TOG,     APT, ___x___,    BASE, SPECIAL, \
    ___x___, SC_NWIN, SC_NTAB, ___x___, EEP_RST, EEP_RST, ___x___, SC_NTAB, SC_NWIN, ___x___, \
    ___x___, ___x___, SC_CLSE, ___x___, QK_BOOT, QK_BOOT, ___x___, SC_CLSE, ___x___, ___x___, \
                               _______, ___x___, ___x___, ___x___, _______
// clang-format on

#define LAYOUT_charybdis_3x5_delay(...) LAYOUT_charybdis_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_charybdis_3x5_delay(COLEMAKdhm_split_3x5_3),
 // [_GAME] = LAYOUT_charybdis_3x5_delay(GAMING_split_3x5_3),
  [_APT] = LAYOUT_charybdis_3x5_delay(APTmod_split_3x5_3),
  [_NAV] = LAYOUT_charybdis_3x5_delay(NAV_split_3x5_3),
  [_SYM] = LAYOUT_charybdis_3x5_delay(SYM_split_3x5_3),
  [_NUM] = LAYOUT_charybdis_3x5_delay(NUMROW_split_3x5_3),
  [_FUN] = LAYOUT_charybdis_3x5_delay(FUN_split_3x5_3),
  [_SPEC] = LAYOUT_charybdis_3x5_delay(SPEC_split_3x5_3),
};
// clang-format on