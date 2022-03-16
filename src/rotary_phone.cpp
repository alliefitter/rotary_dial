#include <rotary_phone.h>
#include "Arduino.h"

RotaryPhone::RotaryPhone(
    const int dial_active_pin,
    const int pulse_pin,
    const int hook_pin,
    std::vector<Action*> actions
) : dial_active_pin(dial_active_pin),
    pulse_pin(pulse_pin),
    hook_pin(hook_pin),
    actions(actions) 
{
    last_dial = millis();
}

bool RotaryPhone::is_dialing() {
    return digitalRead(dial_active_pin) == LOW;
}

void RotaryPhone::read_dial() {
    int pulse_reading;
    int pulse_count = 0;
    int previous_state = LOW;
    while (is_dialing()) {
        pulse_reading = digitalRead(pulse_pin);        
        if (pulse_reading == HIGH && previous_state == LOW) {
            pulse_count++;
            Serial.print("PULSE: ");
            Serial.println(pulse_count);
        }
        previous_state = pulse_reading;
        delay(5);
    };
    append_digit(pulse_count);
}

bool RotaryPhone::is_hook_pressed() {
    HookStatus current_hook_status = digitalRead(hook_pin) == HIGH ? ON : OFF;
    bool hook_pressed = current_hook_status != hook_status && current_hook_status == ON;
    hook_status = current_hook_status;
    if (hook_pressed) {
        Serial.println("HOOK");
    }
    
    return hook_pressed;
}

bool RotaryPhone::should_reset() {
    return dialed_number.length() > 0 && (is_hook_pressed() || millis() - last_dial > 1500);
}

void RotaryPhone::reset() {
    Serial.println(dialed_number.c_str());
    dialed_number = "";
}

void RotaryPhone::append_digit(const int digit) {
    if (digit > 0) {
        last_dial = millis();
        char dialed_digit[11];
        sprintf(dialed_digit, "%d", digit == 10 ? 0 : digit);
        dialed_number.append(dialed_digit);
    }
}

bool RotaryPhone::should_iterate_actions() {
    return dialed_number.length() > 0 && millis() - last_dial > 500;
}

void RotaryPhone::iterate_actions() {
    bool was_performed = false;
    for (Action* action : actions) {
        if (action->is_number_dialed(dialed_number)) {
            was_performed = true;
            action->perform();
        }
    }
    if (was_performed) {
        reset();
    }
}