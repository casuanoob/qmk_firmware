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

#include "dilemma.h"

// clang-format off
#define LAYOUT(                                                   \
  kaa, ka0, ka1, ka2, ka3, ka4,     kb4, kb3, kb2, kb1, kb0, kba, \
  k0a, k00, k01, k02, k03, k04,     k44, k43, k42, k41, k40, k4a, \
  k1a, k10, k11, k12, k13, k14,     k54, k53, k52, k51, k50, k5a, \
  k2a, k20, k21, k22, k23, k24,     k64, k63, k62, k61, k60, k6a, \
            k32, k30, k31, k33,     k73, k71, k70, k72            \
)                                                                 \
{                                                                 \
  {   kaa,   ka0,   ka1,   ka2,   ka3,   ka4 },                   \
  {   k0a,   k00,   k01,   k02,   k03,   k04 },                   \
  {   k1a,   k10,   k11,   k12,   k13,   k14 },                   \
  {   k2a,   k20,   k21,   k22,   k23,   k24 },                   \
  {   KC_NO, k30,   k31,   k32,   k33, KC_NO },                   \
  {   kba,   kb0,   kb1,   kb2,   kb3,   kb4 },                   \
  {   k4a,   k40,   k41,   k42,   k43,   k44 },                   \
  {   k5a,   k50,   k51,   k52,   k53,   k54 },                   \
  {   k6a,   k60,   k61,   k62,   k63,   k64 },                   \
  {   KC_NO, k70,   k71,   k72,   k73, KC_NO },                   \
}
// clang-format on
