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
#include "keymaps/split34.h"

#define LAYOUT_charybdis_3x5_delay(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_nAPTmak] = LAYOUT_charybdis_3x5_delay(nAPTmak_split_3x5_3),
  [_CLMKdh] = LAYOUT_charybdis_3x5_delay(COLEMAKdhm_split_3x5_3),
  [_NRSTex] = LAYOUT_charybdis_3x5_delay(NRSTex_split_3x5_3),
  [_ADEPT] = LAYOUT_charybdis_3x5_delay(ADEPT_split_3x5_3),
  [_APTm] = LAYOUT_charybdis_3x5_delay(APTmod_split_3x5_3),
  [_APT3] = LAYOUT_charybdis_3x5_delay(APTv3_split_3x5_3),
  [_CAN] = LAYOUT_charybdis_3x5_delay(Canary_split_3x5_3),
  [_NERPS] = LAYOUT_charybdis_3x5_delay(Nerps_split_3x5_3),
  [_GAME] = LAYOUT_charybdis_3x5_delay(GAMING_split_3x5_3),
  [_NAV] = LAYOUT_charybdis_3x5_delay(NAV_split_3x5_3),
  [_SYM] = LAYOUT_charybdis_3x5_delay(SYM_split_3x5_3),
  [_NUM] = LAYOUT_charybdis_3x5_delay(NUMBER_split_3x5_3),
  [_NUMPD] = LAYOUT_charybdis_3x5_delay(NUMPAD_split_3x5_3),
  [_FUN] = LAYOUT_charybdis_3x5_delay(FUN_split_3x5_3),
  [_SPEC] = LAYOUT_charybdis_3x5_delay(SPEC_split_3x5_3),
  [_MOUSE] = LAYOUT_charybdis_3x5_delay(MOUSE_split_3x5_3),
};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state) > 0) {
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
    } else {  /* Layer 0 */
            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }
    }
    return false;
}
#endif // ENCODER_ENABLE

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
/**void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}
**/
void keyboard_post_init_user_keymap(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
  debug_matrix=false;
  //debug_keyboard=true;
  //debug_mouse=false;
  #ifdef RGB_MATRIX_ENABLE
  rgb_matrix_sethsv_noeeprom(HSV_WHITE);
  #endif
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
