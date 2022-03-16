#ifndef sleeper_h
#define sleeper_h

class Sleeper {
public:
    Sleeper(int interupt_pin);
    void reset();
    bool should_sleep();
    void nighttime();
private:
    unsigned long time_elapsed;
    bool sleep_active;
    int interupt_pin;
};

#endif