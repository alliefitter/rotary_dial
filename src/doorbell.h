#ifndef Doorbell_h
#define Doorbell_h

#include "Arduino.h"

class Doorbell {
public:
    Doorbell(
        gpio_num_t doorbell_pin,
        gpio_num_t motor_pin_1,
        gpio_num_t motor_pin_2
    );
    bool should_ring() const;
    bool should_stop() const;
    void ring();
    void stop();
private:
    const gpio_num_t doorbell_pin;
    const gpio_num_t motor_pin_1;
    const gpio_num_t motor_pin_2;
    bool is_ringing;
    bool is_first_ring;
    unsigned long ring_start_time;
    unsigned long ring_stop_time;
};

bool doorbell_loop(Doorbell *doorbell);

#endif