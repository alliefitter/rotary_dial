#include <U8g2lib.h>
#include <Wire.h>
#include "Arduino.h"
#include <display.h>


SecretDisplay::SecretDisplay(U8G2 u8g2) {
    u8g2.begin();  
    u8g2.setFont(u8g2_font_inb30_mr);
    u8g2.setDisplayRotation(U8G2_R1);
    u8g2.setFontMode(0);
    this->display = u8g2;
    index = 0;
    is_enabled = false;
    last_show_time = 0;
    strcpy(text, "");
}

void SecretDisplay::set_text(char* new_text) {
    strcpy(text, new_text);
    index = -2;
    last_show_time = 0;
}

void SecretDisplay::enable() {
    is_enabled = true;
}

void SecretDisplay::disable() {
    is_enabled = false;
}

bool SecretDisplay::get_is_enabled() {
    return is_enabled;
}

void SecretDisplay::clear() {
    display.clearDisplay();
    strcpy(text, "");
}

void SecretDisplay::show_next() {
    char display_text[256];
    display.clearDisplay();
    delay(200);
    if (index == strlen(text)) {
        index = -2;
    }
    display.firstPage();
    do {
        if (index < 0) {
            display.setFont(u8g2_font_streamline_phone_t);
            display.drawUTF8(1, 54, "\x003A\x0033\x003A");
            display.drawUTF8(1, 86, "\x0033\x003A\x0033");
            display.drawUTF8(1, 118, "\x003A\x0033\x003A");
        }
        else {
            strncpy(display_text, &text[index], 1);
            display.setFont(u8g2_font_logisoso92_tn);
            display.drawUTF8(1, 121, display_text);
                
        }
    } while (display.nextPage());
    last_show_time = millis();
    index++;
}

bool SecretDisplay::should_show() {
    return is_enabled && strlen(text) > 0 && millis() - last_show_time > 1500;
}

void SecretDisplay::show_phones() {
    do {
        display.setFont(u8g2_font_streamline_phone_t);
        display.drawUTF8(1, 54, "\x003A\x0033\x003A");
        display.drawUTF8(1, 86, "\x0033\x003A\x0033");
        display.drawUTF8(1, 118, "\x003A\x0033\x003A");
    } while (display.nextPage());
}
