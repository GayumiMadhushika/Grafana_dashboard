#include <Arduino.h>
#include <WiFi.h>
#include <AsyncMqttClient.h>
#include <Ticker.h>  // ✅ Include for timer-based reconnections

const char* ssid = "Gayumi";
const char* password = "Gayu1234";
const char* mqtt_server = "mosquitto";
const uint16_t mqtt_port = 1883;

AsyncMqttClient mqttClient;  // ✅ Correct object name
WiFiEventId_t wifiConnectHandler;
WiFiEventId_t wifiDisconnectHandler;
Ticker mqttReconnectTimer;

// Function prototype
void connectToMqtt();

// WiFi event handlers
void onWiFiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Connected to WiFi.");
  connectToMqtt();
}

void onWiFiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("Disconnected from WiFi.");
  mqttReconnectTimer.once(2, connectToMqtt);
}

// Callback when MQTT is connected
void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  mqttClient.publish("esp32/status", 1, true, "online");  // ✅ Birth message
}

// Callback when MQTT is disconnected
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  mqttReconnectTimer.once(2, connectToMqtt); // ✅ Retry connection
}

// Connect to MQTT
void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setClientId("ESP32_Device");
  mqttClient.setCredentials("user", "pass");

  // ✅ LWT (Last Will and Testament)
  mqttClient.setWill("esp32/status", 1, true, "offline");

  mqttClient.connect();
}

// Setup function
void setup() {
  Serial.begin(115200);
  
  // WiFi event handlers
  wifiConnectHandler = WiFi.onEvent(onWiFiConnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  wifiDisconnectHandler = WiFi.onEvent(onWiFiDisconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
}

// Loop function
void loop() {
  // ✅ No need to call `mqttClient.loop()`, AsyncMqttClient handles it.
}
