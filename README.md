### Follow these steps to set up and run the project.

### 1. Clone the Repository

```sh
git clone https://github.com/RUM35H/DSI_Server.git
```
### 2. Make sure you have docker.desktop

### 3. Open 'ESP32_code_final.cpp' file using Arduino IDE. 
Then make sure you have libraries:
```sh
WiFi.h
AsyncMqttClient.h
ArduinoJson.h
```
Then change WIFI_SSID and WIFI_PASSWORD. 
NOW upload the code into ESP32 board.

### 4. Build and run the docker-compose file using,
```sh
docker-compose up --build -d
```
### 5. Open grafana dashboard
```sh
http://localhost:8000/grafana/
```
### 6. User credentials
```sh
ADMIN :  (view and edit)
username: admin
password: admin123

VIEWER: (view only)
username: viewer
password:viewer123
```
### 7. Navigate to ESP32 MQTT Dashboard


### Note:
1. mqtt_to_influx.py        :-  to write data into influxdb
2. MQTT_ESP_dashboard.json  :- update this file everytime when you make changes on the dashboard (otherwise it will not automatically update when load the dashboard)
3. random_sensor_data.py    :- you can use this file when you need to send data from python script. (then change queries on the panels as well)
4. onrender_data.txt        :- This is the onrender tab code
