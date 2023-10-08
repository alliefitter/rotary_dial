#ifndef websocket_h
#define websocket_h

#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <vector>

typedef void (*WsConnectType)();
typedef void (*AppendRequestType)(const DynamicJsonDocument&);

extern uint16_t ws_id_counter;
static WebSocketsClient ws_client;
static std::vector<DynamicJsonDocument> requests;
void init_ws_id();
bool should_authorize(const DynamicJsonDocument& json_response);
void authorize();
void append_request(const DynamicJsonDocument& json);
bool has_request();
void send_request();
void ws_handler(WStype_t type, const uint8_t* payload, size_t length);
void ws_connect();
void ws_loop();

#endif