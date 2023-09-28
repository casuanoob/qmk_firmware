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

#pragma once

#include "delay.h"
#include "quantum.h"

/**
 * \brief Similar to `_kb`, `_user`, `_user_keymap`, and other variants, but for
 * keymaps.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
bool          process_record_keymap(uint16_t keycode, keyrecord_t *record);
void          matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
void          keyboard_post_init_keymap(void);
//void          oneshot_locked_mods_changed_keymap(uint8_t mods);
void          shutdown_keymap(void);

enum layers_keymap {
    _nAPTmak = 0, // nAPTmak layer.
    _CLMKdh,  // Colemak-DH layer.
    _APTm,  // APTmod layer.
    _APT3,  // APTv3 layer.
    //_APT4,  // APTv4 layer.
    //_APTx,  // APTex layer.
    _NRSTex, // NRSTex layer.
    _ADEPT, // Adept layer.
    //_ENGL,  // Engel layer.
    _CAN,  // Canary layer.
    _NERPS,  // Nerps layer.
    _GAME,  // Gaming layer.
    _NAV,  // Navigation.
    _SYM,  // Symbols.
    _NUM,  // Number layer.
    _NUMPD, // Numpad layer
    _FUN,  // Function key layer.
    _SPEC,  // Specials.
    _MOUSE, // Auto mouse layer.
};

// Layers.
#define NAV QK_TRI_LAYER_LOWER
#define SYM QK_TRI_LAYER_UPPER
#define NUMPD MO(_NUMPD)
#define FUN OSL(_FUN)
#define FUNCT MO(_FUN)
#define SPECIAL OSL(_SPEC)
#define MOUSE MO(_MOUSE)
#define GAME DF(_GAME)
#define APTm DF(_APTm)
#define APT3 DF(_APT3)
//#define APT4 DF(_APT4)
//#define APTx DF(_APTx)
#define NRSTex DF(_NRSTex)
#define nAPTmak DF(_nAPTmak)
#define ADEPT DF(_ADEPT)
//#define ENGL DF(_ENGL)
#define CAN DF(_CAN)
#define NERPS DF(_NERPS)
#define CLMKdh DF(_CLMKdh)

// Tap dances.
#define TD_SFT OSM(MOD_LSFT)
#define RD_SFT OSM(MOD_RSFT)

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Shorthands for readability.
#define ___x___ KC_NO

// Shorthands for thumbs
#ifdef TUCKY_THUMBS // if thumb cluster is more tucky
#   define _________DEFAULT_THUMBS_________  NAV,     KC_SPC,  TD_SFT,     SYM
#   define __________THEMBY_THUMBS_________  NAV,     KC_SPC,    KC_E,     SYM
#   define ___________NAV_THUMBS___________ _______, SPECIAL, _______, _______
#   define ___________SYM_THUMBS___________ _______, _______, SPECIAL, _______
#else // if thumb cluster is more reachy
#   define _________DEFAULT_THUMBS_________  KC_SPC,     NAV,     SYM,  TD_SFT
#   define __________THEMBY_THUMBS_________  KC_SPC,     NAV,     SYM,    KC_E
#   define ___________NAV_THUMBS___________ SPECIAL, _______, _______, _______
#   define ___________SYM_THUMBS___________ _______, _______, _______, SPECIAL
#endif //TUCKY_THUMBS

/**
 * \brief Alternative Dvorak layout.
 *
 * Slightly modified versions of the original layout that also prevents quote
 * `'`, comma `,` and dot `.` from shifting (plays well with oneshot shift).
 */
// clang-format off
#define DVORAK_split_3x5_2                                                                    \
    KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_UNDS,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                                   NAV,  TD_SFT,   KC_SPC,    SYM
// clang-format on

