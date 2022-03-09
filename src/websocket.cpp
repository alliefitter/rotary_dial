#include <websocket.h>
using namespace std::placeholders;

WebsocketHandler::WebsocketHandler(WebSocketsClient client) : client(client), 
    json(DynamicJsonDocument(1024)), id_counter(0) {}

bool WebsocketHandler::has_data() {
    return !json.isNull();
}
DynamicJsonDocument WebsocketHandler::get_json() {
    return json;
}
void WebsocketHandler::loop() {
    this->client.loop();
}
void WebsocketHandler::handler(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED: {
      Serial.println("Diconnected from websockect");
    }
      break;
    
    case WStype_CONNECTED: {
      Serial.println("WS Connected");
      DynamicJsonDocument auth(1024);
      String body;
      auth["type"] = "auth";
      auth["access_token"] = HOME_ASSISTANT_TOKEN;
      serializeJson(auth, body);
      client.sendTXT(body);
    }
      break;
    
    case WStype_TEXT: {
      char* response = (char*)payload;
      Serial.println(response);
      send_request();
    }
      break;
  }
}
void WebsocketHandler::connect() {
  if (!client.isConnected()) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Connecting Websocket...");
    client.begin("homeassistant.local", 8123, "/api/websocket");
    client.onEvent(std::bind(&WebsocketHandler::handler, this, _1, _2, _3));
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void WebsocketHandler::send_request() {
    if (!json.isNull()) {
        String body;
        json["id"] = id_counter;
        serializeJson(json, body);
        json = DynamicJsonDocument(1024);
        Serial.println(body);
        client.sendTXT(body);
        id_counter++;
    }
    else {
        client.disconnect();
    }
}