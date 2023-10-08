#include "doorbell.h"

Doorbell::Doorbell(
        const gpio_num_t doorbell_pin,
        const gpio_num_t motor_pin_1,
        const gpio_num_t motor_pin_2
) : doorbell_pin(doorbell_pin), motor_pin_1(motor_pin_1), motor_pin_2(motor_pin_2) {
    is_ringing = false;
    is_first_ring = true;
    ring_start_time = 0;
    ring_stop_time = 0;
    pinMode(doorbell_pin, INPUT);
    pinMode(motor_pin_1, OUTPUT);
    pinMode(motor_pin_2, OUTPUT);
    digitalWrite(motor_pin_1, HIGH);
    digitalWrite(motor_pin_2, LOW);
}

bool Doorbell::should_ring() const {
    return !is_ringing && (is_first_ring || millis() - ring_stop_time > 2000) && digitalRead(doorbell_pin) == HIGH;
}

bool Doorbell::should_stop() const {
    return is_ringing && millis() - ring_start_time > 2000;
}

void Doorbell::ring() {
    ring_start_time = millis();
    is_ringing = true;
    is_first_ring = false;
    digitalWrite(motor_pin_1, LOW);
    digitalWrite(motor_pin_2, LOW);
    delayMicroseconds(30000);
    digitalWrite(motor_pin_1, HIGH);
    digitalWrite(motor_pin_2, HIGH);
    Serial.println("RING");
}

void Doorbell::stop() {
    is_ringing = false;
    ring_stop_time = millis();
    digitalWrite(motor_pin_1, HIGH);
    digitalWrite(motor_pin_2, LOW);
    Serial.println("STOP RINGING");
}

bool doorbell_loop(Doorbell *doorbell) {
    bool is_ringing = false;
    if (doorbell->should_ring()) {
        doorbell->ring();
        is_ringing = true;
    }
    if (doorbell->should_stop()) {
        doorbell->stop();
    }

    return is_ringing;
}
