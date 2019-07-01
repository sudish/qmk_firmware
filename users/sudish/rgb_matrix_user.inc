// !!! DO NOT ADD #pragma once !!! //

RGB_MATRIX_EFFECT(only_underglow)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
extern led_config_t g_led_config;

// Blanks all but the underglow LEDs
static bool only_underglow(effect_params_t* params) {
  if (!params->init) {
    return false;
  }

  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
      rgb_matrix_set_color(i, 0, 0, 0);
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
