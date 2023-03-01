// No #pragma once.

// Declare custom effects using the RGB_MATRIX_EFFECT macro (note the lack of
// semicolon after the macro!).
RGB_MATRIX_EFFECT(CYCLE_LED_INDEX)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool CYCLE_LED_INDEX(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
  uint16_t led_index = time % DRIVER_LED_TOTAL;
  for (int i = led_min; i <= led_max; ++i) {
    if (i == led_index) {
      rgb_matrix_set_color(i, RGB_RED);
    } else {
      rgb_matrix_set_color(i, RGB_BLACK);
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS