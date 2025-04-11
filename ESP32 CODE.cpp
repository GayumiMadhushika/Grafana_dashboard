#include <WiFi.h>
#include <AsyncMqttClient.h>

const char* ssid = "Gayumi";
const char* password = "Gayu1234";
const char* mqtt_server = "172.20.10.3";
const uint16_t mqtt_port = 1883;

AsyncMqttClient mqttClient;
WiFiEventId_t wifiConnectHandler;
WiFiEventId_t wifiDisconnectHandler;
Ticker mqttReconnectTimer;

// Callback when MQTT is connected
void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  mqttClient.publish("esp32/status", 1, true, "online");  // Birth Message
}

// Callback when MQTT is disconnected
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  mqttClient.publish("esp32/status", 1, true, "offline"); // LWT Message
  mqttReconnectTimer.once(2, connectToMqtt); // Attempt reconnection in 2s
}

// Connect to MQTT
void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

// Connect to WiFi
void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
}

// Callback when WiFi is connected
void onWiFiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Connected to WiFi.");
  connectToMqtt();
}

// Callback when WiFi is disconnected
void onWiFiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Disconnected from WiFi.");
  mqttReconnectTimer.once(2, connectToWiFi);
}

void setup() {
  Serial.begin(115200);

  WiFi.onEvent(onWiFiConnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(onWiFiDisconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  connectToWiFi();

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setWill("esp32/status", 1, true, "offline");  // LWT Message
}

void loop() {
  // Nothing needed in loop (Handled asynchronously)
}
