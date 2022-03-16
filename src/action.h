#include <ArduinoJson.h>
#include <websocket.h>
#ifndef Action_h
#define Action_h

class Action {
public:
    Action() {}
    virtual bool is_number_dialed(const std::string dialed_number) = 0;
    virtual void perform() = 0;
};

class DebugAction : public Action {
public:
    DebugAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
    bool is_active;
    std::string dialed_number;
};

class BedAction : public Action {
public:
    BedAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class WakeAction : public Action {
public:
    WakeAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class CoolAction : public Action {
public:
    CoolAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class HeatAction : public Action {
public:
    HeatAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class StereoAction : public Action {
public:
    StereoAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class OfficeLightsAction : public Action {
public:
    OfficeLightsAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class RickRollAction : public Action {
public:
    RickRollAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(const std::string dialed_number);
    void perform();
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

#endif