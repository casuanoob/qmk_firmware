#include QMK_KEYBOARD_H
#include "quantum/rgb_matrix/rgb_matrix.h"
#include "quantum/rgblight/rgblight_list.h"

enum layer_names {
  BASE,  // Default, alpha, layer.
  _DEV,  // Characters heavily used when programming.
  _NAV,  // Navigation layer.
  _NUM,  // Number pad.
  _SYM,  // Other special characters commonly found in regular text.
};

enum custom_keycodes {
  // Custom version of these keycodes to add special effects.
  FX_ESC = SAFE_RANGE,  // Auto-unlock OSM Shift.
  FX_RST,               // Changes LEDs color before entering reset mode.
  // Custom version of these keycodes that can't be shifted.
  NS_0,
  NS_1,
  NS_2,
  NS_3,
  NS_4,
  NS_5,
  NS_6,
  NS_7,
  NS_8,
  NS_9,
  NS_BSLS,
  NS_COMM,
  NS_DOT,
  NS_GRV,
  NS_LBRC,
  NS_RBRC,
  NS_SCLN,
  NS_SLSH,
};

// Custom NAV keycodes, for Apple macOS.
#define FX_CUT LCMD(KC_X)
#define FX_COPY LCMD(KC_C)
#define FX_PSTE LCMD(KC_V)

// Spaces navigation.
#define FX_SCRL LGUI(KC_LEFT)
#define FX_SCRR LGUI(KC_RIGHT)

// Mouse keys.
#define FX_MBT1 KC_MS_BTN1
#define FX_MBT2 KC_MS_BTN2
#define FX_MBT3 KC_MS_BTN3

// Home row mods.
#define HOME_A LGUI_T(KC_A)
#define HOME_O LALT_T(KC_O)
#define HOME_E LCTL_T(KC_E)
#define HOME_U LSFT_T(KC_U)

#define HOME_H RSFT_T(KC_H)
#define HOME_T RCTL_T(KC_T)
#define HOME_N RALT_T(KC_N)
#define HOME_S RGUI_T(KC_S)

// Layers.
#define SPC_NAV LT(_NAV, KC_SPC)
#define TAB_DEV LT(_DEV, KC_TAB)
#define ESC_SYM LT(_SYM, KC_ESC)
#define ENT_NUM LT(_NUM, KC_ENT)

