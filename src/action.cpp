#include "Arduino.h"
#include <action.h>
#include <wifi.h>

#include <utility>

void BaseAction::wait_on_wifi() {
    unsigned long start_time = millis();
    while (!is_wifi_connected()) {
        if (millis() - start_time > 10000) {
            Serial.println("Wait on WiFi time out!");
            break;
        } 
    }
}

DebugAction::DebugAction(AppendRequestType append_request, WsConnectType connect) 
: append_request(append_request), 
  connect(connect), 
  is_active(false) {}

bool DebugAction::is_number_dialed(const std::string dialed_number) {
    if (dialed_number == "00") {
        is_active = !is_active;
    }
    this->current_dialed_number = dialed_number;
    
    return is_active;
}

void DebugAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "call_service";
    json["domain"] = "notify";
    json["service"] = "mobile_app_pixel_5";
    json["service_data"]["message"] = this->current_dialed_number;
    append_request(json);
    connect();
}

WakeAction::WakeAction(AppendRequestType append_request, WsConnectType connect) : append_request(append_request), connect(connect) {}

bool WakeAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  "9253";
}

void WakeAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "fire_event";
    json["event_type"] = "wake";
    append_request(json);
    connect();
}

CoolAction::CoolAction(AppendRequestType append_request, WsConnectType connect) : append_request(append_request), connect(connect) {}

bool CoolAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  "2665";
}

void CoolAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "fire_event";
    json["event_type"] = "cool";
    append_request(json);
    connect();
}

BedAction::BedAction(AppendRequestType append_request, WsConnectType connect) : append_request(append_request), connect(connect) {}

bool BedAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  "233";
}

void BedAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "fire_event";
    json["event_type"] = "bed_time";
    append_request(json);
    connect();
}

HeatAction::HeatAction(AppendRequestType append_request, WsConnectType connect) : append_request(append_request), connect(connect) {}

bool HeatAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  "4328";
}

void HeatAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "fire_event";
    json["event_type"] = "heat";
    append_request(json);
    connect();
}

StereoAction::StereoAction(AppendRequestType append_request, WsConnectType connect) : append_request(append_request), connect(connect) {}

bool StereoAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  "7529";
}

void StereoAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "call_service";
    json["domain"] = "script";
    json["service"] = "play_record";
    append_request(json);
    connect();
}

ToggleLightsAction::ToggleLightsAction(
    AppendRequestType append_request,
    WsConnectType connect,
    std::string  entity_id,
    std::string  trigger_number

) : append_request(append_request), connect(connect), entity_id(std::move(entity_id)), trigger_number(std::move(trigger_number)) {}

bool ToggleLightsAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  trigger_number;
}

void ToggleLightsAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "call_service";
    json["domain"] = "light";
    json["service"] = "toggle";
    json["target"]["entity_id"] = entity_id;
    append_request(json);
    connect();
}

RickRollAction::RickRollAction(AppendRequestType append_request, WsConnectType connect) : append_request(append_request), connect(connect) {}

bool RickRollAction::is_number_dialed(const std::string dialed_number) {
    return dialed_number ==  "911";
}

void RickRollAction::perform() {
    wait_on_wifi();
    DynamicJsonDocument json(1024);
    json["type"] = "call_service";
    json["domain"] = "script";
    json["service"] = "rick_roll";
    append_request(json);
    connect();
}
