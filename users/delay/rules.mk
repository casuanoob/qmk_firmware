# Explicitly enable debug if needed.
DEBUG_ENABLE = no

# Disable unused features that are enabled by default.
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no

# Enable those features on a keymap-basis.
COMBO_ENABLE = no
EXTRAKEY_ENABLE = no
LEADER_ENABLE = no
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = no
TERMINAL_ENABLE = no
UNICODE_ENABLE = no
VIA_ENABLE = no

# Enable optimizations by default.
LINK_TIME_OPTIMIZATION = yes

# Include common sources.
SRC += delay.c

# Include compose source and flags if support is enabled.
ifeq ($(strip $(COMPOSE_ENABLE)), yes)
  SRC += compose.c
  OPT_DEFS += -DCOMPOSE_ENABLE
endif
