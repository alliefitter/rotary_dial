
#pragma once
#include <ArduinoJson.h>
#include <Hash.h>
#include <WebSocketsClient.h>
#ifndef Websocket_h
#define Wedsocket_h

class WebsocketHandler {
public:
    WebsocketHandler(WebSocketsClient client);
    bool has_data();
    DynamicJsonDocument get_json();
    void loop();
    void handler(WStype_t type, uint8_t* payload, size_t length);
    void connect();
private:
    void send_request();
    WebSocketsClient client;
    DynamicJsonDocument json;
    int id_counter;
};

#endif