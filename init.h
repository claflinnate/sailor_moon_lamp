long init_millis = 0;
uint32_t initial_colors[2] = { 0xFF00FF,0xFFFFFF };
uint32_t current_initial_color = 0;
uint32_t active_led_count = 1;
uint32_t max_led_count = (MOON_OFFSET + 15);
uint32_t pulse_count = 0;

void initial_lightup(long global_millis) {
  if (init_millis == 0 ) {
    init_millis = global_millis;
  }
  if ((global_millis - init_millis) > 30) {
    current_initial_color = (current_initial_color+1) % 1;

    for (int i = 0; i < active_led_count; i++) {
            
        //if at wand, light up one row at a time 
        //0, 31, 32, 63
        //1, 30, 33, 62
        //2, 29, 34, 61
        if (i < 15) {
                strip1.setPixelColor(i, initial_colors[current_initial_color]);
                strip1.setPixelColor((29 - i), initial_colors[current_initial_color]);
                strip1.setPixelColor(i+30, initial_colors[current_initial_color]);
                strip1.setPixelColor((59 - i), initial_colors[current_initial_color]);

        }
        else {
            if ((i % 2 == 0) && (i > 59)){
                strip1.setPixelColor(i, initial_colors[current_initial_color]);
            }
            else if (i > 59){
                strip1.setPixelColor(i, initial_colors[(current_initial_color + 1) % 2]);
            }
        }
    }
    strip1.show();
    if (active_led_count == 15) {
        active_led_count = 64;
    }
    else {
        active_led_count++;
    }
    if ((active_led_count == max_led_count)) {
        
        initial_light_sequence = false;
    }

  }
}
