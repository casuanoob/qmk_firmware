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

//#include <qp.h>

// clang-format off
#define _LAYOUT(                                             \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                          k33, k34, k35, k36)                \
    LAYOUT_split_3x5_3(                                      \
           k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
           k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
           k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
                    KC_A, k33, k34, k35, k36, KC_B)
// clang-format on

#define LAYOUT(...) _LAYOUT(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_nAPTmak] = LAYOUT(nAPTmak_split_3x5_2),
  [_CLMKdh] = LAYOUT(COLEMAKdhm_split_3x5_2),
  [_NRSTex] = LAYOUT(NRSTex_split_3x5_2),
  [_ADEPT] = LAYOUT(ADEPT_split_3x5_2),
  [_APTm] = LAYOUT(APTmod_split_3x5_2),
  [_APT3] = LAYOUT(APTv3_split_3x5_2),
  [_CAN] = LAYOUT(Canary_split_3x5_2),
  [_NERPS] = LAYOUT(Nerps_split_3x5_2),
  [_GAME] = LAYOUT(GAMING_split_3x5_2),
  [_NAV] = LAYOUT(NAV_split_3x5_2),
  [_SYM] = LAYOUT(SYM_split_3x5_2),
  [_NUM] = LAYOUT(NUMBER_split_3x5_2),
  [_NUMPD] = LAYOUT(NUMPAD_split_3x5_2),
  [_FUN] = LAYOUT(FUN_split_3x5_2),
  [_SPEC] = LAYOUT(SPEC_split_3x5_2),
  [_MOUSE] = LAYOUT(MOUSE_split_3x5_2),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_nAPTmak] =    { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_CLMKdh] =     { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NRSTex] =     { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_ADEPT] =      { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_APTm] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_APT3] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_CAN] =        { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NERPS] =      { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_GAME] =       { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NAV] =        { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_SYM] =        { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NUM] =        { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NUMPD] =      { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_FUN] =        { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [_SPEC] =       { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [_MOUSE] =      { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

// Triple nop delay thing lol
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}

//static painter_device_t display;

void keyboard_post_init_user_keymap(void) {
  // Keep debug off on boot to toggle on as needed.
  debug_enable=false;
  debug_matrix=false;
  //debug_keyboard=true;
  //debug_mouse=false;
  //display = qp_st7789_make_spi_device(240, 280, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
}

// Turn off per key rgb but keep underglow.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  for (uint8_t i = led_min; i <= led_max; i++) {
    //if(user_config.rgb_per_key_enabled) {
        if (!HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) { // 0x02 == LED_FLAG_MODIFIER
          rgb_matrix_set_color(i, RGB_OFF);
        }
    //}
  }
  return false;
}

//painter_device_t qp_st7789_make_spi_device(uint16_t 240, uint16_t 280, pin_t GP12, pin_t GP11, pin_t GP13, uint16_t spi_divisor, int spi_mode);
