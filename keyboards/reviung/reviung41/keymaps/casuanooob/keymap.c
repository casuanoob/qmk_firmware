/* Copyright 2020 gtips
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

#include "quantum.h"

enum layer_names {
    _BASE = 0,
    _APT,
 //   _GAME,
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
#define FUN OSL(_FUN)
#define SPECIAL OSL(_SPEC)
#define GAME DF(_GAME)
#define APT DF(_APT)
#define BASE DF(_BASE)

// Tap dance
#define TD_SFT OSM(MOD_LSFT)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Shorthands for readability.
#define ___x___ KC_NO

// Shortcuts
#define SC_CUT LCTL(KC_X)
#define SC_COPY LCTL(KC_C)
#define SC_PASTE LCTL(KC_V)
#define SC_PASTE_NO_FORMAT LCTL(S(KC_V))
#define SC_LAUNCHER LGUI(KC_TAB)
#define SC_CLOSE LCTL(KC_W)
#define SC_NEW_TAB LCTL(KC_T)
#define SC_NEW_WINDOW LCTL(KC_N)
#define WS_PREVIOUS LCTL(LGUI(KC_LEFT))
#define WS_NEXT LCTL(LGUI(KC_RIGHT))

// Shorthands.
#define SC_PSTE SC_PASTE
#define SC_CLSE SC_CLOSE
#define SC_NTAB SC_NEW_TAB
#define SC_NWIN SC_NEW_WINDOW
#define WS_PREV WS_PREVIOUS
#define LAUNCHR SC_LAUNCHER

//tri layer
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
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
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS,  KC_BSPC, \
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,  KC_LCTL, \
       TD_SFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_QUOT,   TD_SFT, \
                                          TD_SFT,  NAV,  KC_SPC,  SYM, TD_SFT
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
       KC_ESC,    KC_W,    KC_C,    KC_G,    KC_D,    KC_K,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y,  KC_BSPC, \
      KC_LCTL,    KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I,  KC_LCTL, \
       TD_SFT,    KC_Z,    KC_V,    KC_M,    KC_F,    KC_P,    KC_X,  KC_DOT, KC_COMM, KC_QUOT, KC_UNDS,   TD_SFT, \
                                          TD_SFT,  NAV,  KC_SPC,  SYM, TD_SFT
// clang-format on

/** 
 * \brief Gaming layout (3 rows, 10 columns). 
 */
// clang-format off
#define GAMING_split_3x5_3                                                                     \
       KC_ESC,    KC_T,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  ___x___, \
      ___x___,    KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,  ___x___, \
      ___x___,    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V, DRGSCRL, KC_BTN3, KC_BTN1, KC_BTN2, SNIPING,  ___x___, \
                                          TD_SFT,  NAV,  KC_SPC,  SYM, TD_SFT
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
      _______,    SPECIAL, RCS_TAB,  KC_TAB, CTL_TAB, ___x___, ___x___, KC_HOME,   KC_UP,  KC_END,  KC_DEL,  _______, \
      _______,    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT,   KC_F2, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT,  _______, \
      _______,    WS_PREV, WS_NEXT, SC_COPY, SC_PSTE, LAUNCHR, ___x___, ___x___, ___x___, ___x___, ___x___,  _______, \
                      _______, _______, _______, _______, _______
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYM_split_3x5_3                                                                       \
      _______,     KC_ESC, KC_PERC, KC_QUES, KC_COLN,   KC_AT, KC_CIRC, KC_LPRN, KC_RPRN, KC_SCLN, SPECIAL,  _______, \
      _______,    KC_EXLM, KC_PLUS, KC_MINS,  KC_EQL, KC_HASH, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI,  _______, \
      _______,    KC_TILD,  KC_DLR, KC_ASTR, KC_SLSH, KC_AMPR, KC_PIPE, KC_LCBR, KC_RCBR, KC_BSLS,  KC_GRV,  _______, \
                       _______, _______, _______, _______, _______
// clang-format on

/**
 * \brief Numrow. 
 * 
 * 43215 90678, with the inner keys dropped to bottom index position.
 */
// clang-format off
#define NUMROW_split_3x5_3                                                                       \
      _______,    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI,  _______, \
      _______,    KC_4,    KC_3,    KC_2,    KC_1, ___x___, KC_BSPC,    KC_0,    KC_6,    KC_7,    KC_8,  _______, \
      _______,    FUN, KC_COMM,  KC_DOT,    KC_5, ___x___, ___x___,    KC_9, KC_LBRC, KC_RBRC,     FUN,  _______, \
                       _______, _______, _______, _______, _______
// clang-format on

/**
 * \brief Function keys.
 */
// clang-format off
#define FUN_split_3x5_3                                                                       \
     _______,    KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_CAPS, KC_CAPS, KC_NUM,  KC_INS,  KC_SCRL, KC_PAUS,  ___x___, \
     ___x___,    KC_F11,   KC_F4,   KC_F5,   KC_F6, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI,  ___x___, \
     ___x___,    KC_F10,   KC_F1,   KC_F2,   KC_F3, ___x___, ___x___, ___x___, ___x___, ___x___,     FUN,  ___x___, \
                               ___x___, ___x___, ___x___, ___x___, ___x___
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_3                                                                      \
      ___x___,    SPECIAL,   BASE,  RGB_MOD,     APT, RGB_TOG, RGB_TOG,     APT, RGB_MOD,    BASE, SPECIAL,  ___x___, \
      RGB_HUI,    RGB_SAI, SC_NWIN, SC_NTAB, RGB_VAI, EEP_RST, EEP_RST, RGB_VAI, SC_NTAB, SC_NWIN, RGB_SAI,  RGB_HUI, \
      RGB_HUD,    RGB_SAD, ___x___, SC_CLSE, RGB_VAD, QK_BOOT, QK_BOOT, RGB_VAD, SC_CLSE, ___x___, RGB_SAD,  RGB_HUD, \
                               _______, ___x___, ___x___, ___x___, _______
// clang-format on

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

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
    case NAV:
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
      del_mods(MOD_MASK_SHIFT);
      break;
    case SYM:
      clear_oneshot_mods();
      clear_oneshot_locked_mods();
      del_mods(MOD_MASK_SHIFT);
      break;
  }
  return true;
};

#define LAYOUT_wrapper(...) LAYOUT_reviung41(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_wrapper(COLEMAKdhm_split_3x5_3),
//  [_GAME] = LAYOUT_wrapper(GAMING_split_3x5_3),
  [_APT] = LAYOUT_wrapper(APTmod_split_3x5_3),
  [_NAV] = LAYOUT_wrapper(NAV_split_3x5_3),
  [_SYM] = LAYOUT_wrapper(SYM_split_3x5_3),
  [_NUM] = LAYOUT_wrapper(NUMROW_split_3x5_3),
  [_FUN] = LAYOUT_wrapper(FUN_split_3x5_3),
  [_SPEC] = LAYOUT_wrapper(SPEC_split_3x5_3),
};
// clang-format on

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
}