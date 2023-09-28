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
#include "users/casuanoob/keymaps/split34.h"

#define LAYOUT_charybdis_3x5_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)
#define LAYOUT_charybdis_3x5_base( \
    K01, K02, K03, K04, K05,  K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15,  K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25,  K26, K27, K28, K29, K2A, \
                   K34, K35,  K36, K37                 \
    ) \
    LAYOUT_charybdis_3x5 ( \
       K01, K02, K03, K04, K05,  K06, K07, K08, K09, K0A, \
       K11, K12, K13, K14, K15,  K16, K17, K18, K19, K1A, \
       K21, K22, K23, K24, K25,  K26, K27, K28, K29, K2A, \
                 K34, KC_NO, K35, K36, K37                \
    )
#define LAYOUT_charybdis_3x5_base_wrapper(...)       LAYOUT_charybdis_3x5_base(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_nAPTmak] = LAYOUT_charybdis_3x5_base_wrapper(nAPTmak_split_3x5_2),
  [_CLMKdh] = LAYOUT_charybdis_3x5_base_wrapper(COLEMAKdhm_split_3x5_2),
  [_NRSTex] = LAYOUT_charybdis_3x5_base_wrapper(NRSTex_split_3x5_2),
  [_ADEPT] = LAYOUT_charybdis_3x5_base_wrapper(ADEPT_split_3x5_2),
  [_APTm] = LAYOUT_charybdis_3x5_base_wrapper(APTmod_split_3x5_2),
  [_APT3] = LAYOUT_charybdis_3x5_base_wrapper(APTv3_split_3x5_2),
  [_CAN] = LAYOUT_charybdis_3x5_base_wrapper(Canary_split_3x5_2),
  [_NERPS] = LAYOUT_charybdis_3x5_base_wrapper(Nerps_split_3x5_2),
  [_GAME] = LAYOUT_charybdis_3x5_base_wrapper(GAMING_split_3x5_2),
  [_NAV] = LAYOUT_charybdis_3x5_base_wrapper(NAV_split_3x5_2),
  [_SYM] = LAYOUT_charybdis_3x5_base_wrapper(SYM_split_3x5_2),
  [_NUM] = LAYOUT_charybdis_3x5_base_wrapper(NUMBER_split_3x5_2),
  [_NUMPD] = LAYOUT_charybdis_3x5_base_wrapper(NUMPAD_split_3x5_2),
  [_FUN] = LAYOUT_charybdis_3x5_base_wrapper(FUN_split_3x5_2),
  [_SPEC] = LAYOUT_charybdis_3x5_base_wrapper(SPEC_split_3x5_2),
  [_MOUSE] = LAYOUT_charybdis_3x5_base_wrapper(MOUSE_split_3x5_2),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_nAPTmak] =    { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_CLMKdh] =     { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_NRSTex] =     { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_ADEPT] =      { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_APTm] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_APT3] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_CAN] =        { ENCODER_CCW_CW(KC_UP, KC_DOWN) },
    [_NERPS] =      { ENCODER_CCW_CW(KC_UP, KC_DOWN) },
    [_GAME] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_NAV] =        { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_SYM] =        { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_NUM] =        { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_NUMPD] =      { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FUN] =        { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_SPEC] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_MOUSE] =      { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) {
    //if (index == 0) {
        if (active) {
            register_code(KC_A);
        } else {
            unregister_code(KC_A);
        }
    //}
    return true;
}
#endif // DIP_SWITCH_ENABLE

// Triple nop delay thing lol
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}

void keyboard_post_init_user_keymap(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
  debug_matrix=false;
  //debug_keyboard=true;
  //debug_mouse=false;
}

void matrix_init_keymap(void) {
#if defined (RGB_MATRIX_ENABLE) && defined(KEYBOARD_bastardkb_charybdis_3x5_blackpill)

/**
 * \brief LEDs index.
 *
 * ╭────────────────────╮                 ╭────────────────────╮
 *    2   3   8   9  12                     30  27  26  21  20
 * ├────────────────────┤                 ├────────────────────┤
 *    1   4   7  10  13                     31  28  25  22  19
 * ├────────────────────┤                 ├────────────────────┤
 *    0   5   6  11  14                     32  29  24  23  18
 * ╰────────────────────╯                 ╰────────────────────╯
 *                   15  16  17     33  34  XX
 *                 ╰────────────╯ ╰────────────╯
 *
 * Note: the LED config simulates 36 LEDs instead of the actual 35 to prevent
 * confusion when testing LEDs during assembly when handedness is not set
 * correctly.  Those fake LEDs are bound to the physical top-left corner.
 */
g_led_config = (led_config_t){ {
    /* Key Matrix to LED index. */
    // Left split.
    {      2,      3,      8,      9,     12 }, // Top row
    {      1,      4,      7,     10,     13 }, // Middle row
    {      0,      5,      6,     11,     14 }, // Bottom row
    {     17, NO_LED,     15,     16, NO_LED }, // Thumb cluster
    // Right split.
    {     20,     21,     26,     27,     30 }, // Top row
    {     19,     22,     25,     28,     31 }, // Middle row
    {     18,     23,     24,     29,     32 }, // Bottom row
    {     33, NO_LED,     34, NO_LED, NO_LED }, // Thumb cluster

}, {
    /* LED index to physical position. */
    // Left split.
    /* index=0  */ {   0,  42 }, {   0,  21 }, {   0,   0 }, // col 1 (left most)
    /* index=3  */ {  18,   0 }, {  18,  21 }, {  18,  42 }, // col 2
    /* index=6  */ {  36,  42 }, {  36,  21 }, {  36,   0 },
    /* index=9  */ {  54,   0 }, {  54,  21 }, {  54,  42 },
    /* index=12 */ {  72,   0 }, {  72,  21 }, {  72,  42 },

    {   0,   0 }, {   0,   0 }, {   0,   0 },
    {   0,   0 }, {   0,   0 }, {   0,   0 },
    {   0,   0 }, {   0,   0 }, {   0,   0 },
    {   0,   0 }, {   0,   0 }, {   0,   0 }, //Falcon left

    /* index=15 */ {  72,  64 }, {  90,  64 }, { 108,  64 }, // Thumb cluster
    // Right split.
    /* index=18 */ { 224,  42 }, { 224,  21 }, { 224,   0 }, // col 10 (right most)
    /* index=21 */ { 206,   0 }, { 206,  21 }, { 206,  42 }, // col 9
    /* index=24 */ { 188,  42 }, { 188,  21 }, { 188,   0 },
    /* index=27 */ { 170,   0 }, { 170,  21 }, { 170,  42 },
    /* index=30 */ { 152,   0 }, { 152,  21 }, { 152,  42 },
    /* index=33 */ { 134,  64 }, { 152,  64 }, {   0,   0 }, // Thumb cluster
}, {
    /* LED index to flag. */
    // Left split.
    /* index=0  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 1
    /* index=3  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 2
    /* index=6  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=9  */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=12 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,

    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, //Falcon left

    /* index=15 */ LED_FLAG_INDICATOR, LED_FLAG_INDICATOR, LED_FLAG_INDICATOR,
//    /* index=15 */ LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, LED_FLAG_MODIFIER, // Thumb cluster
    // Right split.
    /* index=18 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 10
    /* index=21 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // col 9
    /* index=24 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=27 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=30 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    /* index=33 */ LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, // Thumb cluster
} };
#endif //defined (RGB_MATRIX_ENABLE) && defined(KEYBOARD_bastardkb_charybdis_3x5_blackpill)
}
