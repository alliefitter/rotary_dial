#ifndef rotary_phone_h
#define rotary_phone_h

#include <action.h>
#include "sleeper.h"

enum HookStatus {ON, OFF};
enum DialStatus {ACTIVE, INACTIVE};

class RotaryPhone {
public:
    RotaryPhone(
        gpio_num_t dial_active_pin,
        gpio_num_t pulse_pin,
        gpio_num_t hook_pin,
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
    gpio_num_t dial_active_pin;
    gpio_num_t pulse_pin;
    gpio_num_t hook_pin;
    std::string dialed_number;
    bool was_digit_appended;
    unsigned long last_dial;
    HookStatus hook_status;
    std::vector<Action*> actions;
    void append_digit(int digit);
};

DialStatus rotary_dial_loop(RotaryPhone* phone);

#endif