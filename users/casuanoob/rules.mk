# Explicitly enable debug if needed.
#DEBUG_ENABLE = no
#CONSOLE_ENABLE = no

# Disable unused features that are enabled by default.
ifndef GRAVE_ESC_ENABLE
	GRAVE_ESC_ENABLE = no
endif
ifndef MAGIC_ENABLE
	MAGIC_ENABLE = yes
endif
ifndef SPACE_CADET_ENABLE
	SPACE_CADET_ENABLE = no
endif

# Include common sources.
SRC += $(USER_PATH)/delay.c

# Include callum-style oneshot mods.
SRC += $(USER_PATH)/features/oneshot_mod.c

# Include combo source
INTROSPECTION_KEYMAP_C = features/combos.c

# Include split34 keymap source and flags if enabled.
#ifeq ($(strip $(KEYMAP_ENABLE)), split34)
	SRC += $(USER_PATH)/keymaps/split34.c
#endif

DEFERRED_EXEC_ENABLE = yes
TRI_LAYER_ENABLE = yes
CAPS_WORD_ENABLE = yes
REPEAT_KEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
COMBO_ENABLE = yes
NKRO_ENABLE = yes
DEBOUNCE_TYPE = asym_eager_defer_pk

# Drashna's OLED driver for SH1107.
ifeq ($(strip $(OLED_DRIVER)), custom)
ifeq ($(strip $(OLED_ENABLE)), yes)
	OPT_DEFS += -DOLED_ENABLE -DOLED_DRIVER_SH1107
	SRC += $(USER_PATH)/oled/sh110x.c
	QUANTUM_LIB_SRC += i2c_master.c
	DEFERRED_EXEC_ENABLE = yes
endif #OLED_ENABLE
endif #OLED_DRIVER
