#include <sleeper.h>
#include <Arduino.h>
#include <wifi.h>

Sleeper::Sleeper(gpio_num_t hook_pin) {
    time_elapsed = millis();
    sleep_active = false;
    // 0x900000000 bit mask for pins 32 and 35
    // 0x802000000 with doorbell
    esp_sleep_enable_ext1_wakeup(0x900000000, ESP_EXT1_WAKEUP_ANY_HIGH);
}

void Sleeper::reset() {
    time_elapsed = millis();
}

bool Sleeper::should_sleep() const {
    return !sleep_active && millis() - time_elapsed > 30000;
}

void Sleeper::nighttime() {
    sleep_active = true;
    yield();
    wifi_disconnect();
    esp_deep_sleep_start();
}

void sleep_loop(Sleeper* sleeper, bool is_dial_active, bool is_ringing) {
    if (is_dial_active || is_ringing) {
        sleeper->reset();
    }
    if (sleeper->should_sleep()) {
        Serial.println("SLEEP");
        sleeper->nighttime();
    }
}
