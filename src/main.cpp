#include "Arduino.h"
// #include <avr/sleep.h>
#include <dial.h>
#include <action.h>
#include <Hash.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>


enum HookStatus {ON, OFF};

const int dial_active_pin = D5;
const int pulse_pin = D6;
const int hook_pin = D1;
const int doorbell_pin = 8;
const int NUM_ACTIONS = 5;
const float VOLTAGE_CALIBRATION = 0.364; // 4.156
int ws_id_counter = 1;

WebSocketsClient ws_client;
DynamicJsonDocument json(1024);
unsigned long last_dial = 0;
unsigned long last_battery_report = 0;
char dialed_number[266];
bool sleep_active = false;
HookStatus hook_status;
Dial dial(pulse_pin, dial_active_pin);
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 5, /* data=*/ 4);   // ESP32 Thing, HW I2C with pin remapping
// SecretDisplay* display;
Action* actions[NUM_ACTIONS];

// void dialing() {
//   detachInterrupt(digitalPinToInterrupt(dial_active_pin));
//   last_dial = 0;
// }

// void doorbell() {
//   Serial.println("RING!!!!");
//   pinMode(dial_active_pin, INPUT_PULLUP);
// }

void send_request() {
  if (!json.isNull()) {
    String body;
    json["id"] = ws_id_counter;
    serializeJson(json, body);
    json = DynamicJsonDocument(1024);
    json.garbageCollect();
    Serial.println(body);
    ws_client.sendTXT(body);
    ws_id_counter++;
  }
  else {
    ws_client.disconnect();
  }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void websocket_handler(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED: {
      Serial.println("Diconnected from websockect");
    }
      break;
    
    case WStype_CONNECTED: {
      Serial.println("WS Connected");
    }
      break;
    
    case WStype_TEXT: {
      char* response = (char*)payload;
      DynamicJsonDocument json_response(1024);
      deserializeJson(json_response, response);
      Serial.println(response);
      if (json_response["type"] == "auth_required") {
        DynamicJsonDocument auth(1024);
        String body;
        auth["type"] = "auth";
        auth["access_token"] = HOME_ASSISTANT_TOKEN;
        serializeJson(auth, body);
        ws_client.sendTXT(body);
      }
      else {
        send_request();
      }
    }
      break;
  }
}

void connect_ws() {
  if (!ws_client.isConnected()) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Connecting Websocket...");
    ws_client.begin("homeassistant.local", 8123, "/api/websocket");
    ws_client.onEvent(websocket_handler);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void report_battery() {
  last_battery_report = millis();
  int sensor_value = analogRead(A0);
  float voltage = (((sensor_value * 11.78) / 1024) + VOLTAGE_CALIBRATION);
  int percentage = mapfloat(voltage, 2.8, 4.2, 0, 100);
  json["type"] = "call_service";
  json["domain"] = "input_number";
  json["service"] = "set_value";
  json["service_data"]["value"] = percentage;
  json["target"]["entity_id"] = "input_number.rotary_phone_battery";
  connect_ws();
}

void nighttime() {
  yield();
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  gpio_pin_wakeup_enable(dial_active_pin, GPIO_PIN_INTR_LOLEVEL);//3.676239
  wifi_station_disconnect();
  wifi_set_opmode_current(NULL_MODE);
  delay(1000);
  wifi_fpm_do_sleep(0xFFFFFFF);
  delay(10);
  wifi_set_opmode(STATION_MODE);
  wifi_station_connect();
  yield();
  // display->clear();
  // Serial.println(body);
  // WiFiClient client;
  // HTTPClient http;
  // http.begin(client, "homeassistant.local", 8123, "/api/services/input_number/set_value");
  // yield();
  // // delay(1000);
  // http.addHeader("Content-Type", "application/json");
  // http.addHeader("Authorization", HOME_ASSISTANT_TOKEN);
  // int responseCode = http.POST(body);
  // WiFiClient client;
  // HTTPClient http;
  // http.begin(client, "homeassistant.local", 8123, "/api/services/input_number/set_value");
  // yield();
  // Serial.println(responseCode);
  // Serial.println(http.getString());
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(100);
  // digitalWrite(LED_BUILTIN, HIGH);
  // http.end();
  
}

void setup() {
  yield();
  Serial.begin(115200);
  Serial.println("START");
  pinMode(dial_active_pin, INPUT);
  pinMode(pulse_pin, INPUT);
  pinMode(hook_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(doorbell_pin, INPUT_PULLUP);
  // display = new SecretDisplay(u8g2);
  // actions[0] = new RickRollAction();
  // actions[0] = new DebugAction(display);
  actions[0] = new WakeAction(&json, connect_ws);
  actions[1] = new BedAction(&json, connect_ws);
  actions[2] = new HeatAction(&json, connect_ws);
  actions[3] = new StereoAction(&json, connect_ws);
  actions[4] = new OfficeLightsAction(&json, connect_ws);
  // display->enable();
  digitalWrite(LED_BUILTIN, LOW);
  ws_client.onEvent(websocket_handler);
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
  // if (!ws_client.isConnected()) {
  //   Serial.println("Connecting Websocket...");
  //   ws_client.begin("homeassistant.local", 8123, "/api/websocket");
  //   ws_client.onEvent(websocket_handler);
  //   ws_client.setReconnectInterval(1000);
  // }
  digitalWrite(LED_BUILTIN, HIGH);
  // display->clear();
  // display->show_phones();
  // delay(50);
  // display->clear();
  last_dial = millis();
  yield();
}

void loop() {
  yield();
  if (!json.isNull()) {
    ws_client.loop();
  }
  // Serial.println(digitalRead(dial_active_pin)); 
  // Serial.println(digitalRead(hook_pin));
  // Serial.println(digitalRead(pulse_pin)); 
  // delay(1000);
  int digit;
  bool is_dialing = digitalRead(dial_active_pin) == LOW;
  bool is_on_hook = digitalRead(hook_pin) == HIGH;
  HookStatus current_hook_status = is_on_hook ? ON : OFF;
  // Serial.println(current_hook_status);
  if (current_hook_status != hook_status) {
    if (is_on_hook) {
      // display->clear();
      Serial.println("HOOK");
      memset(dialed_number, 0, 256);
    }
  }
  hook_status = current_hook_status;
  if (is_dialing) {
    // if (strlen(dialed_number) == 0) {
    //   display->clear();
    // }
    digit = dial.read_dial(is_dialing);
    if (digit > 0) {
      last_dial = millis();
      sprintf(dialed_number, "%s%d", dialed_number, digit == 10 ? 0 : digit);
    }
  }
  if (strlen(dialed_number) > 0 && millis() - last_dial > 2500) {
    Serial.println(dialed_number);
    // display->set_text(dialed_number);
    for (int x = 0; x < NUM_ACTIONS; x++) {
      if (actions[x]->is_number_dialed(dialed_number)) {
        actions[x]->perform();
      }
    }
    memset(dialed_number, 0, 256);
  }
  // if (millis() - last_dial > 2500 && display->should_show()) {
  //   display->show_next();
  // }
  if (millis() - last_dial > 15000 && millis() - last_battery_report > 20000) {
    Serial.println("REPORT BATTERY");
    report_battery();
  }
  if (sleep_active == false && millis() - last_dial > 30000) {
    Serial.println("SLEEP");
    Serial.println(sleep_active == false && millis() - last_dial > 30000);
    last_dial = millis();
    sleep_active = true;
    yield();
    nighttime();
    sleep_active = false;
    yield();
  }
  // detachInterrupt(digitalPinToInterrupt(dial_active_pin));
  yield();
}
