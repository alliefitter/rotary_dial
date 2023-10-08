#ifndef Action_h
#define Action_h

#include <ArduinoJson.h>
#include <websocket.h>

class Action {
public:
    virtual bool is_number_dialed(std::string dialed_number) = 0;
    virtual void perform() = 0;
private:
    virtual void wait_on_wifi() = 0;
};

class BaseAction : public Action {
protected:
    void wait_on_wifi() override;
};

class DebugAction : public BaseAction {
public:
    DebugAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
    bool is_active;
    std::string current_dialed_number;
};

class BedAction : public BaseAction {
public:
    BedAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class WakeAction : public BaseAction {
public:
    WakeAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class CoolAction : public BaseAction {
public:
    CoolAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class HeatAction : public BaseAction {
public:
    HeatAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class StereoAction : public BaseAction {
public:
    StereoAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

class ToggleLightsAction : public BaseAction {
public:
    ToggleLightsAction(
        AppendRequestType append_request,
        WsConnectType connect,
        std::string  entity_id,
        std::string  trigger_number
    );
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
    const std::string entity_id;
    const std::string trigger_number;
};

class RickRollAction : public BaseAction {
public:
    RickRollAction(AppendRequestType append_request, WsConnectType connect);
    bool is_number_dialed(std::string dialed_number) override;
    void perform() override;
private:
    AppendRequestType append_request;
    WsConnectType connect;
};

#endif