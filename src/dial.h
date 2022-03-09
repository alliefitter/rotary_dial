#ifndef Dial_h
#define Dial_h

#include "Arduino.h"

class Dial 
{
    public:
        Dial(int pulse_pin, int dial_active_pin);
        int read_dial(bool is_dialing);
    private:
        int pulse_pin;
        int dial_active_pin;
};

#endif
