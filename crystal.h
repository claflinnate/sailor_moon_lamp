uint32_t crystal_colors[3] = { 0xFF00FF,0x0,0x0 };
uint32_t current_crystal_color = 0;
uint32_t crystal_count = 0;
long crystal_millis = 0;
void spin_crystal(long global_millis) {
  if (crystal_millis == 0) {
    crystal_millis = global_millis;
  }
  if ((global_millis - crystal_millis) > 100) {
    crystal_millis = global_millis;
    crystal_count += 1;
    crystal_count %= 10;
    current_crystal_color = (current_crystal_color + 1) % 3;
    for (int i = CRYSTAL_OFFSET; i < MOON_OFFSET; i++) {
        strip1.setPixelColor(i, crystal_colors[(current_crystal_color+i)%3]);
    }
  }
}
