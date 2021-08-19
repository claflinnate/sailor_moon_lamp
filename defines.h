
#define LED_PIN1     18 
#define LED_COUNT1   200
#define HANDLE_OFFSET 0
#define BALL_OFFSET HANDLE_OFFSET + 60
#define CRYSTAL_OFFSET BALL_OFFSET + 7
#define MOON_OFFSET CRYSTAL_OFFSET + 3
#define HANDLE_LENGTH BALL_OFFSET-HANDLE_OFFSET
void POWER_ON_OFF();
void IRAM_ATTR START_STOP_PLAYING();

int waitValue = 10;
uint8_t r_prev, g_prev, b_prev = 0;
uint8_t r_prev_1_a, g_prev_1_a, b_prev_1_a = 0;
uint8_t r_prev_1_b, g_prev_1_b, b_prev_1_b = 0;
uint8_t r_prev_2_a, g_prev_2_a, b_prev_2_a = 0;
uint8_t r_prev_2_b, g_prev_2_b, b_prev_2_b = 0;
uint8_t r_prev_3_a, g_prev_3_a, b_prev_3_a = 0;
uint8_t r_prev_3_b, g_prev_3_b, b_prev_3_b = 0;
uint8_t r_prev_4_a, g_prev_4_a, b_prev_4_a = 0;
uint8_t r_prev_4_b, g_prev_4_b, b_prev_4_b = 0;
uint8_t r_prev_5, g_prev_5, b_prev_5 = 0;


uint32_t Colors[2];
uint32_t INTR_STATUS = 0;
bool state_changed = true;
volatile bool power_state = true; //on by default and restart

bool led_used = false;
bool reset_state = true;

uint32_t current_color = 0;
uint8_t currently_active_pixels = 0;
uint32_t leds[100];
uint32_t leds_colors[100];
uint8_t num_leds = 0;
uint8_t rand_led = 0;
uint32_t all_leds_255 = 0;// (255 << 16) | (255 << 8) | 255;
uint32_t all_leds_zero = 255;
uint32_t try_play_music = 0;
uint32_t try_dfp_count = 0;
bool try_dfp_begin = false;
long debounce_interrupt_millis = 0;
long power_debounce = 0;
long play_debounce = 0;

uint32_t delay_index = 1;

long playing_state_counter = 0;

uint32_t delay_list[] = { 200,599,980,1423,2229,2654,3410,3845,4601,5444,6611,7021,7437,7859,8685,9085,9463,9861,10721,13106,13497,13917,14358,15166,15566,16342,16724,17585,18411,19625,20012,20416,20824,21612,22018,22389,22809,23634,24867,26011,26428,26850,27254,28061,28485,29276,29661,30503,31331,32509,32899,33316,33723,34564,35408,35893,36820,36821 };


Adafruit_NeoPixel strip1(LED_COUNT1, LED_PIN1, NEO_GRB + NEO_KHZ800);

bool initial_light_sequence = true;

inline uint32_t decrement_color(uint32_t input_color) {
    signed int r = input_color & 0xFF;
    signed int g = (input_color >> 8) & 0xFF;
    signed int b = (input_color >> 16) & 0xFF;

    r -= 2;
    if (r < 3) {
        r = 0;
    }
    g -= 2;
    if (g < 3) {
        g = 0;
    }
    b -= 2;
    if (b < 3) {
        b = 0;
    }
    return (b << 16) | (g << 8) | r;
}

inline uint32_t increment_color(uint32_t input_color) {
    uint32_t r = input_color & 0xFF;
    uint32_t g = (input_color >> 8) & 0xFF;
    uint32_t b = (input_color >> 16) & 0xFF;

    r += 2;
    if (r > 251) {
        r = 255;
    }

    g += 2;
    if (g > 251) {
        g = 255;
    }
    b += 2;
    if (b > 251) {
        b = 255;
    }
    return (b << 16) | (g << 8) | r;
}

#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include "ESP32TimerInterrupt.h"
#include "ESP32_ISR_Timer.h"

#define TIMER_INTERVAL_MS         200
#define HW_TIMER_INTERVAL_MS      100

volatile uint32_t startMillis = 0;
// Init ESP32 timer 1
ESP32Timer ITimer(1);

// Init ESP32_ISR_Timer
ESP32_ISR_Timer ISR_Timer;


DFRobot_PLAY  myDFPlayer;
