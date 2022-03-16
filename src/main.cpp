#include "Arduino.h"
#include <action.h>
#include <Hash.h>
#include <websocket.h>
#include <battery.h>
#include <sleeper.h>
#include <rotary_phone.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

Battery* battery;
Sleeper* sleeper;
RotaryPhone* rotary_phone;

std::vector<Action*> init_actions() {
    std::vector<Action*> actions;
    actions.push_back(new WakeAction(append_request, ws_connect));
    actions.push_back(new CoolAction(append_request, ws_connect));
    actions.push_back(new BedAction(append_request, ws_connect));
    actions.push_back(new HeatAction(append_request, ws_connect));
    actions.push_back(new StereoAction(append_request, ws_connect));
    actions.push_back(new OfficeLightsAction(append_request, ws_connect));
    actions.push_back(new DebugAction(append_request, ws_connect));
    actions.push_back(new RickRollAction(append_request, ws_connect));

    return actions;
}

void setup() {
    yield();
    Serial.begin(115200);
    Serial.println("START");
    init_ws_id();
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D1, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    battery = new Battery(append_request, ws_connect);
    sleeper = new Sleeper(D5);
    rotary_phone = new RotaryPhone(D5, D6, D1, init_actions());
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Configuring access point...");
    IPAddress ip(192, 168, 0, 220);
    IPAddress gateway(192,168,0,1);
    IPAddress subnet(255,255,255,0);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    yield();
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_BUILTIN, HIGH);
    rotary_phone->reset();
    sleeper->reset();
    battery->reset();
    yield();
}

void loop() {
    yield();
    ws_loop();
    if (rotary_phone->should_reset()) {
        rotary_phone->reset();
    }
    if (rotary_phone->is_dialing()) {
        rotary_phone->read_dial();
        battery->reset();
        sleeper->reset();
    }
    if (rotary_phone->should_iterate_actions()) {
        rotary_phone->iterate_actions();
    }
    if (battery->should_report_battery()) {
        Serial.println("REPORT BATTERY");
        battery->report_battery();
    }
    if (sleeper->should_sleep()) {
        Serial.println("SLEEP");
        sleeper->nighttime();
    }
    yield();
}
