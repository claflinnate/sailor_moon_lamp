bool moon_needs_setup = true;
bool dimming = true;
bool not_dimming = false;
uint32_t moon_count = 0;
long moon_millis = 0;
void twinkle_moon(long global_millis) {
  if (moon_millis == 0) {
    moon_millis = global_millis;
  }
  if ((global_millis - moon_millis) > 10) {
    moon_millis = global_millis;
    
    if (moon_needs_setup) {
        strip1.fill(strip1.Color(255, 255, 255), MOON_OFFSET, MOON_OFFSET + 15);
        num_leds = (random(3) + 1);
        rand_led = 0;
        led_used = false;

        for (int i = 0; i < num_leds; i++) {
            rand_led = MOON_OFFSET + random(15);
            while (led_used) {
                led_used = false;
                for (int j = 0; j < num_leds; j++) {
                    if (rand_led == leds[j]) {
                        led_used = true;
                        rand_led = MOON_OFFSET + random(15);
                    }
                }
            }
            leds[i] = rand_led;
            leds_colors[i] = strip1.getPixelColor(leds[i]);
        }
        moon_needs_setup = false;
    }

      if ((all_leds_zero != 0) && dimming) {
          //for (int i = 0; i < num_leds * 31; i++) {
          all_leds_zero = 0;
          for (int led = 0; led < num_leds; led++) {
              current_color = leds_colors[led];
              if (current_color != 0) {
                  current_color = decrement_color(current_color);
                  leds_colors[led] = current_color;
                  strip1.setPixelColor(leds[led], current_color);

              }
          }
          //strip1.show();
          for (int led = 0; led < num_leds; led++) {
              all_leds_zero |= leds_colors[led];
          }
          if (all_leds_zero == 0) {
              dimming = false;
              not_dimming = true;
          }
      }
      all_leds_zero = 255;


      if (not_dimming && (all_leds_255 < ((254 << 16) | (254 << 8) | 25))) {

          all_leds_255 = (255 << 16) | (255 << 8) | 255;
          //Serial.println("before 1st for");
          for (int led = 0; led < num_leds; led++) {

              current_color = leds_colors[led];
              if (current_color != ((255 << 16) | (255 << 8) | (255))) {
                  current_color = increment_color(current_color);
                  leds_colors[led] = current_color;
                  strip1.setPixelColor(leds[led], current_color);
              }
              //strip1.show();
          }
          //Serial.println("before 2nd for");
          for (int led = 0; led < num_leds; led++) {
              all_leds_255 = all_leds_255 & leds_colors[led];
          }
          if (all_leds_255 == ((255 << 16) | (255 << 8) | (255))) {
              dimming = true;
              not_dimming = false;
              moon_needs_setup = 1;
          }
      }
      all_leds_255 = 0;
      
  strip1.show();
  }
}
