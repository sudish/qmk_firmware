ifneq ("$(wildcard $(USER_PATH)/sudish.c)","")
    SRC += sudish.c
endif

SPACE_CADET_ENABLE = no

RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    ifneq ("$(wildcard $(USER_PATH)/rgb_matrix_user.inc)","")
        RGB_MATRIX_CUSTOM_USER ?= yes
    endif
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dances.c
endif


# ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
#     SRC += secrets.c
# endif

# ifeq ($(strip $(NO_SECRETS)), yes)
#     OPT_DEFS += -DNO_SECRETS
# endif

# ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
#     SRC += rgb_stuff.c
#     ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
#         OPT_DEFS += -DINDICATOR_LIGHTS
#     endif
#     ifeq ($(strip $(RGBLIGHT_TWINKLE)), yes)
#         OPT_DEFS += -DRGBLIGHT_TWINKLE
#     endif
#     ifeq ($(strip $(RGBLIGHT_NOEEPROM)), yes)
#         OPT_DEFS += -DRGBLIGHT_NOEEPROM
#     endif
#     ifeq ($(strip $(RGBLIGHT_STARTUP_ANIMATION)), yes)
#         OPT_DEFS += -DRGBLIGHT_STARTUP_ANIMATION
#     endif
# endif

# ifeq ($(strip $(MACROS_ENABLED)), yes)
#     OPT_DEFS += -DMACROS_ENABLED
# endif

# ifdef CONSOLE_ENABLE
#     ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
#         OPT_DEFS += -DKEYLOGGER_ENABLE
#     endif
# endif

# ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
#     OPT_DEFS += -DMAKE_BOOTLOADER
# endif
