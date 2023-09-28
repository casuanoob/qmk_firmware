#include "combos.h"

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
  V_COMBO,          // LT2 and LT3 => V
  Q_COMBO,          // LT3 and LT4 => Q
  Z_COMBO,          // LB3 and LB4 => Z
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
  GAME_G_COMBO,     // LT0 and LM0 => G
  GAME_B_COMBO,     // LM0 and LB0 => B
  COMBO_LENGTH
};
//uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t l_shift_combo[] PROGMEM = {KC_R, KC_S, COMBO_END};
const uint16_t r_shift_combo[] PROGMEM = {KC_E, KC_I, COMBO_END};
const uint16_t caps_lock_combo[] PROGMEM = {KC_W, KC_Y, COMBO_END};
const uint16_t caps_word_combo[] PROGMEM = {KC_F, KC_U, COMBO_END};
const uint16_t escape_combo[] PROGMEM = {KC_Q, KC_W, COMBO_END};
const uint16_t kc_v_combo[] PROGMEM = {KC_W, KC_F, COMBO_END};
const uint16_t kc_q_combo[] PROGMEM = {KC_F, KC_P, COMBO_END};
const uint16_t kc_z_combo[] PROGMEM = {KC_C, KC_D, COMBO_END};
const uint16_t backspace_combo[] PROGMEM = {KC_H, KC_COMM, COMBO_END};
const uint16_t backword_combo[] PROGMEM = {KC_H, KC_DOT, COMBO_END};
const uint16_t delete_combo[] PROGMEM = {KC_Y, KC_UNDS, COMBO_END};
const uint16_t dquo_combo[] PROGMEM = {KC_U, KC_Y, COMBO_END};
const uint16_t enter_combo[] PROGMEM = {KC_DOT, KC_QUOT, COMBO_END};
const uint16_t l_bracket_combo[] PROGMEM = {KC_W, KC_R, COMBO_END};
const uint16_t r_bracket_combo[] PROGMEM = {KC_Y, KC_I, COMBO_END};
const uint16_t l_paren_combo[] PROGMEM = {KC_F, KC_S, COMBO_END};
const uint16_t r_paren_combo[] PROGMEM = {KC_U, KC_E, COMBO_END};
const uint16_t l_brace_combo[] PROGMEM = {KC_P, KC_T, COMBO_END};
const uint16_t r_brace_combo[] PROGMEM = {KC_L, KC_N, COMBO_END};
const uint16_t l_abk_combo[] PROGMEM = {KC_B, KC_G, COMBO_END};
const uint16_t r_abk_combo[] PROGMEM = {KC_J, KC_M, COMBO_END};
const uint16_t l_mouse_combo[] PROGMEM = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t r_mouse_combo[] PROGMEM = {KC_DOT, KC_I, COMBO_END};
const uint16_t m_mouse_combo[] PROGMEM = {KC_H, KC_N, COMBO_END};
const uint16_t drgscrl_combo[] PROGMEM = {KC_K, KC_H, COMBO_END};
const uint16_t fun_layer_combo[] PROGMEM = {TD_SFT, SYM, COMBO_END};
const uint16_t num_layer_combo[] PROGMEM = {NAV, KC_SPC, COMBO_END};
const uint16_t game_g_combo[] PROGMEM = {KC_B, KC_G, COMBO_END};
const uint16_t game_b_combo[] PROGMEM = {KC_G, KC_V, COMBO_END};

combo_t key_combos[] = {
    [L_SHIFT_COMBO] = COMBO(l_shift_combo, TD_SFT),
    [R_SHIFT_COMBO] = COMBO(r_shift_combo, RD_SFT),
    [CAPS_LOCK_COMBO] = COMBO(caps_lock_combo, KC_CAPS),
    [CAPS_WORD_COMBO] = COMBO(caps_word_combo, CW_TOGG),
    [ESAPE_COMBO] = COMBO(escape_combo, KC_ESC),
    [V_COMBO] = COMBO(kc_v_combo, KC_V),
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
    [GAME_G_COMBO] = COMBO(game_g_combo, KC_G),
    [GAME_B_COMBO] = COMBO(game_b_combo, KC_B),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    //combo index, i.e. its name from enum.
    switch (index) {
        case L_SHIFT_COMBO:
        case R_SHIFT_COMBO:
            return 14;
        case FUN_LAYER_COMBO:
        case NUM_LAYER_COMBO:
            return 45;
    }
    return COMBO_TERM;
}

//Callback to replicate layer_state_is(layer) for default layer state
layer_state_t default_layer_state;

bool default_layer_state_is(layer_state_t layer) {
    return (default_layer_state & ((layer_state_t)1 << layer)) != 0;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    //disable and enable some left hand combos when on game layer
    switch (combo_index) {
        case GAME_G_COMBO:
        case GAME_B_COMBO:
            return default_layer_state_is(_GAME);
        case L_SHIFT_COMBO:
        case V_COMBO ... Z_COMBO:
        case L_BRACKET_COMBO ... R_ABK_COMBO:
            return !default_layer_state_is(_GAME);
    }
    return true;
}
