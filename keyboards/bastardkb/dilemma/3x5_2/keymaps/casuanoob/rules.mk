# Keymap supports OLED screen. Not enabled by default.
OLED_DRIVER = custom
OLED_SUPPORTED = yes
OLED_ENABLE           = yes
CAPS_WORD_ENABLE      = yes
CONSOLE_ENABLE        = yes
KEYLOGGER_ENABLE      = no
WPM_ENABLE            = yes

# Loads /users/casuanoob userspace.
USER_NAME := casuanoob

KEYMAP_ENABLE = split34  # Use "split34" keymap (from /users/casuanoob).
ONESHOT_MOD_ENABLE = yes

TAP_DANCE_ENABLE = no
TD_ONESHOT_SHIFT_ENABLE = no
TD_ONESHOT_DRAGSCROLL_ENABLE = no

COMBO_ENABLE = yes

# Speed testing
LTO_ENABLE = no

DEBOUNCE_TYPE = asym_eager_defer_pk
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = yes
