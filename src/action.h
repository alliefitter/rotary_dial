#include <display.h>
#include <ArduinoJson.h>
#ifndef Action_h
#define Action_h

typedef void (*WsConnectType)();

class Action {
public:
    Action() {}
    virtual bool is_number_dialed(char* dialed_number) = 0;
    virtual void perform() = 0;
};

class DebugAction : public Action {
public:
    DebugAction(SecretDisplay* secret_display);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    SecretDisplay* display;
};

class BedAction : public Action {
public:
    BedAction(DynamicJsonDocument* json, WsConnectType connect);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    DynamicJsonDocument* json;
    WsConnectType connect;
};

class WakeAction : public Action {
public:
    WakeAction(DynamicJsonDocument* json, WsConnectType connect);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    DynamicJsonDocument* json;
    WsConnectType connect;
};

class HeatAction : public Action {
public:
    HeatAction(DynamicJsonDocument* json, WsConnectType connect);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    DynamicJsonDocument* json;
    WsConnectType connect;
};

class StereoAction : public Action {
public:
    StereoAction(DynamicJsonDocument* json, WsConnectType connect);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    DynamicJsonDocument* json;
    WsConnectType connect;
};

class OfficeLightsAction : public Action {
public:
    OfficeLightsAction(DynamicJsonDocument* json, WsConnectType connect);
    bool is_number_dialed(char* dialed_number);
    void perform();
private:
    DynamicJsonDocument* json;
    WsConnectType connect;
};

#endif