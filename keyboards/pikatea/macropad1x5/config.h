/*
Copyright 2021 Leon Stubbig <leonskeyboards@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID 0x0801
#define PRODUCT_ID 0x1133
#define DEVICE_VER 0x0001
#define MANUFACTURER LS Keyboards
#define PRODUCT Macropad1x5(rev1)
#define DESCRIPTION 1x5 Macropad with Rotary Encoder

// Keyboard Matrix Assignments
#define MATRIX_ROWS 1
#define MATRIX_COLS 5
#define DIODE_DIRECTION COL2ROW
#define MATRIX_COL_PINS \
  { D1, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS \
  { F7 }

// Encoder
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A \
  { D0 }
#define ENCODERS_PAD_B \
  { D4 }

// Debounce reduces chatter (unintended double-presses).
#define DEBOUNCE 5

// Only use 8 bits for layers (using less that 8 layers).
#define LAYER_STATE_8BIT
