/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (0xcharly)
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

#include "process_unicode_common.h"

enum custom_keycodes {
    UC_HPPY,
    UC_SHRG,
    UC_FPLM,
    UC_FLIP,
};

#define CUT G(KC_X)
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define LANG G(KC_TILDE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
     UC_HPPY, UC_SHRG, UC_FPLM, UC_FLIP,
        COPY,   PASTE,     CUT,   LANG
    ),
};
// clang-format on

static bool process_record_unicode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UC_HPPY: // ᕕ( ᐛ )ᕗ
            if (record->event.pressed) {
                send_unicode_string("ᕕ( ᐛ )ᕗ");
            }
            break;

        case UC_SHRG: // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;

        case UC_FLIP: // (╯°□°）╯︵ ┻━┻
            if (record->event.pressed) {
                send_unicode_string("(╯°□°)╯︵ ┻━┻");
            }
            break;

        case UC_FPLM: // (－‸ლ)
            if (record->event.pressed) {
                send_unicode_string("(－‸ლ)");
            }
            break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_unicode(keycode, record);
}

/**
 * @brief Initialize the default unicode mode on firmware startup.
 */
static void matrix_init_unicode(void) {
    unicode_input_mode_init();
}

void matrix_init_user(void) {
    matrix_init_unicode();
}

void eeconfig_init_user(void) {
    rgblight_mode(RGBLIGHT_DEFAULT_MODE);
}
