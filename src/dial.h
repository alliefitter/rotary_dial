#ifndef Dial_h
#define Dial_h

#include "Arduino.h"

class Dial 
{
    public:
        Dial(int pulse_pin, int dial_active_pin);
        int read_dial(bool is_dialing);
        void send_pulse(int count);
        void send_dialed_number(int number);
    private:
        int pulse_pin;
        int dial_active_pin;
};

#endif
