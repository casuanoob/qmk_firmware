# Explicitly enable debug if needed.
DEBUG_ENABLE = no

# Disable unused features that are enabled by default.
ifndef GRAVE_ESC_ENABLE
	GRAVE_ESC_ENABLE = no
endif
ifndef MAGIC_ENABLE
	MAGIC_ENABLE = no
endif
ifndef SPACE_CADET_ENABLE
	SPACE_CADET_ENABLE = no
endif

# Include common sources.
SRC += $(USER_PATH)/keymap.c
SRC += $(USER_PATH)/features/achordion.c
SRC += $(USER_PATH)/features/compose.c
SRC += $(USER_PATH)/features/custom_shift_keys.c
SRC += $(USER_PATH)/features/oneshot_mod.c
SRC += $(USER_PATH)/features/tap_dance.c

CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
