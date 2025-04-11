import time
import random
from influxdb import InfluxDBClient

client = InfluxDBClient(host="influxdb", port=8086, database="grafana")

while True:
    json_body = [
        {
            "measurement": "sensor_data",
            "tags": {"device": "1"},
            "fields": {
                "IR_Sensor_1": round(random.uniform(20, 50), 2),
                "K_Type_Sensor_1": round(random.uniform(10, 30), 2),
                "Current_Miller_1": round(random.uniform(30, 60), 2),
                "Current_Mixer_1": round(random.uniform(15, 40), 2),
            },
        },
        {
            "measurement": "sensor_data",
            "tags": {"device": "2"},
            "fields": {
                "IR_Sensor_2": round(random.uniform(20, 50), 2),
                "K_Type_Sensor_2": round(random.uniform(10, 30), 2),
                "Current_Miller_2": round(random.uniform(30, 60), 2),
                "Current_Mixer_2": round(random.uniform(15, 40), 2),
            },
        },
        {
            "measurement": "sensor_data",
            "tags": {"device": "3"},
            "fields": {
                "IR_Sensor_3": round(random.uniform(20, 50), 2),
                "K_Type_Sensor_3": round(random.uniform(10, 30), 2),
                "Current_Miller_3": round(random.uniform(30, 60), 2),
                "Current_Mixer_3": round(random.uniform(15, 40), 2),
            },
        },
    ]

    client.write_points(json_body)
    print("✅ Data written to InfluxDB")
    time.sleep(5)
