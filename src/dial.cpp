#include <dial.h>
#include "Arduino.h"



Dial::Dial(int pulse_pin, int dial_active_pin) {
    this->pulse_pin = pulse_pin;
    this->dial_active_pin = dial_active_pin;
}

int Dial::read_dial(bool is_dialing) {
    int pulse_reading;
    int pulse_count = 0;
    int previous_state = LOW;
    while (is_dialing) {
        pulse_reading = digitalRead(pulse_pin);        
        if (pulse_reading == HIGH && previous_state == LOW) {
            pulse_count++;
            // this->send_pulse(pulse_count);
            Serial.print("PULSE: ");
            Serial.println(pulse_count);
        }
        previous_state = pulse_reading;
        delay(5);
        is_dialing = digitalRead(dial_active_pin) == LOW;
    };
    // if (pulse_count > 0) {
    //     this->send_dialed_number(pulse_count);
    // }
    return pulse_count;
}
