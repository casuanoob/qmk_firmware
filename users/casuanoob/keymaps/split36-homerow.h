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
#pragma once

#include "compose.h"
#include "delay.h"
#include "quantum.h"

#ifdef TAP_DANCE_ENABLE
#include "tap_dance.h"
#endif  // TAP_DANCE_ENABLE

enum layers_keymap {
  LAYER_DEFAULT = 0,
  // Alpha layers.
  LAYER_ALPHAS_FIRST = LAYER_DEFAULT,
  LAYER_ALPHAS_DVORAK = LAYER_ALPHAS_FIRST,  // Dvorak.
  LAYER_ALPHAS_COLEMAK_DHM,                  // Colemak-DHm.
  LAYER_ALPHAS_LAST = LAYER_ALPHAS_COLEMAK_DHM,
#ifndef DELAY_KEYMAP_SPLIT36_HOMEROW_LITE
  // Alpha layers with no Home Row Mods (for practice/typing tests).
  // Must mirror alpha layers, and follow the same orders.
  LAYER_NO_MODS_ALPHAS_FIRST,
  LAYER_NO_MODS_ALPHAS_DVORAK = LAYER_NO_MODS_ALPHAS_FIRST,  // Dvorak.
  LAYER_NO_MODS_ALPHAS_COLEMAK_DHM,                          // Colemak-DHm.
  LAYER_NO_MODS_ALPHAS_LAST = LAYER_NO_MODS_ALPHAS_COLEMAK_DHM,
#endif  // !DELAY_KEYMAP_SPLIT36_HOMEROW_LITE
  // Non-alphas layers.
  LAYER_NON_ALPHAS_FIRST,
  LAYER_DEV = LAYER_NON_ALPHAS_FIRST,  // Special characters used for dev/shell.
  LAYER_NAV,                           // Navigation.
  LAYER_NUM,                           // Number pad.
  LAYER_SYM,                           // Other special characters.
  LAYER_EXP,                           // Experiment layers (for one-off tests).
  LAYER_NON_ALPHAS_LAST = LAYER_EXP,
};

enum keycodes_keymap {
  FX_ESCAPE = SAFE_RANGE_KEYMAP,  // Auto-unlock OSM Shift.
  // Change default layers.  Order must match the one in `layers_keymap`.
  // By default, the default layer is changed only temporarily (ie. it only
  // persists until the keyboard loses power).  Use Shift to modify the default
  // layer in a persistent way.
  KM_FIRST_DEFAULT_LAYER,
  KM_DVORAK = KM_FIRST_DEFAULT_LAYER,  // Sets default layer to Dvorak.
  KM_COLEMAK_DHM,                      // Sets default layer to Colemak-DHm.
  KM_LAST_DEFAULT_LAYER = KM_COLEMAK_DHM,
  SAFE_RANGE_WITH_DEFAULT_KEYMAP,
};

/**
 * \brief Similar to `_kb`, `_user`, and other variants, but for keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `layer_state_set_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
layer_state_t layer_state_set_keymap(layer_state_t state);

// Shorthands
#define FX_ESC FX_ESCAPE

#define KM_DVRK KM_DVORAK
#define KM_CDHM KM_COLEMAK_DHM

// Spaces navigation.
#define FX_SCRL LGUI(KC_LEFT)
#define FX_SCRR LGUI(KC_RIGHT)

// Layers.
#define SPC_NAV LT(LAYER_NAV, KC_SPC)
#define TAB_DEV LT(LAYER_DEV, KC_TAB)
#define ESC_SYM LT(LAYER_SYM, KC_ESC)
#define ENT_NUM LT(LAYER_NUM, KC_ENT)
#define _L_PTR(KC) LT(LAYER_PTR, KC)

// Optional layers.
#define OSL_EXP OSL(LAYER_EXP)

// One-shot keys.
#if defined(TAP_DANCE_ENABLE) && defined(TD_ONESHOT_SHIFT_ENABLE)
#define OSM_SFT TD(TD_ONESHOT_SHIFT)
#else
#define OSM_SFT OSM(MOD_LSFT)
#endif  // TAP_DANCE_ENABLE && TD_ONESHOT_SHIFT_ENABLE

// clang-format off
/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with the `LAYER_ALPHAS_*` defined below, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_COLEMAK_DHM_3x10)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/* Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define ________________RESET_ROW_L________________   RESET, EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________RESET_ROW_R________________ XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,   RESET

/** \brief Dvorak layout (3 rows, 10 columns). */
#define LAYER_ALPHAS_DVORAK_3x10                                                              \
    KC_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z

/** \brief Colemak-DHm layout (3 rows, 10 columns). */
#define LAYER_ALPHAS_COLEMAK_DHM_3x10                                                         \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, NS_SCLN, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, NS_COMM,  NS_DOT, KC_SLSH

