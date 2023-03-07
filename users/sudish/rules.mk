MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

INTROSPECTION_KEYMAP_C = sudish.c

LTO_ENABLE = yes  # if firmware size over limit, try this option

RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    ifneq ("$(wildcard $(USER_PATH)/rgb_matrix_user.inc)","")
        RGB_MATRIX_CUSTOM_USER ?= yes
    endif
endif
