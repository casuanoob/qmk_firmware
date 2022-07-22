# Explicitly enable debug if needed.
DEBUG_ENABLE = no

# Enable optimizations by default.
# LINK_TIME_OPTIMIZATION = yes

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

# Include tap-dances source and flags if enabled.
ifeq ($(strip $(TD_ONESHOT_SHIFT_ENABLE)), yes)
	TAP_DANCE_ENABLE = yes
	SRC += $(USER_PATH)/tap_dance.c
	OPT_DEFS += -DTD_ONESHOT_SHIFT_ENABLE
endif

# Include tap-dances source and flags if enabled.
# This feature only works for the charybdis.
ifeq ($(strip $(TD_ONESHOT_DRAGSCROLL_ENABLE)), yes)
	TAP_DANCE_ENABLE = yes
	SRC += $(USER_PATH)/tap_dance.c
	OPT_DEFS += -DTD_ONESHOT_DRAGSCROLL_ENABLE
endif

# Include oneshot mods.
ifeq ($(strip $(ONESHOT_MOD_ENABLE)), yes)
	SRC += $(USER_PATH)/oneshot_mod.c
	OPT_DEFS += -DONESHOT_MOD_ENABLE
endif

# Include split34 keymap source and flags if enabled.
ifeq ($(strip $(KEYMAP_ENABLE)), split34)
	SRC += $(USER_PATH)/keymaps/split34.c
	OPT_DEFS += -DDELAY_KEYMAP_SPLIT34
	DEFERRED_EXEC_ENABLE = yes
endif

# Drashna's OLED driver for SH1107.
ifeq ($(strip $(OLED_DRIVER)), custom)
ifeq ($(strip $(OLED_ENABLE)), yes)
	OPT_DEFS += -DOLED_ENABLE -DOLED_DRIVER_SH1107
	SRC += $(USER_PATH)/oled/sh110x.c
	QUANTUM_LIB_SRC += i2c_master.c
	DEFERRED_EXEC_ENABLE = yes
endif
endif