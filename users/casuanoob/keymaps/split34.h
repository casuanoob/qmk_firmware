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

#ifdef TAP_DANCE_ENABLE
#    include "tap_dance.h"
#endif // TAP_DANCE_ENABLE

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
void          oneshot_locked_mods_changed_keymap(uint8_t mods);
void          shutdown_keymap(void);

enum layers_keymap {
    _BASE = 0,
    _APTm,  // APTmod layer.
    _APT3,  // APTv3 layer.
    _APT4,  // APTv4 layer.
    _APTx,  // APTex layer.
    _APTmak2, // APTmak2 layer.
    _ENGL,  // Engel layer.
    _CAN,   // Canary layer.
    _GAME,  // Gaming layer.
    _NAV,  // Navigation.
    _SYM,  // Symbols.
    _NUM,  // Numrow.
    _NUMPD,  // Numpad.
    _FUN,  // Function key layer
    _SPEC,  // Specials.
};

// Layers.
#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define NUMPD TG(_NUMPD)
#define FUN OSL(_FUN)
#define SPECIAL OSL(_SPEC)
#define GAME DF(_GAME)
#define APTm DF(_APTm)
#define APT3 DF(_APT3)
#define APT4 DF(_APT4)
#define APTx DF(_APTx)
#define APTmak2 DF(_APTmak2)
#define ENGL DF(_ENGL)
#define CAN DF(_CAN)
#define BASE DF(_BASE)

// Tap dances.
#define TD_SFT OSM(MOD_LSFT)
#define RD_SFT OSM(MOD_RSFT)

// Ctrl-Tab.
#define CTL_TAB C(KC_TAB)
#define RCS_TAB RCS(KC_TAB)

// Shorthands for readability.
#define ___x___ KC_NO
/**
enum combo_events {
  THUMB_NAV,
  THUMB_SYM,
  FP_Q,
  LU_Z,
  HC_BSPC,
  DQ_ENT,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ns_combo[] = {NAV, KC_SPC, COMBO_END};
const uint16_t PROGMEM ss_combo[] = {SYM, TD_SFT, COMBO_END};
const uint16_t PROGMEM fp_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM hc_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM dq_combo[] = {NS_DOT, NS_QUOT, COMBO_END};

combo_t key_combos[] = {
  [THUMB_NAV] = COMBO(ns_combo, NAV),
  [THUMB_SYM] = COMBO(ss_combo, SYM),
  [FP_Q] = COMBO(fp_combo, KC_Q),
  [LU_Z] = COMBO(lu_combo, KC_Z),
  [HC_BSPC] = COMBO(hc_combo, KC_BSPC),
  [DQ_ENT] = COMBO(dq_combo, KC_ENT),
};
**/
/**
 * \brief Alternative Dvorak layout.
 *
 * Slightly modified versions of the original layout that also prevents quote
 * `'`, comma `,` and dot `.` from shifting (plays well with oneshot shift).
 */
// clang-format off
#define DVORAK_split_3x5_2                                                                    \
    NS_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_UNDS,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                                   NAV,  TD_SFT,   KC_SPC,    SYM
// clang-format on

/** 
 * \brief COLEMAK-dhm layout.
 * 
 * quote `'` replaces `;` on base layer to accommodate reduced keys.
 * Also prevent quote `'`, comma `,` and dot `.` from shifting 
 * (plays well with oneshot shift).
 */
// clang-format off
#define COLEMAKdhm_split_3x5_2                                                                  \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_UNDS, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, NS_COMM,  NS_DOT, NS_QUOT, \
                                   NAV,  KC_SPC,  TD_SFT,    SYM
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
       KC_Z,    KC_V,    KC_M,    KC_F,    KC_P,    KC_X,  NS_DOT, NS_COMM, NS_QUOT, KC_UNDS, \
                                   NAV,  KC_SPC,  TD_SFT,    SYM
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
       KC_X,    KC_C,    KC_M,    KC_P,    KC_K,    KC_Z,  NS_DOT, NS_COMM, NS_QUOT, KC_UNDS, \
                                   NAV,  KC_SPC,  TD_SFT,    SYM
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
       KC_Z,    KC_V,    KC_M,    KC_F,    KC_P,    KC_X,  NS_DOT, NS_COMM, NS_QUOT, KC_UNDS, \
                                   NAV,  KC_SPC,  TD_SFT,    SYM
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
    NS_QUOT,    KC_X,    KC_V,    KC_D,    KC_K,    KC_Z,    KC_H, NS_COMM,  NS_DOT, NS_SLSH, \
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
    NS_SLSH,    KC_W,    KC_M,    KC_V,    KC_Q,    KC_Z,    KC_Y,    KC_O,    KC_U, KC_UNDS, \
       KC_R,    KC_S,    KC_T,    KC_H,    KC_B,    KC_P,    KC_N,    KC_A,    KC_I,    KC_L, \
       KC_X,    KC_C,    KC_G,    KC_D,    KC_K,    KC_J,    KC_F, NS_QUOT, NS_COMM,  NS_DOT, \
                                KC_SPC,     NAV,     SYM,    KC_E
