//#include "defines.h"
uint32_t colors[2] = { 0xFF00FF,0xFF00FF };
uint32_t current_handle_color = 0;
uint32_t handle_count = 0;
long handle_millis = 0;
void spin_handle(long global_millis) {
  if (handle_millis == 0) {
    handle_millis = global_millis;
  }
  if ((global_millis - handle_millis) > 1000) {
    handle_millis = global_millis;
  	current_handle_color = (current_handle_color +1)%2;
  	for (int i = HANDLE_OFFSET; i < BALL_OFFSET; i++) {
  		if ((i % 2) == 0)  {
  			strip1.setPixelColor(i, colors[current_handle_color]);
  		}
  		else {
  			strip1.setPixelColor(i, colors[(current_handle_color+1)%2]);
  		}
  	}
  }
}
