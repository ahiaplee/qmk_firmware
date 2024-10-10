#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE)
#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_SIMPLE_math(HSV hsv, uint16_t offset) {
#            ifdef RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
    hsv.h = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 8) >> 4);
#            endif

    // return original colour if offset is max
    if(offset == 255){
        return hsv;
    }

    // slowly lerp the colour back to the original
    hsv.h = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 8) >> 4);


    // make pressed keys slightly brighter than the settings
    uint8_t led_v = 255 - offset;
    
    // clamp the value between min(255, v  * 1.5)
    uint8_t upper_bound = qadd8(hsv.v, hsv.v >> 2);
    led_v = led_v > upper_bound ? upper_bound : led_v;
    hsv.v = qadd8(hsv.v, led_v);

    return hsv;
}

bool SOLID_REACTIVE_SIMPLE(effect_params_t* params) {
    return effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_math);
}

#        endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif     // ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif         // RGB_MATRIX_KEYREACTIVE_ENABLED
