#ifndef sleeper_h
#define sleeper_h
#include <WiFi.h>

class Sleeper {
public:
    Sleeper(gpio_num_t hook_pin);
    void reset();
    bool should_sleep() const;
    void nighttime();
private:
    unsigned long time_elapsed;
    bool sleep_active;
};

void sleep_loop(Sleeper* sleeper, bool is_dial_active, bool is_ringing);

#endif