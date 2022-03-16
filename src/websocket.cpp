#include <websocket.h>

uint16_t ws_id_counter;

void init_ws_id() {
    ws_id_counter = 1;
}

void append_request(DynamicJsonDocument request) {
    requests.push_back(request);
}

bool has_request() {
    return !requests.empty();
}

void send_request() {
    if (has_request()) {
        String body;
        DynamicJsonDocument json = requests.front();
        requests.erase(requests.begin());
        json["id"] = ws_id_counter;
        serializeJson(json, body);
        json = DynamicJsonDocument(1024);
        json.garbageCollect();
        Serial.println(body);
        ws_client.sendTXT(body);
        ws_id_counter++;
        json.garbageCollect();
    }
    else {
        ws_client.disconnect();
    }
}

bool should_authorize(const DynamicJsonDocument json_response) {
    return json_response["type"] == "auth_required";
}

void authorize() {
    DynamicJsonDocument auth(1024);
    String body;
    auth["type"] = "auth";
    auth["access_token"] = HOME_ASSISTANT_TOKEN;
    serializeJson(auth, body);
    ws_client.sendTXT(body);
}

void ws_handler(const WStype_t type, const uint8_t* payload, const size_t length) {
    switch (type) {
        case WStype_DISCONNECTED: {
            ws_client.setReconnectInterval(86400 * 1000);
            Serial.println("Diconnected from websockect");
        }
            break;
        
        case WStype_CONNECTED: {
            Serial.println("WS Connected");
            if (length > 0) {
                Serial.printf("%s\n", payload);
            }
        }
            break;
        
        case WStype_TEXT: {
            Serial.printf("%s\n", payload);
            char* response = (char*)payload;
            DynamicJsonDocument json_response(1024);
            deserializeJson(json_response, response);
            if (should_authorize(json_response)) {
                authorize();
            }
            else {
                send_request();
            }
        }
            break;

        case WStype_BIN:
        case WStype_PING:
        case WStype_PONG:
        case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
        break;
    }
}

void ws_connect() {
    if (!ws_client.isConnected()) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Connecting Websocket...");
        ws_client.onEvent(ws_handler);
        ws_client.setReconnectInterval(500);
        ws_client.begin("homeassistant.local", 8123, "/api/websocket");
        digitalWrite(LED_BUILTIN, HIGH);
    }
}

void ws_loop() {
    ws_client.loop();
}
