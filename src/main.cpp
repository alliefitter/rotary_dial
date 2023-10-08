#include "Arduino.h"
#include <action.h>
#include <websocket.h>
#include <sleeper.h>
#include <wifi.h>
#include <rotary_phone.h>
#include <vector>

Sleeper* sleeper;
RotaryPhone* rotary_phone;

std::vector<Action*> init_actions() {
    std::vector<Action*> actions;
    actions.push_back(new WakeAction(append_request, ws_connect));
    actions.push_back(new CoolAction(append_request, ws_connect));
    actions.push_back(new BedAction(append_request, ws_connect));
    actions.push_back(new HeatAction(append_request, ws_connect));
    actions.push_back(new StereoAction(append_request, ws_connect));
    actions.push_back(new ToggleLightsAction(append_request, ws_connect, "light.office_lights", "546"));
    actions.push_back(new ToggleLightsAction(append_request, ws_connect, "light.hall_light", "544"));
    actions.push_back(new ToggleLightsAction(append_request, ws_connect, "light.kitchen_lights", "545"));
    actions.push_back(new ToggleLightsAction(append_request, ws_connect, "light.bedroom_lights", "542"));
    actions.push_back(new ToggleLightsAction(append_request, ws_connect, "light.living_room_lights", "547"));
    actions.push_back(new ToggleLightsAction(append_request, ws_connect, "light.bathroom_light", "548"));
    actions.push_back(new DebugAction(append_request, ws_connect));
    actions.push_back(new RickRollAction(append_request, ws_connect));

    return actions;
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(GPIO_NUM_32, INPUT);
    pinMode(GPIO_NUM_34, INPUT);
    pinMode(GPIO_NUM_35, INPUT);
    rotary_phone = new RotaryPhone(GPIO_NUM_32, GPIO_NUM_34, GPIO_NUM_35, init_actions());
    rotary_phone->reset();
    sleeper = new Sleeper(GPIO_NUM_35);
    sleeper->reset();
    Serial.begin(115200);
    Serial.println("START");
    init_ws_id();
    yield();
}

void loop() {
    yield();
    // Serial.println(digitalRead(GPIO_NUM_25));
    ws_loop();
    wifi_loop();
    DialStatus dial_status = rotary_dial_loop(rotary_phone);
    sleep_loop(sleeper, dial_status == ACTIVE, false);
    yield();
}
