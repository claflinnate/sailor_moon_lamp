#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include <DFRobot_PLAY.h>


#include "defines.h"
#include "handle.h"
#include "ball.h"
#include "moon.h"
#include "crystal.h"
#include "init.h"
#include "play.h"


#define RXD2 16
#define TXD2 17

void setup() {
    Colors[0] = strip1.Color(255, 255, 255);
    Colors[1] = strip1.Color(255, 0, 255);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    Serial.begin(115200);
    Serial.println("setup func");
    pinMode(33,OUTPUT);
    digitalWrite(33,HIGH);
    pinMode(23,INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(23), START_STOP_PLAYING, RISING);
    reset_state = true;
    sound_setup();

}

void sound_setup() {
    
    //myDFPlayer.setTimeOut(1500);

    try_dfp_begin = myDFPlayer.begin(Serial2);
    while (!try_dfp_begin && (try_dfp_count < 2)) { //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        delay(5000);
        try_dfp_begin = myDFPlayer.begin(Serial2);
        try_dfp_count++;
    }
    if (try_dfp_begin) {
        myDFPlayer.setVol(25);
        myDFPlayer.switchFunction((DFRobot_PLAY::eFunction_t)1);
        myDFPlayer.setPlayMode((DFRobot_PLAY::ePlayMode_t)1);
        myDFPlayer.setPrompt(false);
        myDFPlayer.setLED(false);
    }
    Serial.print("Final state is ");
    Serial.println(try_dfp_begin);
}

void light_setup() {
    
    strip1.begin();
    strip1.setBrightness(100);
    strip1.show();
}
uint32_t start = 0;

void loop() {
   real_loop();
}

void real_loop() {
    
    for (;;) {
        if (power_state) {
            if (digitalRead(23) && ((millis() - play_debounce) > 1000)) {
                play_debounce = millis();
                INTR_STATUS = 1;
            }
            if (reset_state) {
                Serial.println("setting up lights");
                light_setup();
                sound_setup();
                reset_state = 0;
            }
            if (INTR_STATUS) {
                INTR_STATUS = 0;
                try_play_music = 0;
                Serial.println("pressed");

                myDFPlayer.setPlayTime(0);
                myDFPlayer.start();
                //while ((myDFPlayer.readState() != 513) && (try_play_music < 1000)) {
                //  try_play_music++;
                //  delay(1);
                //}
                //wait for state to change
                //then play music box light sequence
                  //play_music_box(millis())
            //} else if (myDFPlayer.readState() == 513){
              delay_index = 1;
              while ((myDFPlayer.getCurTime() < 39) && (delay_index < 59)) {
                if (digitalRead(23) && ((millis() - play_debounce) > 1000)) {
                    play_debounce = millis();
                    Serial.println("pausing");
                    INTR_STATUS = 0;
                    delay_index = 1;
                    myDFPlayer.pause();
                    break;
                }
                play_music_box(millis());
              }
              myDFPlayer.pause();
            } else {
              while (initial_light_sequence) {
                  initial_lightup(millis());
              }
              Serial.print("spin sequence");
              for (;;) {
                if (digitalRead(23) && ((millis() - play_debounce) > 1000)) {
                    INTR_STATUS = 1;
                    break;
                }
                spin_handle(millis());
                spin_ball(millis());
                spin_crystal(millis());
                twinkle_moon(millis());
                strip1.show();
              }
              Serial.print("done spinning");
            }
        }
        else {
            myDFPlayer.pause();
            INTR_STATUS = 0;
            strip1.fill(strip1.Color(0, 0, 0), 0, LED_COUNT1);
            strip1.setBrightness(0);
            strip1.show();
            //delay(10);
            reset_state = true;
        }
        delay(1);
    }

}

void IRAM_ATTR START_STOP_PLAYING() {
    
    if ((millis() - play_debounce) > 10) {
        play_debounce = millis();
        INTR_STATUS = 1;
    }
}

void POWER_ON_OFF() {
    
    if ((millis() - power_debounce) > 10) {
        power_debounce = millis();
        power_state = !power_state;
    }
}
