#include <action.h>
#include <ArduinoJson.h>
#include <WiFi.h>

bool RickRollAction::is_number_dialed(char* dialed_number) {
    return strcmp(dialed_number, "911") == 0;
}

void RickRollAction::perform() {
    Serial.print(WiFi.status());
    WiFi.begin("Fitter Than The Rest", "egd7efx8");
    Serial.println(WiFi.status());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    WiFi.lowPowerMode();
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
    WiFiClient client;
    client.connect("192.168.0.205", 8080);
    DynamicJsonDocument message(2048);
    String output;
    message["action"] = "RICK_ROLL";
    serializeJson(message, output);
    client.println(output);
    client.stop();
    WiFi.end();
}

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
}
