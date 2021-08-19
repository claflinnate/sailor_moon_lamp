//#include "defines.h"
uint32_t base_colors[2] = { 0xFF00FF,0xFFFFFF };
uint32_t yrg_colors[3] = { 0xFFFF00,0xFF0000,0x00FF00 };
uint32_t current_base_color = 0;
uint32_t current_yrg_color = 0;
uint32_t ball_count = 0;
long ball_millis = 0;
void spin_ball(long global_millis) {
  if (ball_millis == 0) {
    ball_millis = global_millis;
  }
  if ((global_millis - ball_millis) > 100) {
    ball_millis = global_millis;
    
  	current_base_color = (current_base_color + 1) % 2;
  	current_yrg_color = (current_yrg_color + 1) % 3;
  
  	for (int i = BALL_OFFSET; i < CRYSTAL_OFFSET; i++) {
  		if (((i < BALL_OFFSET+3) || (i > BALL_OFFSET+6)) && ((i % 2) == 0))  {
  			strip1.setPixelColor(i, base_colors[0]);
  		}
  		else if ((i < BALL_OFFSET + 3) || (i > BALL_OFFSET + 6)) {
  			strip1.setPixelColor(i, base_colors[0]);
  			strip1.setPixelColor(BALL_OFFSET+6, base_colors[1]);
  		}
  		else {
  			strip1.setPixelColor(BALL_OFFSET+3, yrg_colors[current_yrg_color]);
  			strip1.setPixelColor(BALL_OFFSET+4, yrg_colors[(current_yrg_color+1)%3]);
  			strip1.setPixelColor(BALL_OFFSET+5, yrg_colors[(current_yrg_color+2)%3]);
  		}
  	}
  }
}