// Tap dances.
#define OSM_SFT OSM(MOD_LSFT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_split_3x5_3(
  // ╭────────────────────────────────────────────╮ ╭────────────────────────────────────────────╮
       KC_QUOT, NS_COMM,  NS_DOT,    KC_P,    KC_Y,      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
        HOME_A,  HOME_O,  HOME_E,  HOME_U,    KC_I,      KC_D,  HOME_H,  HOME_T,  HOME_N,  HOME_S,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       NS_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,
  // ╰────────────────────────────────────────────┤ ├────────────────────────────────────────────╯
                         TAB_DEV, SPC_NAV, OSM_SFT,   ESC_SYM, ENT_NUM, XXXXXXX
  //                   ╰──────────────────────────╯ ╰──────────────────────────╯
  ),

  [_DEV] = LAYOUT_split_3x5_3(
  // ╭────────────────────────────────────────────╮ ╭────────────────────────────────────────────╮
        FX_RST, EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX,   NS_BSLS, KC_LCBR, KC_AMPR, KC_RCBR, KC_PIPE,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,   KC_CIRC, KC_LPRN, KC_ASTR, KC_RPRN,  KC_DLR,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_QUES, NS_SLSH, KC_TILD, XXXXXXX,
  // ╰────────────────────────────────────────────┤ ├────────────────────────────────────────────╯
                         TAB_DEV, XXXXXXX, XXXXXXX,    FX_ESC,  KC_ENT, XXXXXXX
  //                   ╰──────────────────────────╯ ╰──────────────────────────╯
  ),

  [_NAV] = LAYOUT_split_3x5_3(
  // ╭────────────────────────────────────────────╮ ╭────────────────────────────────────────────╮
       FX_SCRL, FX_MBT3, FX_MBT1, FX_MBT2, FX_SCRR,   KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       XXXXXXX, FX_PSTE, FX_COPY,  FX_CUT, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰────────────────────────────────────────────┤ ├────────────────────────────────────────────╯
                         XXXXXXX, SPC_NAV, XXXXXXX,    FX_ESC,  KC_ENT, XXXXXXX
  //                   ╰──────────────────────────╯ ╰──────────────────────────╯
  ),

  [_NUM] = LAYOUT_split_3x5_3(
  // ╭────────────────────────────────────────────╮ ╭────────────────────────────────────────────╮
       KC_PEQL,    NS_7,    NS_8,    NS_9, KC_PDOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       KC_COLN,    NS_4,    NS_5,    NS_6, KC_PPLS,   XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       KC_PSLS,    NS_1,    NS_2,    NS_3, KC_PAST,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰────────────────────────────────────────────┤ ├────────────────────────────────────────────╯
                         KC_BSPC,    NS_0, KC_MINS,   XXXXXXX, ENT_NUM, XXXXXXX
  //                   ╰──────────────────────────╯ ╰──────────────────────────╯
  ),

  [_SYM] = LAYOUT_split_3x5_3(
  // ╭────────────────────────────────────────────╮ ╭────────────────────────────────────────────╮
       XXXXXXX,   KC_LT,  NS_GRV,   KC_GT, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,  FX_RST,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       XXXXXXX, NS_LBRC, KC_PERC, NS_RBRC, XXXXXXX,   XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├────────────────────────────────────────────┤ ├────────────────────────────────────────────┤
       XXXXXXX, KC_EXLM,   KC_AT, KC_HASH, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰────────────────────────────────────────────┤ ├────────────────────────────────────────────╯
                          KC_TAB,  KC_SPC, KC_UNDS,   ESC_SYM, XXXXXXX, XXXXXXX
  //                   ╰──────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

static void _maybe_clear_oneshot_locked_mods(void) {
  const uint8_t locked_mods = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
  if (locked_mods) {
    // Clear any locked one-shot mod, if enabled.  The only one-shot layer in
    // this layout is the one-shot shift layer, so it is safe to clear all
    // locked mods.
    del_mods(locked_mods);
    clear_oneshot_locked_mods();
  }
}

#ifndef NO_SHIFT_CODE
#define NO_SHIFT_CODE(keycode)                          \
  {                                                     \
    if (record->event.pressed) {                        \
      const uint8_t mods = get_mods() & MOD_MASK_SHIFT; \
      if (mods) {                                       \
        del_mods(mods);                                 \
        register_code(keycode);                         \
        add_mods(mods);                                 \
      } else {                                          \
        register_code(keycode);                         \
      }                                                 \
    } else {                                            \
      unregister_code(keycode);                         \
    }                                                   \
    break;                                              \
  }
#endif  // NO_SHIFT_CODE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ESC_SYM: {
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          _maybe_clear_oneshot_locked_mods();
          register_code(KC_ESC);
        } else {
          unregister_code(KC_ESC);
        }
        // Do not continue with the default tap action if the LT was pressed or
        // released, but not held.
        return false;
      }
      break;
    }
    case FX_ESC: {
      if (record->event.pressed) {
        _maybe_clear_oneshot_locked_mods();
        register_code(KC_ESC);
      } else {
        unregister_code(KC_ESC);
      }
      break;
    }
    case FX_RST: {
      if (record->event.pressed) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
        rgb_matrix_sethsv_noeeprom(HSV_RED);
      } else {
        reset_keyboard();
      }
      break;
    }
    case NS_0:
      NO_SHIFT_CODE(KC_0);
    case NS_1:
      NO_SHIFT_CODE(KC_1);
    case NS_2:
      NO_SHIFT_CODE(KC_2);
    case NS_3:
      NO_SHIFT_CODE(KC_3);
    case NS_4:
      NO_SHIFT_CODE(KC_4);
    case NS_5:
      NO_SHIFT_CODE(KC_5);
    case NS_6:
      NO_SHIFT_CODE(KC_6);
    case NS_7:
      NO_SHIFT_CODE(KC_7);
    case NS_8:
      NO_SHIFT_CODE(KC_8);
    case NS_9:
      NO_SHIFT_CODE(KC_9);
    case NS_BSLS:
      NO_SHIFT_CODE(KC_BSLASH);
    case NS_COMM:
      NO_SHIFT_CODE(KC_COMMA);
    case NS_DOT:
      NO_SHIFT_CODE(KC_DOT);
    case NS_GRV:
      NO_SHIFT_CODE(KC_GRAVE);
    case NS_LBRC:
      NO_SHIFT_CODE(KC_LBRC);
    case NS_RBRC:
      NO_SHIFT_CODE(KC_RBRC);
    case NS_SCLN:
      NO_SHIFT_CODE(KC_SCOLON);
    case NS_SLSH:
      NO_SHIFT_CODE(KC_SLASH);
  }
  return true;
};

