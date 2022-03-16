#ifndef websocket_h
#define websocket_h

#include <WebSocketsClient.h>
#include <ArduinoJson.h>

typedef void (*WsConnectType)();
typedef void (*AppendRequestType)(DynamicJsonDocument);

extern uint16_t ws_id_counter;
static WebSocketsClient ws_client;
static std::vector<DynamicJsonDocument> requests;
void init_ws_id();
bool should_authorize(const DynamicJsonDocument json_response);
void authorize();
void append_request(DynamicJsonDocument json);
bool has_request();
void send_request();
void ws_handler(const WStype_t type, const uint8_t* payload, const size_t length);
void ws_connect();
void ws_loop();

#endif