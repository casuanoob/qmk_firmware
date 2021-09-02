#pragma once

/**
 * Custom keycodes.
 *
 * Use `SAFE_RANGE_KEYMAP` for keymap specific codes, instead of `SAFE_RANGE`.
 */
enum delay_custom_keycodes {
  COMPOSE = SAFE_RANGE,
  SAFE_RANGE_KEYMAP,
};

#ifdef COMPOSE_ENABLE
/**
 * Use this function to add support for more composition on a per-keymap basis.
 */
void compose_keymap(compose_state_t *state);
#endif  // COMPOSE_ENABLE

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `process_record_*` callback is necessary for each keymap
 * to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `matrix_scan_keymap_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void matrix_scan_keymap(void);

/**
 * Similar to `_kb`, `_user`, and other variants, but for individual keymaps.
 *
 * `_user` is already defined to add common functions to all keymaps, therefore
 * a new version of the `keyboard_post_init_*` callback is necessary for each
 * keymap to add their own.
 *
 * docs.qmk.fm/using-qmk/software-features/feature_userspace#customized-functions.
 */
void keyboard_post_init_keymap(void);