/**
 * Apply default/startup RGB matrix values.
 *
 * This is to replace the missing `rgb_matrix_reload_from_eeprom()`.
 */
static void _rgb_matrix_reset_noeeprom(void) {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv_noeeprom(RGB_MATRIX_STARTUP_HSV);
  rgb_matrix_set_speed_noeeprom(RGB_MATRIX_STARTUP_SPD);
}

/**
 * Called on layer change.
 *
 * This is called automatically by the QMK framework when the active layer
 * changes.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case BASE:
      _rgb_matrix_reset_noeeprom();
      break;
    case _DEV:
    case _SYM:
      rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
      rgb_matrix_sethsv_noeeprom(HSV_PINK);
      break;
  }
  return state;
}

/**
 * Thin wrapper around rgb_matrix_set_color that takes a HSV instead of RGB, and
 * caps the value component to RGB_MATRIX_MAXIMUM_BRIGHTNESS.
 */
static void _rgb_matrix_sethsv_noeeprom(uint8_t index, uint8_t h, uint8_t s,
                                        uint8_t v) {
  const HSV hsv = {
      .h = h,
      .s = s,
      .v = MIN(v, RGB_MATRIX_MAXIMUM_BRIGHTNESS),
  };
  const RGB rgb = hsv_to_rgb(hsv);
  rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

/**
 * Called during every cycle.
 *
 * Per-key RGB configuration must go in this callback to be properly applied.
 */
void rgb_matrix_indicators_user(void) {
  switch (get_highest_layer(layer_state)) {
    case _NUM:
    case _NAV:
      _rgb_matrix_sethsv_noeeprom(22, HSV_YELLOW);
      _rgb_matrix_sethsv_noeeprom(25, HSV_YELLOW);
      _rgb_matrix_sethsv_noeeprom(26, HSV_YELLOW);
      _rgb_matrix_sethsv_noeeprom(28, HSV_YELLOW);
      break;
  }
}

/**
 * Called when a one-shot layer "lock" status changes.
 *
 * This is called automatically by the QMK framework when a one-shot layer is
 * activated and deactivated.
 * The only one-shot layer in this layout is the one-shot shift layer.  Turns
 * the RGBs solid blue when this layer is activated, and back to default when
 * deactivated.
 */
void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  } else if (!mods) {
    _rgb_matrix_reset_noeeprom();  // Load default values.
  }
}

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Pinky and ring fingers.
    case HOME_A:
    case HOME_O:
    case HOME_N:
    case HOME_S:
      return TAPPING_TERM + 125;
    // Index fingers.
    case HOME_U:
    case HOME_H:
      return TAPPING_TERM + 25;
    default:
      return TAPPING_TERM;
  }
}
#endif  // TAPPING_TERM_PER_KEY

#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  return keycode != OSM_SFT;
}
#endif  // TAPPING_FORCE_HOLD_PER_KEY

#if 0
void keyboard_post_init_user(void) {
}
#endif

void eeconfig_init_user(void) {
  rgb_matrix_mode(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv(RGB_MATRIX_STARTUP_HSV);
  rgb_matrix_set_speed(RGB_MATRIX_STARTUP_SPD);
}
