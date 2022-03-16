#include <sleeper.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

Sleeper::Sleeper(int interupt_pin) : interupt_pin(interupt_pin) {
    time_elapsed = millis();
}

void Sleeper::reset() {
    time_elapsed = millis();
}

bool Sleeper::should_sleep() {
    return sleep_active == false && millis() - time_elapsed > 30000;
}

void Sleeper::nighttime() {
    sleep_active = true;
    yield();
    wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
    wifi_fpm_open();
    gpio_pin_wakeup_enable(interupt_pin, GPIO_PIN_INTR_LOLEVEL);
    wifi_station_disconnect();
    wifi_set_opmode_current(NULL_MODE);
    delay(1000);
    wifi_fpm_do_sleep(0xFFFFFFF);
    delay(10);
    wifi_set_opmode(STATION_MODE);
    wifi_station_connect();
    yield();
    sleep_active = false;
}