/**
 * \brief COLEMAK-dhm layout.
 *
 * quote `'` replaces `;` on alpha layer to accommodate reduced keys.
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define COLEMAKdhm_split_3x5_2                                                                  \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_QUOT, \
                                  _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief APTv3 modified layout.
 *
 * Slightly modified APTv3, ZX switch, GDF rotated
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define APTmod_split_3x5_2                                                                      \
       KC_W,    KC_C,    KC_G,    KC_D,    KC_K,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I, \
       KC_Z,    KC_V,    KC_M,    KC_F,    KC_P,    KC_X,  KC_DOT, KC_COMM, KC_QUOT, KC_UNDS, \
                                 _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief APTv3 modified layout.
 *
 * Slightly modified APTv3, VBK rotate
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define APTv3_split_3x5_2                                                                      \
       KC_W,    KC_G,    KC_D,    KC_F,    KC_V,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I, \
       KC_X,    KC_C,    KC_M,    KC_P,    KC_K,    KC_Z,  KC_DOT, KC_COMM, KC_QUOT, KC_UNDS, \
                                 _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief APTv4 modified layout.
 *
 * Slightly modified APTv4, ZX swap
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define APTv4_split_3x5_2                                                                      \
       KC_W,    KC_C,    KC_G,    KC_D,    KC_K,    KC_Q,    KC_L,    KC_U,    KC_O,    KC_Y, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_J,    KC_N,    KC_E,    KC_A,    KC_I, \
       KC_Z,    KC_V,    KC_M,    KC_F,    KC_P,    KC_X,  KC_DOT, KC_COMM, KC_QUOT, KC_UNDS, \
                                 _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief Engel layout.
 *
 * Engel layout by Apsu with QZ swap
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define Engel_split_3x5_2                                                                      \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS, \
       KC_C,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_A,    KC_I,    KC_O, \
    KC_QUOT,    KC_X,    KC_V,    KC_D,    KC_K,    KC_Z,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, \
                                   NAV,  KC_SPC,  TD_SFT,    LT(_SYM, KC_E)
// clang-format on

/**
 * \brief APTex modified layout.
 *
 * Slightly modified APTex, VK and PY swaps
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define APTex_split_3x5_2                                                                      \
    KC_SLSH,    KC_W,    KC_M,    KC_V,    KC_Q,    KC_Z,    KC_Y,    KC_O,    KC_U, KC_UNDS, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_P,    KC_N,    KC_A,    KC_I,    KC_L, \
       KC_X,    KC_C,    KC_G,    KC_D,    KC_K,    KC_J,    KC_F, KC_QUOT, KC_COMM,  KC_DOT, \
                                 __________THEMBY_THUMBS_________
// clang-format on

/**
 * \brief APTmak2 layout. Actually NRSTex
 *
 * NRSTex, designed for 30 key layout with Q and Z on combos
 * Left and right shift are moved to thumb bigram combos
 */
// clang-format off
#define NRSTex_split_3x5_2                                                                      \
       KC_X,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, \
       KC_N,    KC_R,    KC_S,    KC_T,    KC_G,    KC_K,    KC_H,    KC_A,    KC_I,    KC_O, \
      MOUSE,    KC_V,    KC_C,    KC_D,    KC_Q,    KC_Z,    KC_M, KC_COMM,  KC_DOT,   MOUSE, \
                                 __________THEMBY_THUMBS_________
// clang-format on

/**
 * \brief nu-APTmak layout.
 *
 * nAPTmak, 34 key version - can be converted to 30 key layout with Q and Z on combos
 * Left and right shift are moved to thumb bigram combos
 */
// clang-format off
#define nAPTmak_split_3x5_2                                                                      \
     QK_REP,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_K,    KC_X,    KC_N,    KC_A,    KC_I,    KC_O, \
      MOUSE,    KC_C,    KC_G,    KC_D,    KC_Q,    KC_Z,    KC_M, KC_COMM,  KC_DOT,   MOUSE, \
                                 __________THEMBY_THUMBS_________
// clang-format on

/** \brief Adept layout.
 *
 * nAPTmak, 34 key version - can be converted to 30 key layout with Q and Z on combos
 * Left and right shift are moved to thumb bigram combos
 */
// clang-format off
#define ADEPT_split_3x5_2                                                                        \
     TD_SFT,    KC_W,    KC_M,    KC_P,    KC_Q,    KC_Z,    KC_K, KC_COMM,  KC_DOT,  RD_SFT, \
       KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_V,    KC_H,    KC_A,    KC_I,    KC_O, \
       KC_X,    KC_C,    KC_F,    KC_D,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, \
                                 __________THEMBY_THUMBS_________
