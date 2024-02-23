# Loads /users/casuanoob userspace.
USER_NAME := casuanoob
KEYMAP_ENABLE = split34  # Use "split34" keymap (from /users/casuanoob).

CONSOLE_ENABLE        	= yes
DEBUG_ENABLE		  	= yes
WPM_ENABLE            	= no
ENCODER_ENABLE		  	= yes
ENCODER_MAP_ENABLE 		= yes

VIA_ENABLE = no
DEBOUNCE_TYPE = asym_eager_defer_pk

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi
#DEFERRED_EXEC_ENABLE = yes
QUANTUM_PAINTER_SUPPORTS_256_PALETTE = yes
SRC += suisei.qgf.c
SRC += ghost3_crop.qgf.c

BACKLIGHT_ENABLE = yes

#EXTRALDFLAGS = -Wl,--defsym,FLASH_LEN=8192k
