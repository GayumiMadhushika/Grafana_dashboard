import json
import os
import requests

GRAFANA_URL = os.getenv("GRAFANA_URL", "http://localhost:8000")
GRAFANA_API_TOKEN = os.getenv("GRAFANA_API_TOKEN", "")

HEADERS = {
    "Authorization": f"Bearer {GRAFANA_API_TOKEN}",
    "Content-Type": "application/json"
}

DASHBOARD_JSON = {
    "dashboard": {
        "schemaVersion": 30,
        "title": "Automated Sensor Dashboard",
        "refresh": "5s",
        "timezone": "browser",
        "panels": []
    }
}

devices = {
    "1": ["IR_Sensor_1", "K_Type_Sensor_1", "Current_Miller_1", "Current_Mixer_1"],
    "2": ["IR_Sensor_2", "K_Type_Sensor_2", "Current_Miller_2", "Current_Mixer_2"],
    "3": ["IR_Sensor_3", "K_Type_Sensor_3", "Current_Miller_3", "Current_Mixer_3"]
}

x_pos = 0
for device, sensors in devices.items():
    panel = {
        "title": f"Device {device}",
        "type": "stat",
        "gridPos": {"x": x_pos, "y": 0, "w": 4, "h": 8},
        "targets": [
            {
                "refId": chr(65 + i),
                "datasource": "InfluxDB",
                "rawQuery": True,
                "query": f'SELECT last("{sensor}") FROM "sensor_data" WHERE "device" = \'{device}\' AND time > now() - 1h'
            }
            for i, sensor in enumerate(sensors)
        ],
        "fieldConfig": {"defaults": {"displayName": f"Device {device} Sensors"}}
    }
    DASHBOARD_JSON["dashboard"]["panels"].append(panel)
    x_pos += 4

response = requests.post(
    f"{GRAFANA_URL}/api/dashboards/db",
    headers=HEADERS,
    json=DASHBOARD_JSON
)

print(response.json())
