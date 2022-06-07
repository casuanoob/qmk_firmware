# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

AUDIO_SUPPORTED = no        # Audio is not supported
RGB_MATRIX_SUPPORTED = yes  # RGB matrix is supported and enabled by default
RGBLIGHT_SUPPORTED = yes    # RGB underglow is supported, but not enabled by default
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix functionality
RGB_MATRIX_DRIVER = WS2812

# Charybdis nano is a split 3x5 keyboard with a maximum of 3 thumb keys (2 on
# the trackball side).
SPLIT_KEYBOARD = yes
LAYOUTS = split_3x5_3 # Support community layout, in particular Manna-Harbour's Miryoku layout

POINTING_DEVICE_ENABLE = yes # Enable trackball
POINTING_DEVICE_DRIVER = pmw3360
# https://qmk.fm/changes/2018-11-16-use-a-single-endpoint-for-hid-reports
<<<<<<< HEAD
MOUSE_SHARED_EP = yes # Unify multiple HID interfaces into a single Endpoint
=======
MOUSE_SHARED_EP = no # Unify multiple HID interfaces into a single Endpoint
>>>>>>> ac19e2581d36d9bb0fec7132d4e50fb1f16264a0
KEYBOARD_SHARED_EP = yes

EEPROM_DRIVER = spi
WS2812_DRIVER = pwm
SERIAL_DRIVER = usart

DEBOUNCE_TYPE = asym_eager_defer_pk
