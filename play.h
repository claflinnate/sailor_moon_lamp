long play_millis = 0;

void play_music_box(long global_millis) {
    if (play_millis == 0) {
      play_millis = global_millis;
    }
    if (((global_millis - play_millis) > (delay_list[delay_index] - delay_list[delay_index-1])) && (delay_index < 58)) {
        play_millis = global_millis;
        delay_index++;
        for (int i = 0; i < LED_COUNT1; i++) {
            if (i % 2 == 0) {
                if (random(2) == 1) {
                    strip1.setPixelColor(i, Colors[random(2)]);
                }
                else {
                    strip1.setPixelColor(i, Colors[0]);
                }
            }
            else {
                if (random(2) == 1) {
                    strip1.setPixelColor(i, Colors[random(2)]);
                }
                else {
                    strip1.setPixelColor(i, Colors[0]);
                }
            }
        }
        strip1.show();
    }
}
