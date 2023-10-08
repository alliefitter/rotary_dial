#ifndef WIFI_H
#define WIFI_H

#include "WiFi.h"

void wifi_connect();
void wifi_disconnect();
void handle_wifi_event(WiFiEvent_t event);
bool is_wifi_connected();
void wifi_loop();

#endif