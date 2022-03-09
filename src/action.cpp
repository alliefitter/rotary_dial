#include "Arduino.h"
#include <action.h>

DebugAction::DebugAction(SecretDisplay* secret_display) {
    display = secret_display;
}

bool DebugAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "00") == 0;
}

void DebugAction::perform() {
    if (display->get_is_enabled()) {
        display->disable();
    }
    else {
        display->enable();
    }
    display->clear();
    display->show_phones();
    delay(50);
    display->clear();
}

WakeAction::WakeAction(DynamicJsonDocument* json, WsConnectType connect) : json(json), connect(connect) {}

bool WakeAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "9253") == 0;
}

void WakeAction::perform() {
    (*json)["type"] = "fire_event";
    (*json)["event_type"] = "wake";
    connect();
}

BedAction::BedAction(DynamicJsonDocument* json, WsConnectType connect) : json(json), connect(connect) {}

bool BedAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "233") == 0;
}

void BedAction::perform() {
    (*json)["type"] = "fire_event";
    (*json)["event_type"] = "bed_time";
    connect();
}

HeatAction::HeatAction(DynamicJsonDocument* json, WsConnectType connect) : json(json), connect(connect) {}

bool HeatAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "4328") == 0;
}

void HeatAction::perform() {
    (*json)["type"] = "fire_event";
    (*json)["event_type"] = "heat";
    connect();
}

StereoAction::StereoAction(DynamicJsonDocument* json, WsConnectType connect) : json(json), connect(connect) {}

bool StereoAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "7529") == 0;
}

void StereoAction::perform() {
    (*json)["type"] = "call_service";
    (*json)["domain"] = "script";
    (*json)["service"] = "play_record";
    connect();
}

OfficeLightsAction::OfficeLightsAction(DynamicJsonDocument* json, WsConnectType connect) : json(json), connect(connect) {}

bool OfficeLightsAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "540") == 0;
}

void OfficeLightsAction::perform() {
    (*json)["type"] = "call_service";
    (*json)["domain"] = "light";
    (*json)["service"] = "toggle";
    (*json)["target"]["entity_id"] = "light.office_lights";
    connect();
}
