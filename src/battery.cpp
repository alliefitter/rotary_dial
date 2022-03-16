#include <battery.h>
#include <Arduino.h>

Battery::Battery(AppendRequestType append_request, WsConnectType connect) : append_request(append_request),
                                                                            connect(connect) {}

float Battery::mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Battery::reset() {
    time_elapsed = millis();
}

bool Battery::should_report_battery() {
    return millis() - time_elapsed > 20000;
}

void Battery::report_battery() {
    time_elapsed = millis();
    int sensor_value = analogRead(A0);
    float voltage = (((sensor_value * 11.78) / 1024) + VOLTAGE_CALIBRATION);
    int percentage = mapfloat(voltage, 2.8, 4.2, 0, 100);
    DynamicJsonDocument json(1024);
    json["type"] = "call_service";
    json["domain"] = "input_number";
    json["service"] = "set_value";
    json["service_data"]["value"] = percentage;
    json["target"]["entity_id"] = "input_number.rotary_phone_battery";
    append_request(json);
    connect();
}