/*
 * Slightly modified versions of the layouts above to surface high-frequency
 * keys on the base layer (namely, underscore `_`).
 */

/** \brief Slightly modified Dvorak layout (3 rows, 10 columns). */
#define LAYER_ALPHAS_DVORAK_ALT_3x10                                                          \
    KC_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
       KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
    KC_UNDS,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z

/** \brief Slightly modified Colemak-DHm layout (3 rows, 10 columns). */
#define LAYER_ALPHAS_COLEMAK_DHM_ALT_3x10                                                     \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, NS_UNDS, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, NS_COMM,  NS_DOT, KC_SLSH

/** \brief Thumb clusters used on split 3x5+3 keyboards. */
#define LAYER_ALPHAS_THUMBS_1x6         TAB_DEV, SPC_NAV, OSM_SFT, ESC_SYM, ENT_NUM, OSL_EXP

/** \brief Thumb clusters used on split 3x5+3 keyboards. Use with homerow-free layouts.  */
#define LAYER_NO_MODS_ALPHAS_THUMBS_1x6    KC_TAB, KC_SPC, OSM_SFT, KC_ESC, ENT_NUM, OSL_EXP

/*
 * Layers used on split 3x5+3 keyboards.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored to my usage personal preferences.
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Development and Console layer.
 *
 * The Development & Console layer contains symbols that are most commonly used
 * by programming languages, and shells.  Symbols are on the opposite hand.
 */
#define LAYER_DEV_split_3x5_3                                                                 \
    ________________RESET_ROW_L________________, NS_BSLS, KC_LCBR, KC_AMPR, KC_RCBR, KC_PIPE, \
    ______________HOME_ROW_GACS_L______________, KC_CIRC, KC_LPRN, KC_ASTR, KC_RPRN,  KC_DLR, \
    _______________DEAD_HALF_ROW_______________, XXXXXXX, KC_QUES, NS_SLSH, KC_TILD, XXXXXXX, \
                      _______, XXXXXXX, XXXXXXX,  FX_ESC,  KC_ENT, XXXXXXX

/**
 * \brief Navigation layer.
 *
 * The Navigation layer contains the arrow keys on the opposite hand, and adds
 * the mouse buttons and cut/copy/paste fonctions on the same hand.
 */
#define LAYER_NAV_split_3x5_3                                                                 \
    FX_SCRL, KC_BTN3, KC_BTN1, KC_BTN2, FX_SCRR, XXXXXXX, KC_HOME,   KC_UP,  KC_END, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, \
    XXXXXXX, PL_PSTE, PL_COPY,  PL_CUT, XXXXXXX, _______________DEAD_HALF_ROW_______________, \
                      XXXXXXX, _______, XXXXXXX,  FX_ESC,  KC_ENT, XXXXXXX

/**
 * \brief Numerals and Symbols layer.
 *
 * The Numerals & Symbols layer contains the numpad and common arithmetic
 * functions on the opposite hand.
 */
#define LAYER_NUM_split_3x5_3                                                                 \
    KC_PEQL,    NS_7,    NS_8,    NS_9, KC_PDOT, _______________DEAD_HALF_ROW_______________, \
    KC_COLN,    NS_4,    NS_5,    NS_6, KC_PPLS, ______________HOME_ROW_GACS_R______________, \
    KC_PSLS,    NS_1,    NS_2,    NS_3, KC_PAST, _______________DEAD_HALF_ROW_______________, \
                      KC_BSPC,    NS_0, KC_MINS, XXXXXXX, _______, XXXXXXX

/**
 * \brief Symbols layer.
 *
 * The Symbol layer contains most symbols that didn't make the cut to the
 * Development & Console layer.  Those symbols are placed on the opposite hand.
 */
#define LAYER_SYM_split_3x5_3                                                                 \
    XXXXXXX,   KC_LT,  NS_GRV,   KC_GT, XXXXXXX, ________________RESET_ROW_R________________, \
    XXXXXXX, NS_LBRC, KC_PERC, NS_RBRC, XXXXXXX, ______________HOME_ROW_GACS_R______________, \
    XXXXXXX, KC_EXLM,   KC_AT, KC_HASH, XXXXXXX, _______________DEAD_HALF_ROW_______________, \
                       KC_TAB,  KC_SPC, KC_UNDS, _______, XXXXXXX, XXXXXXX

/**
 * \brief Experiments layer.
 *
 * The Experiments layer serves as placeholder for new features currently under
 * active development, until they get promoted to one of the stable layers.
 */
#define LAYER_EXP_split_3x5_3                                                                 \
    KM_DVRK, KM_CDHM, FX_PL_L, FX_PL_M, FX_PL_W, _______________DEAD_HALF_ROW_______________, \
    XXXXXXX, XXXXXXX, COMPOSE, XXXXXXX, XXXXXXX, ______________HOME_ROW_GACS_R______________, \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______
// clang-format on
