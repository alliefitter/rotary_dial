#ifndef battery_h
#define battery_h

#include <websocket.h>

const float VOLTAGE_CALIBRATION = 0.364;

class Battery {
public:
    Battery(AppendRequestType append_request, WsConnectType connect);
    bool should_report_battery();
    void report_battery();
    void reset();
private:
    AppendRequestType append_request;
    WsConnectType connect;
    unsigned long time_elapsed;
    float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif