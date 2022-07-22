# Loads /users/casuanoob userspace.
USER_NAME := casuanoob

KEYMAP_ENABLE = split34  # Use "split34" keymap (from /users/casuanoob).
ONESHOT_MOD_ENABLE = yes

TAP_DANCE_ENABLE = no
TD_ONESHOT_SHIFT_ENABLE = no
TD_ONESHOT_DRAGSCROLL_ENABLE = no

COMBO_ENABLE = yes

NKRO_ENABLE = yes

# testing encoder function
ENCODER_ENABLE = yes
#testing encoder switch function, guard against blackpill build as mine has the switch wired into the matrix
ifneq ($(strip $(BOARD)), BLACKPILL_STM32_F411) 
DIP_SWITCH_ENABLE = no
LTO_ENABLE = no
endif 

# Speed testing
#LTO_ENABLE = no
#OPT = fast
CONSOLE_ENABLE = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

CAPS_WORD_ENABLE = yes

MOUSEKEY_ENABLE = yes