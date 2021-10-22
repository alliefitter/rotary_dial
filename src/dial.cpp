#include <dial.h>
#include "Arduino.h"
#include <ArduinoJson.h>
#include <WiFi.h>



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

void Dial::send_pulse(int count) {
    Serial.print("START PULSE: ");
    Serial.println(millis());
    Serial.println("PULSE");
    WiFiClient client;
    client.connect("192.168.0.205", 8080);
    DynamicJsonDocument message(2048);
    String output;
    message["action"] = "PULSE";
    message["count"] = count;
    serializeJson(message, output);
    client.println(output);
    client.stop();
    Serial.print("END PULSE: ");
    Serial.println(millis());
}

void Dial::send_dialed_number(int number) {
    WiFiClient client;
    client.connect("192.168.0.205", 8080);
    DynamicJsonDocument message(2048);
    String output;
    message["action"] = "DIALED_NUMBER";
    message["dialed_number"] = number == 10 ? 0 : number;
    serializeJson(message, output);
    client.println(output);
    client.stop();
}

