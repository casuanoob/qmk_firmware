SRC += delay.c

ifeq ($(strip $(COMPOSE_ENABLE)), yes)
  SRC += compose.c
  OPT_DEFS += -DCOMPOSE_ENABLE
endif