// clang-format on

/**
 * \brief Canary layout.
 *
 * Canary Ortho version layout by AKL
 * Also prevent quote `'`, comma `,` and dot `.` from shifting
 * (plays well with oneshot shift).
 */
// clang-format off
#define Canary_split_3x5_2                                                                       \
       KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,    KC_Z,    KC_F,    KC_O,    KC_U, KC_QUOT, \
       KC_C,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_A, \
       KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,    KC_X,    KC_H, KC_COMM,  KC_DOT, KC_UNDS, \
                                 _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief Nerps layout.
 *
 * Nerps by Smudge
 */
// clang-format off
#define Nerps_split_3x5_2                                                                       \
       KC_X,    KC_L,    KC_D,    KC_P,    KC_V,    KC_Z,    KC_K,    KC_O,    KC_U, KC_UNDS, \
       KC_N,    KC_R,    KC_T,    KC_S,    KC_G,    KC_Y,    KC_H,    KC_E,    KC_I,    KC_A, \
       KC_Q,    KC_J,    KC_M,    KC_C,    KC_W,    KC_B,    KC_F, KC_QUOT, KC_COMM,  KC_DOT, \
                                 _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief Gaming layout (3 rows, 10 columns).
 */
// clang-format off
#define GAMING_split_3x5_2                                                                      \
       KC_T,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
    KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
    KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_N,    KC_M, KC_COMM,  KC_DOT, SNIPING, \
                                _________DEFAULT_THUMBS_________
// clang-format on

/**
 * \brief Navigation layer, with convenience one-hand shortcuts.
 *
 * Shortcuts on the left side for use with the mouse in the right hand.
 * Inverted T navigation cluster on the right side to combine with left side
 * home row mods.
 */
// clang-format off
#define NAV_split_3x5_2                                                                       \
    SPECIAL, RCS_TAB,  KC_TAB, CTL_TAB, ___x___, KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT,   KC_F2, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT, \
    WS_PREV,  SC_CUT, SC_COPY, SC_PSTE, WS_NEXT, ___x___, KC_BSPC, ___x___, ___x___, ___x___, \
                               ___________NAV_THUMBS___________
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYM_split_3x5_2                                                                       \
     KC_ESC, KC_PERC, KC_QUES, KC_COLN,   KC_AT, KC_CIRC, KC_SCLN, KC_LPRN, KC_RPRN, SPECIAL, \
    KC_EXLM, KC_PLUS, KC_MINS,  KC_EQL, KC_HASH, KC_UNDS, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    KC_TILD,  KC_DLR, KC_ASTR, KC_SLSH, KC_AMPR, KC_PIPE, KC_BSLS, KC_LCBR, KC_RCBR,  KC_GRV, \
                               ___________SYM_THUMBS___________
// clang-format on

/**
 * \brief Numrow.
 *
 * 43215 90678, with the inner keys dropped to bottom index position.
 */
// clang-format off
#ifdef NUM_LAYER_NUMROW
#define NUMBER_split_3x5_2                                                                    \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
       KC_4,    KC_3,    KC_2,    KC_1, ___x___, KC_BSPC,    KC_0,    KC_6,    KC_7,    KC_8, \
        FUN, KC_COMM,  KC_DOT,    KC_5, KC_LABK, KC_RABK,    KC_9, KC_LBRC, KC_RBRC,     FUN, \
                               _______, _______, _______, _______
#else
#define NUMBER_split_3x5_2                                                                    \
    KC_SLSH,    KC_7,    KC_8,    KC_9, KC_ASTR, ___x___,  KC_EQL, KC_LABK, KC_RABK, ___x___, \
    KC_MINS,    KC_4,    KC_5,    KC_6, KC_PLUS, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
     KC_DOT,    KC_1,    KC_2,    KC_3, KC_COMM, ___x___,    KC_0, KC_LBRC, KC_RBRC,     FUN, \
                               _______, _______, _______, _______
