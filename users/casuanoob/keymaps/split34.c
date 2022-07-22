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
#include "quantum/rgb_matrix/rgb_matrix.h"
#endif  // RGB_MATRIX_ENABLE

#ifdef ONESHOT_MOD_ENABLE
#include "oneshot_mod.h"
#endif  // ONESHOT_MOD_ENABLE

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
#endif  // ONESHOT_MOD_ENABLE

/*        34 KEY MATRIX / LAYOUT MAPPING

  ╭─────────────────────┬─────────────────────╮
  │ LT4 LT3 LT2 LT1 LT0 │ RT0 RT1 RT2 RT3 RT4 │
  │ LM4 LM3 LM2 LM1 LM0 │ RM0 RM1 RM2 RM3 RM4 │
  │ LB4 LB3 LB2 LB1 LB0 │ RB0 RB1 RB2 RB3 RB4 │
  ╰───────────╮ LH1 LH0 │ RH0 RH1 ╭───────────╯
              ╰─────────┴─────────╯             */

enum combo_events {
  L_SHIFT_COMBO,    // LM2 and LM3 => TD_SFT
  R_SHIFT_COMBO,    // RM2 and RM3 => RD_SFT
  CAPS_LOCK_COMBO,  // LT3 and RT3 => activate Caps Lock.
  CAPS_WORD_COMBO,  // LT2 and RT2 => activate Caps Word.
  ESAPE_COMBO,      // LT3 and LT4 => Esc
  Q_COMBO,          // LT2 and LT3 => Q
  Z_COMBO,          // LB2 and LB3 => Z
  BACKSPACE_COMBO,  // RB1 and RB2 => Backspace
  BACKWORD_COMBO,   // RB1 and RB3 => Backspace
  DELETE_COMBO,     // RT3 and RT4 => Delete
  DQUO_COMBO,       // RT2 and RT3 => "
  ENTER_COMBO,      // RB3 and RB4 => Enter
  L_BRACKET_COMBO,  // LT3 and LM3 => [
  R_BRACKET_COMBO,  // RT3 and RM3 => ]
  L_PAREN_COMBO,    // LT2 and LM2 => (
  R_PAREN_COMBO,    // RT2 and RM2 => )
  L_BRACE_COMBO,    // LT1 and LM1 => {
  R_BRACE_COMBO,    // RT1 and RM1 => }
  L_ABK_COMBO,      // LT0 and LM0 => <
  R_ABK_COMBO,      // LT0 and LM0 => >
  L_MOUSE_COMBO,    // RB2 and RB3 => MBTN1
  R_MOUSE_COMBO,    // RM3 and RB3 => MBTN2
  M_MOUSE_COMBO,    // RM1 and RM1 => MBTN3
  DRGSCRL_COMBO,    // RB1 and RB2 => Dragscroll
  FUN_LAYER_COMBO,  // RH0 and RH1 => _FUN
  NUM_LAYER_COMBO,  // LH0 and LH1 => _NUMPD
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t l_shift_combo[] PROGMEM = {KC_R, KC_S, COMBO_END};
const uint16_t r_shift_combo[] PROGMEM = {KC_E, KC_I, COMBO_END};
const uint16_t caps_lock_combo[] PROGMEM = {KC_W, KC_Y, COMBO_END};
const uint16_t caps_word_combo[] PROGMEM = {KC_F, KC_U, COMBO_END};
const uint16_t escape_combo[] PROGMEM = {KC_Q, KC_W, COMBO_END};
const uint16_t kc_q_combo[] PROGMEM = {KC_W, KC_F, COMBO_END};
const uint16_t kc_z_combo[] PROGMEM = {KC_X, KC_C, COMBO_END};
const uint16_t backspace_combo[] PROGMEM = {KC_H, NS_COMM, COMBO_END};
const uint16_t backword_combo[] PROGMEM = {KC_H, NS_DOT, COMBO_END};
const uint16_t delete_combo[] PROGMEM = {KC_Y, KC_UNDS, COMBO_END};
const uint16_t dquo_combo[] PROGMEM = {KC_U, KC_Y, COMBO_END};
const uint16_t enter_combo[] PROGMEM = {NS_DOT, NS_QUOT, COMBO_END};
const uint16_t l_bracket_combo[] PROGMEM = {KC_W, KC_R, COMBO_END};
const uint16_t r_bracket_combo[] PROGMEM = {KC_Y, KC_I, COMBO_END};
const uint16_t l_paren_combo[] PROGMEM = {KC_F, KC_S, COMBO_END};
const uint16_t r_paren_combo[] PROGMEM = {KC_U, KC_E, COMBO_END};
const uint16_t l_brace_combo[] PROGMEM = {KC_P, KC_T, COMBO_END};
const uint16_t r_brace_combo[] PROGMEM = {KC_L, KC_N, COMBO_END};
const uint16_t l_abk_combo[] PROGMEM = {KC_B, KC_G, COMBO_END};
const uint16_t r_abk_combo[] PROGMEM = {KC_J, KC_M, COMBO_END};
const uint16_t l_mouse_combo[] PROGMEM = {NS_COMM, NS_DOT, COMBO_END};
const uint16_t r_mouse_combo[] PROGMEM = {NS_DOT, KC_I, COMBO_END};
const uint16_t m_mouse_combo[] PROGMEM = {KC_H, KC_N, COMBO_END};
const uint16_t drgscrl_combo[] PROGMEM = {KC_K, KC_H, COMBO_END};
const uint16_t fun_layer_combo[] PROGMEM = {TD_SFT, SYM, COMBO_END};
const uint16_t num_layer_combo[] PROGMEM = {NAV, KC_SPC, COMBO_END};

combo_t key_combos[] = {
    [L_SHIFT_COMBO] = COMBO(l_shift_combo, TD_SFT),
    [R_SHIFT_COMBO] = COMBO(r_shift_combo, RD_SFT),
    [CAPS_LOCK_COMBO] = COMBO(caps_lock_combo, KC_CAPS),
    [CAPS_WORD_COMBO] = COMBO(caps_word_combo, CAPSWRD),
    [ESAPE_COMBO] = COMBO(escape_combo, KC_ESC),
    [Q_COMBO] = COMBO(kc_q_combo, KC_Q),
    [Z_COMBO] = COMBO(kc_z_combo, KC_Z),
    [BACKSPACE_COMBO] = COMBO(backspace_combo, KC_BSPC),
    [BACKWORD_COMBO] = COMBO(backword_combo, C(KC_BSPC)),
    [DELETE_COMBO] = COMBO(delete_combo, KC_DEL),
    [DQUO_COMBO] = COMBO(dquo_combo, KC_DQUO),
    [ENTER_COMBO] = COMBO(enter_combo, KC_ENT),
    [L_BRACKET_COMBO] = COMBO(l_bracket_combo, KC_LBRC),
    [R_BRACKET_COMBO] = COMBO(r_bracket_combo, KC_RBRC),
    [L_PAREN_COMBO] = COMBO(l_paren_combo, KC_LPRN),
    [R_PAREN_COMBO] = COMBO(r_paren_combo, KC_RPRN),
    [L_BRACE_COMBO] = COMBO(l_brace_combo, KC_LCBR),
    [R_BRACE_COMBO] = COMBO(r_brace_combo, KC_RCBR),
    [L_ABK_COMBO] = COMBO(l_abk_combo, KC_LABK),
    [R_ABK_COMBO] = COMBO(r_abk_combo, KC_RABK),
    [L_MOUSE_COMBO] = COMBO(l_mouse_combo, KC_BTN1),
    [R_MOUSE_COMBO] = COMBO(r_mouse_combo, KC_BTN2),
    [M_MOUSE_COMBO] = COMBO(m_mouse_combo, KC_BTN3),
    [DRGSCRL_COMBO] = COMBO(drgscrl_combo, DRGSCRL),
    [FUN_LAYER_COMBO] = COMBO(fun_layer_combo, FUNCT),
    [NUM_LAYER_COMBO] = COMBO(num_layer_combo, NUMPD),
};

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

__attribute__((weak)) bool process_record_keymap(uint16_t keycode,
                                                 keyrecord_t *record) {
  return true;
}

void matrix_scan_user_keymap(void) { matrix_scan_keymap(); }

__attribute__((weak)) void matrix_scan_keymap(void) {}

/** Called on layer change. */
layer_state_t layer_state_set_user_keymap(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
  #ifdef RGB_MATRIX_ENABLE
    switch (get_highest_layer(state | default_layer_state)) {
      case _CLMKdh:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_WHITE);
        break;
      case _NAV:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_WHITE);
        break;
      case _SYM:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_WHITE);
        break;
      case _NUM:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
        break;
      case _GAME:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_TEAL);
        break;
      case _APTm:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_GOLD);
        break;
      case _APT3:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_TURQUOISE);
        break;
/**      case _APT4:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_CYAN);
        break;
      case _APTx:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_SPRINGGREEN);
        break;
*/
      case _nAPTmak:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_SPRINGGREEN);
        break;
      case _NRSTex:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_AZURE);
        break;
/**      case _ENGL:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
        break;
*/
      case _CAN:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_PINK);
        break;
      case _NERPS:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
        break;
      case _NUMPD:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
        break;
      case _FUN:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_CORAL);
        break;
      case _SPEC:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_GOLDENROD);
        break;
      case _MOUSE:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
        break;
      default: //  for any other layers, or the default layer
        rgb_matrix_reload_from_eeprom();  // Load default values.
        break;
    }
    #endif // RGB_MATRIX_ENABLE
  return state;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        // I have a dedicated underscore key, so no need to shift KC_MINS.
        case KC_UNDS:
        case NS_MINS:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}