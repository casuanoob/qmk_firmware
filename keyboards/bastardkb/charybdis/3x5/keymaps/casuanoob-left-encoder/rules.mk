# Loads /users/casuanoob userspace.
USER_NAME := casuanoob
KEYMAP_ENABLE = split34  # Use "split34" keymap (from /users/casuanoob).

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