#endif
// clang-format on

/**
 * \brief Numpad
 */
// clang-format off
#define ___________NUMPAD_HRM_____________ GUI_T(KC_PMNS), ALT_T(KC_4), CTL_T(KC_5), SFT_T(KC_6)
#define NUMPAD_split_3x5_2                                                                       \
    KC_PSLS,    KC_7,    KC_8,    KC_9, KC_PAST, KC_PAST,   KC_P7,   KC_P8,   KC_P9, KC_PMNS, \
    ___________NUMPAD_HRM_____________, KC_PPLS, KC_PSLS,   KC_P4,   KC_P5,   KC_P6, KC_PPLS, \
    KC_PDOT,    KC_1,    KC_2,    KC_3,    KC_0,   KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PDOT, \
                               _______, _______, KC_PENT,   KC_P0
// clang-format on

/**
 * \brief Function keys.
 */
// clang-format off
#define FUN_split_3x5_2                                                                       \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_CAPS,  KC_NUM,  KC_INS, KC_PSCR, KC_SCRL, KC_PAUS, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6,  KC_APP, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, ___x___, ___x___, ___x___, ___x___, ___x___,     FUN, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_2                                                                      \
    SPECIAL,  CLMKdh,   NERPS,     APTm, nAPTmak, nAPTmak,    APT3,     CAN, CLMKdh, SPECIAL, \
      NK_ON,  NRSTex,    GAME,  RGB_MOD,  EE_CLR,  EE_CLR, RGB_MOD,    GAME, NRSTex,   NK_ON, \
     NK_OFF,   ADEPT, RGB_TOG,  DB_TOGG, QK_BOOT, QK_BOOT, DB_TOGG, RGB_TOG,  ADEPT,  NK_OFF, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Pointing layer.
 */
// clang-format off
#define MOUSE_split_3x5_2                                                                     \
    _______, _______, _______, S_D_MOD, DPI_MOD, _______, _______, _______, _______, _______, \
    _______, SNIPING, _______, _______, _______, _______, _______, _______, SNIPING, _______, \
    _______, KC_BTN2, KC_BTN1, KC_BTN3, DRGSCRL, DRG_TOG, KC_BTN3, KC_BTN1, KC_BTN2, _______, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Converts a 3x5_2 layout into the more community 3x5_3 layout.
 *
 * In other words, converts a split-34 keymap into a split-36 one.
 */
// clang-format off
/*#define _LAYOUT_split_3x5_2_to_split_3x5_3(                  \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                          k33, k34, k35, k36)                \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                     k33, KC_NO, k34, k35, k36, KC_NO

#define LAYOUT_split_3x5_2_to_split_3x5_3(...) _LAYOUT_split_3x5_2_to_split_3x5_3(__VA_ARGS__)
*/
// clang-format on
/* Converts the 3x5_2 layouts into 3x5_3 layouts. */
// clang-format off
/*#define DVORAK_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(DVORAK_split_3x5_2)
#define NAV_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NAV_split_3x5_2)
#define SYM_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SYM_split_3x5_2)
#define NUMBER_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NUMBER_split_3x5_2)
#define SPEC_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SPEC_split_3x5_2)
#define NUMPAD_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NUMPAD_split_3x5_2)
#define FUN_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(FUN_split_3x5_2)
#define MOUSE_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(MOUSE_split_3x5_2)
#define GAMING_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(GAMING_split_3x5_2)
#define COLEMAKdhm_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(COLEMAKdhm_split_3x5_2)
#define APTmod_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTmod_split_3x5_2)
#define APTv3_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTv3_split_3x5_2)
#define APTv4_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTv4_split_3x5_2)
#define APTex_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTex_split_3x5_2)
#define NRSTex_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NRSTex_split_3x5_2)
#define nAPTmak_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(nAPTmak_split_3x5_2)
#define ADEPT_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(ADEPT_split_3x5_2)
#define Engel_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(Engel_split_3x5_2)
#define Canary_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(Canary_split_3x5_2)
#define Nerps_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(Nerps_split_3x5_2)
// clang-format on
*/
