#include <wifi.h>
#include "Arduino.h"

bool is_connecting = false;
RTC_DATA_ATTR int32_t channel = 0;

void handle_wifi_event(WiFiEvent_t event) {
    switch (event)
    {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        Serial.println("WiFi connected");
        digitalWrite(LED_BUILTIN, LOW);
        is_connecting = false;
        channel = WiFi.channel();
        break;

    case ARDUINO_EVENT_WIFI_READY:
        Serial.println("ARDUINO_EVENT_WIFI_READY");
        break;
    
    case ARDUINO_EVENT_WIFI_SCAN_DONE:
        Serial.println("ARDUINO_EVENT_WIFI_SCAN_DONE");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_START:
        Serial.println("ARDUINO_EVENT_WIFI_STA_START");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_STOP:
        Serial.println("ARDUINO_EVENT_WIFI_STA_STOP");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Serial.println("ARDUINO_EVENT_WIFI_STA_CONNECTED");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        Serial.println("ARDUINO_EVENT_WIFI_STA_DISCONNECTED");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
        Serial.println("ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
        Serial.println("ARDUINO_EVENT_WIFI_STA_GOT_IP6");
        break;
    
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
        Serial.println("ARDUINO_EVENT_WIFI_STA_LOST_IP");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_START:
        Serial.println("ARDUINO_EVENT_WIFI_AP_START");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_STOP:
        Serial.println("ARDUINO_EVENT_WIFI_AP_STOP");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
        Serial.println("ARDUINO_EVENT_WIFI_AP_STACONNECTED");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
        Serial.println("ARDUINO_EVENT_WIFI_AP_STADISCONNECTED");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
        Serial.println("ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
        Serial.println("ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED");
        break;
    
    case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
        Serial.println("ARDUINO_EVENT_WIFI_AP_GOT_IP6");
        break;
    
    case ARDUINO_EVENT_WIFI_FTM_REPORT:
        Serial.println("ARDUINO_EVENT_WIFI_FTM_REPORT");
        break;
    
    case ARDUINO_EVENT_ETH_START:
        Serial.println("ARDUINO_EVENT_ETH_START");
        break;
    
    case ARDUINO_EVENT_ETH_STOP:
        Serial.println("ARDUINO_EVENT_ETH_STOP");
        break;
    
    case ARDUINO_EVENT_ETH_CONNECTED:
        Serial.println("ARDUINO_EVENT_ETH_CONNECTED");
        break;
    
    case ARDUINO_EVENT_ETH_DISCONNECTED:
        Serial.println("ARDUINO_EVENT_ETH_DISCONNECTED");
        break;
    
    case ARDUINO_EVENT_ETH_GOT_IP:
        Serial.println("ARDUINO_EVENT_ETH_GOT_IP");
        break;
    
    case ARDUINO_EVENT_ETH_GOT_IP6:
        Serial.println("ARDUINO_EVENT_ETH_GOT_IP6");
        break;
    
    case ARDUINO_EVENT_WPS_ER_SUCCESS:
        Serial.println("ARDUINO_EVENT_WPS_ER_SUCCESS");
        break;
    
    case ARDUINO_EVENT_WPS_ER_FAILED:
        Serial.println("ARDUINO_EVENT_WPS_ER_FAILED");
        break;
    
    case ARDUINO_EVENT_WPS_ER_TIMEOUT:
        Serial.println("ARDUINO_EVENT_WPS_ER_TIMEOUT");
        break;
    
    case ARDUINO_EVENT_WPS_ER_PIN:
        Serial.println("ARDUINO_EVENT_WPS_ER_PIN");
        break;
    
    case ARDUINO_EVENT_WPS_ER_PBC_OVERLAP:
        Serial.println("ARDUINO_EVENT_WPS_ER_PBC_OVERLAP");
        break;
    
    case ARDUINO_EVENT_SC_SCAN_DONE:
        Serial.println("ARDUINO_EVENT_SC_SCAN_DONE");
        break;
    
    case ARDUINO_EVENT_SC_FOUND_CHANNEL:
        Serial.println("ARDUINO_EVENT_SC_FOUND_CHANNEL");
        break;
    
    case ARDUINO_EVENT_SC_GOT_SSID_PSWD:
        Serial.println("ARDUINO_EVENT_SC_GOT_SSID_PSWD");
        break;
    
    case ARDUINO_EVENT_SC_SEND_ACK_DONE:
        Serial.println("ARDUINO_EVENT_SC_SEND_ACK_DONE");
        break;
    
    case ARDUINO_EVENT_PROV_INIT:
        Serial.println("ARDUINO_EVENT_PROV_INIT");
        break;
    
    case ARDUINO_EVENT_PROV_DEINIT:
        Serial.println("ARDUINO_EVENT_PROV_DEINIT");
        break;
    
    case ARDUINO_EVENT_PROV_START:
        Serial.println("ARDUINO_EVENT_PROV_START");
        break;
    
    case ARDUINO_EVENT_PROV_END:
        Serial.println("ARDUINO_EVENT_PROV_END");
        break;
    
    case ARDUINO_EVENT_PROV_CRED_RECV:
        Serial.println("ARDUINO_EVENT_PROV_CRED_RECV");
        break;
    
    case ARDUINO_EVENT_PROV_CRED_FAIL:
        Serial.println("ARDUINO_EVENT_PROV_CRED_FAIL");
        break;
    
    case ARDUINO_EVENT_PROV_CRED_SUCCESS:
        Serial.println("ARDUINO_EVENT_PROV_CRED_SUCCESS");
        break;
    
    case ARDUINO_EVENT_MAX:
        Serial.println("ARDUINO_EVENT_MAX");
        break;
    
    default:
        Serial.println(event);
        break;
    }
}

void wifi_connect() {
    is_connecting = true;
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Configuring access point...");
    Serial.print("Current channel: ");
    Serial.println(channel);
    IPAddress ip(192, 168, 50, 229);
    IPAddress gateway(192,168,50,1);
    IPAddress subnet(255,255,255,0);
    IPAddress dns(192, 168, 50, 29);
    unsigned char bssid[18] = {0x50, 0xeb, 0xf6, 0x10, 0x86, 0xf8};
    WiFiClass::mode(WIFI_STA);
    WiFiClass::hostname("rotaryphone.home");
    WiFi.onEvent(handle_wifi_event);
    WiFi.config(ip, gateway, subnet);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    WiFi.dnsIP(dns);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD, channel, bssid);
}

void wifi_disconnect() {
    WiFi.disconnect();
}

bool is_wifi_connected() {
    return WiFi.isConnected() or is_connecting;
}

void wifi_loop() {
    if (!is_wifi_connected()) {
        wifi_connect();
    }
}
