#include "Arduino.h"
#include <avr/sleep.h>/
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <dial.h>
#include <action.h>
#include <WiFiNINA.h>
#include <U8g2lib.h>
#include <Wire.h>

enum HookStatus {ON, OFF};

const int dial_active_pin = 2;
const int pulse_pin = 3;
const int hook_pin = 4;
const int doorbell_pin = 8;
const int NUM_ACTIONS = 1;

unsigned long last_dial = 0;
char dialed_number[256];
HookStatus hook_status;
Dial dial(pulse_pin, dial_active_pin);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
SecretDisplay* display;
Action* actions[NUM_ACTIONS];

void dialing() {
  Serial.println("WAKE UP!!!!!");
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(dial_active_pin));
  pinMode(dial_active_pin, INPUT_PULLUP);
}

void doorbell() {
  Serial.println("RING!!!!");
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(dial_active_pin));
  pinMode(dial_active_pin, INPUT_PULLUP);
}

void nighttime() {
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(doorbell_pin), doorbell, RISING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
  Serial.println("WAKE");
}

void setup() {
  Serial.begin(9600);
  pinMode(dial_active_pin, INPUT);
  pinMode(pulse_pin, INPUT);
  pinMode(hook_pin, INPUT);
  pinMode(doorbell_pin, INPUT_PULLUP);
  display = new SecretDisplay(u8g2);
  actions[0] = new RickRollAction();
  actions[1] = new DebugAction(display);
  display->enable(); 
}

void loop() {
  int digit;
  bool is_dialing = digitalRead(dial_active_pin) == LOW;
  bool is_on_hook = digitalRead(hook_pin) == LOW;
  Serial.println(is_dialing);
  HookStatus current_hook_status = is_on_hook ? ON : OFF;
  // send_hook_status(current_hook_status);
  if (current_hook_status != hook_status) {
    if (is_on_hook) {
      display->clear();
      memset(dialed_number, 0, 256);
    }
  }
  hook_status = current_hook_status;
  if (is_dialing) {
    if (strlen(dialed_number) == 0) {
      display->clear();
    }
    digit = dial.read_dial(is_dialing);
    if (digit > 0) {
      last_dial = millis();
      sprintf(dialed_number, "%s%d", dialed_number, digit == 10 ? 0 : digit);
    }
  }
  if (strlen(dialed_number) > 0 && millis() - last_dial > 2500) {
    Serial.println(dialed_number);
    display->set_text(dialed_number);
    for (int x = 0; x < NUM_ACTIONS; x++) {
      if (actions[x]->is_number_dialed(dialed_number)) {
        actions[x]->perform();
      }
    }
    memset(dialed_number, 0, 256);
  }
  if (millis() - last_dial > 2500 && display->should_show()) {
    display->show_next();
  }
  if (millis() - last_dial > 10000) {
    nighttime();
  }
}