// clang-format on

/** 
 * \brief APTmak2 layout.
 * 
 * APTmak2, designed for 30 key layout with Q and Z on combos 
 * NAV and SYM are moved to thumb bigram combos
 */
// clang-format off
#define APTmak2_split_3x5_2                                                                      \
       KC_X,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, NS_QUOT, \
       KC_N,    KC_R,    KC_S,    KC_T,    KC_G,    KC_K,    KC_H,    KC_A,    KC_I,    KC_O, \
     TD_SFT,    KC_V,    KC_C,    KC_D,    KC_G,    KC_K,    KC_M, NS_COMM,  NS_DOT,  RD_SFT, \
                                KC_SPC,     NAV,     SYM,    KC_E
// clang-format on

/** 
 * \brief Canary layout.
 * 
 * Canary Ortho version layout by AKL
 * Also prevent quote `'`, comma `,` and dot `.` from shifting 
 * (plays well with oneshot shift).
 */
// clang-format off
#define Canary_split_3x5_2                                                                      \
       KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,    KC_Z,    KC_F,    KC_O,    KC_U, NS_QUOT, \
       KC_C,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_A, \
       KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,    KC_X,    KC_H, NS_COMM,  NS_DOT, KC_UNDS, \
                                   NAV,  KC_SPC,  TD_SFT,    SYM
// clang-format on
/** 
 * \brief Gaming layout (3 rows, 10 columns). 
 */
// clang-format off
#define GAMING_split_3x5_2                                                                     \
       KC_T,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
    KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_J,    KC_K,    KC_L, NS_QUOT, \
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V, DRGSCRL, KC_BTN3, KC_BTN1, KC_BTN2, SNIPING, \
                                  NAV,  KC_SPC,  TD_SFT,    SYM
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
    SPECIAL, RCS_TAB,  KC_TAB, CTL_TAB, ___x___, ___x___, KC_HOME,   NS_UP,  KC_END,  KC_DEL, \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT,   KC_F2, KC_BSPC, NS_LEFT, NS_DOWN, NS_RGHT,  KC_ENT, \
    WS_PREV,  SC_CUT, SC_COPY, SC_PSTE, WS_NEXT, DRG_TOG, KC_BTN3, KC_BTN1, KC_BTN2, SNIPING, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Symbols.
 */
// clang-format off
#define SYM_split_3x5_2                                                                       \
     KC_ESC, KC_PERC, KC_QUES, KC_COLN,   KC_AT, KC_CIRC, KC_LPRN, NS_SCLN, KC_RPRN, SPECIAL, \
    KC_EXLM, KC_PLUS, NS_MINS,  KC_EQL, KC_HASH, KC_UNDS, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    KC_TILD,  KC_DLR, KC_ASTR, NS_SLSH, KC_AMPR, KC_PIPE, KC_LCBR, NS_BSLS, KC_RCBR,  NS_GRV, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Numrow. 
 * 
 * 43215 90678, with the inner keys dropped to bottom index position.
 */
// clang-format off
#define NUMROW_split_3x5_2                                                                       \
    OS_LGUI, OS_LALT, OS_LCTL, OS_LSFT, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
       NS_4,    NS_3,    NS_2,    NS_1, ___x___, KC_BSPC,    NS_0,    NS_6,    NS_7,    NS_8, \
        FUN, NS_COMM,  NS_DOT,    NS_5, KC_LABK, KC_RABK,    NS_9, NS_LBRC, NS_RBRC,     FUN, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Numpad_j_J.
 */
// clang-format off
#define NUMPAD_split_3x5_2                                                                       \
     NS_DOT,    NS_7,    NS_8,    NS_9, KC_ASTR,   NUMPD, ___x___, ___x___, ___x___,  KC_DEL, \
     KC_EQL,    NS_4,    NS_5,    NS_6, KC_PLUS, KC_BSPC, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
    NS_SLSH,    NS_1,    NS_2,    NS_3, NS_MINS, ___x___, NS_LBRC,    NS_0, NS_RBRC,     FUN, \
                                  NS_0,   NUMPD,   NUMPD,   NUMPD
