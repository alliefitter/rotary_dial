#include <U8g2lib.h>
#include <Wire.h>


class SecretDisplay {
public:
    SecretDisplay() {}
    SecretDisplay(U8G2 u8g2);
    void set_text(char* new_text);
    void enable();
    void disable();
    bool get_is_enabled();
    void clear();
    void show_next();
    bool should_show();
private:
    bool is_enabled;
    unsigned long last_show_time;
    int index;
    char text[256];
    U8G2 display;
};
