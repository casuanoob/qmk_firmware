# MCU name
<<<<<<< HEAD
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu
=======
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu
>>>>>>> ac19e2581d36d9bb0fec7132d4e50fb1f16264a0

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
<<<<<<< HEAD
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
<<<<<<< HEAD:keyboards/bastardkb/scylla/v1/elitec/rules.mk
=======
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
>>>>>>> ac19e2581d36d9bb0fec7132d4e50fb1f16264a0

AUDIO_SUPPORTED = no        # Audio is not supported
RGB_MATRIX_SUPPORTED = yes  # RGB matrix is supported and enabled by default
RGBLIGHT_SUPPORTED = yes    # RGB underglow is supported, but not enabled by default
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support

SPLIT_KEYBOARD = yes
<<<<<<< HEAD
=======
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
WS2812_DRIVER = pwm         # Driver for RGB
>>>>>>> ac19e2581d36d9bb0fec7132d4e50fb1f16264a0:keyboards/yandrstudio/nz64/rules.mk
=======
>>>>>>> ac19e2581d36d9bb0fec7132d4e50fb1f16264a0