// clang-format on

/**
 * \brief Function keys.
 */
// clang-format off
#define FUN_split_3x5_2                                                                       \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_CAPS, KC_CAPS, KC_NUM,  KC_INS,  KC_SCRL, KC_PAUS, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, ___x___, ___x___, OS_LSFT, OS_LCTL, OS_LALT, OS_LGUI, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, ___x___, ___x___, ___x___, ___x___, ___x___,     FUN, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Special keycodes/functions.
 */
// clang-format off
#define SPEC_split_3x5_2                                                                      \
    SPECIAL,   BASE,     CAN,    ENGL,     APTx,    APTm,    ENGL,     CAN,    BASE, SPECIAL, \
      NK_ON,APTmak2,    GAME,  RGB_MOD, EEP_RST, EEP_RST, RGB_MOD,    GAME,    APT4,   NK_ON, \
     NK_OFF,   APT3, RGB_TOG,  DB_TOGG, QK_BOOT, QK_BOOT, DB_TOGG, RGB_TOG,    APT3,  NK_OFF, \
                               _______, _______, _______, _______
// clang-format on

/**
 * \brief Converts a 3x5_2 layout into the more community 3x5_3 layout.
 *
 * In other words, converts a split-34 keymap into a split-36 one.
 */
// clang-format off
#define _LAYOUT_split_3x5_2_to_split_3x5_3(                  \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                          k33, k34, k35, k36)                \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                     k33, KC_NO, k34, k35, k36, KC_NO 

#define LAYOUT_split_3x5_2_to_split_3x5_3(...) _LAYOUT_split_3x5_2_to_split_3x5_3(__VA_ARGS__)

// clang-format on
/* Converts the 3x5_2 layouts into 3x5_3 layouts. */
// clang-format off
#define DVORAK_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(DVORAK_split_3x5_2)
#define NAV_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NAV_split_3x5_2)
#define SYM_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SYM_split_3x5_2)
#define NUMROW_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NUMROW_split_3x5_2)
#define SPEC_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(SPEC_split_3x5_2)
#define COLEMAKdhm_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(COLEMAKdhm_split_3x5_2)
#define APTmod_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTmod_split_3x5_2)
#define APTv3_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTv3_split_3x5_2)
#define APTv4_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTv4_split_3x5_2)
#define APTex_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTex_split_3x5_2)
#define APTmak2_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(APTmak2_split_3x5_2)
#define Engel_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(Engel_split_3x5_2)
#define Canary_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(Canary_split_3x5_2)
#define GAMING_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(GAMING_split_3x5_2)
#define NUMPAD_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(NUMPAD_split_3x5_2)
#define FUN_split_3x5_3 LAYOUT_split_3x5_2_to_split_3x5_3(FUN_split_3x5_2)
// clang-format on

/**
 * \brief Converts a 3x5_2 layout into the more community 3x5_3 layout for cnano.
 *
 * In other words, converts a split-34 keymap into a split-36 one.
 */
// clang-format off
#define _LAYOUT_split_3x5_2_to_charybdis_3x5_3(                  \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                          k33, k34, k35, k36)                \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                     k33, k34, TD_SFT, k35, k36, KC_NO 

#define LAYOUT_split_3x5_2_to_charybdis_3x5_3(...) _LAYOUT_split_3x5_2_to_charybdis_3x5_3(__VA_ARGS__)
                
// clang-format on
/* Converts the 3x5_2 layouts into 3x5_3 layouts. */
// clang-format off
#define DVORAK_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(DVORAK_split_3x5_2)
#define NAV_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(NAV_split_3x5_2)
#define SYM_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(SYM_split_3x5_2)
#define NUMROW_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(NUMROW_split_3x5_2)
#define SPEC_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(SPEC_split_3x5_2)
#define COLEMAKdhm_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(COLEMAKdhm_split_3x5_2)
#define APTmod_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(APTmod_split_3x5_2)
#define APTv3_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(APTv3_split_3x5_2)
#define APTv4_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(APTv4_split_3x5_2)
#define APTex_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(APTex_split_3x5_2)
#define APTmak2_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(APTmak2_split_3x5_2)
#define Engel_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(Engel_split_3x5_2)
#define Canary_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(Canary_split_3x5_2)
#define GAMING_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(GAMING_split_3x5_2)
#define NUMPAD_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(NUMPAD_split_3x5_2)
#define FUN_cnano_3x5_3 LAYOUT_split_3x5_2_to_charybdis_3x5_3(FUN_split_3x5_2)
// clang-format on