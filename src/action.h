#include <display.h>
#ifndef Action_h
#define Action_h

class Action {
public:
    Action() {}
    virtual bool is_number_dialed(char* dialed_number) = 0;
    virtual void perform() = 0;
};

class RickRollAction : public Action {
    bool is_number_dialed(char* dialed_number);
    void perform();
};

class DebugAction : public Action {
public:
    DebugAction(SecretDisplay* secret_display);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    SecretDisplay* display;
};

#endif