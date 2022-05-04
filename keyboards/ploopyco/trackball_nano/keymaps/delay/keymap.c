#include QMK_KEYBOARD_H

void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
  if (host_keyboard_led_state().num_lock ||
      host_keyboard_led_state().scroll_lock) {
    mouse_report->v = x == 0 ? 0 : x > 0 ? -1 : 1;
  } else {
    mouse_report->x = -y;
    mouse_report->y = x;
  }
}
