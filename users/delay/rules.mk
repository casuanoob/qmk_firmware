# Explicitly enable debug if needed.
DEBUG_ENABLE = no

# Enable optimizations by default.
LINK_TIME_OPTIMIZATION = yes

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
SRC += $(USER_PATH)/delay.c $(USER_PATH)/platform.c

# Include compose source and flags if enabled.
ifeq ($(strip $(COMPOSE_ENABLE)), yes)
	SRC += $(USER_PATH)/compose.c
	OPT_DEFS += -DCOMPOSE_ENABLE
endif

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

# Include split36 keymap source and flags if enabled.
ifeq ($(strip $(KEYMAP_ENABLE)), split36)
	SRC += $(USER_PATH)/keymaps/split36.c
	OPT_DEFS += -DDELAY_KEYMAP_SPLIT36
	DEFERRED_EXEC_ENABLE = yes
endif

# Include split36-homerow keymap source and flags if enabled.
ifeq ($(strip $(KEYMAP_ENABLE)), split36-homerow)
	SRC += $(USER_PATH)/keymaps/split36-homerow.c
	OPT_DEFS += -DDELAY_KEYMAP_SPLIT36_HOMEROW
endif

# Include split36-homerow-lite source and flags if enabled.
ifeq ($(strip $(KEYMAP_ENABLE)), split36-homerow-lite)
	SRC += $(USER_PATH)/keymaps/split36-homerow.c
	OPT_DEFS += -DDELAY_KEYMAP_SPLIT36_HOMEROW
	OPT_DEFS += -DDELAY_KEYMAP_SPLIT36_HOMEROW_LITE
endif
