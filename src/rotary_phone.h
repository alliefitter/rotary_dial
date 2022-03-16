#ifndef rotary_phone_h
#define rotary_phone_h

#include <action.h>
#include <ESP8266WiFi.h>

enum HookStatus {ON, OFF};

class RotaryPhone {
public:
    RotaryPhone(
        const int dial_active_pin, 
        const int pulse_pin, 
        const int hook_pin, 
        std::vector<Action*> actions
    );
    bool is_dialing();
    void read_dial();
    bool should_reset();
    bool is_hook_pressed();
    void reset();
    bool should_iterate_actions();
    void iterate_actions();
private:
    int dial_active_pin;
    int pulse_pin;
    int hook_pin;
    std::string dialed_number;
    unsigned long last_dial;
    HookStatus hook_status;
    std::vector<Action*> actions;
    void append_digit(const int digit);
};

#endif