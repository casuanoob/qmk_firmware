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
SRC += delay.c

# Include compose source and flags if support is enabled.
ifeq ($(strip $(COMPOSE_ENABLE)), yes)
	SRC += compose.c
	OPT_DEFS += -DCOMPOSE_ENABLE
endif

# Include compose source and flags if support is enabled.
ifeq ($(strip $(KEYMAP_ENABLE)), default)
	SRC += keymaps/default.c
endif

# Include compose source and flags if support is enabled.
ifeq ($(strip $(KEYMAP_ENABLE)), lite)
	SRC += keymaps/default.c
	OPT_DEFS += -DKEYMAP_DEFAULT_LITE
endif
