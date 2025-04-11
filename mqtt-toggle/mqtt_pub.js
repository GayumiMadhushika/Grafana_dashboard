const express = require('express');    //create a web server
const mqtt = require('mqtt');    //mqtt client library
const cors = require('cors');    //cross origin resource sharing

const app = express();
const PORT = 1880;  //surver is run at this port

app.use(cors());    //allow frontend to make request to backend
app.use(express.json());

const mqttClient = mqtt.connect('mqtt://mosquitto:1883', {     //connect to local mqtt broker(mosquitto = container name)
  clientId: 'toggle-publisher',   //publisher name
  clean: true    //to remove previouse subscriptions
});

mqttClient.on('connect', () => {
  console.log('Connected to MQTT broker');
});

mqttClient.on('error', (err) => {
  console.error('MQTT connection error:', err.message);
});

app.post('/publish', (req, res) => {        //listen POST request at 1880 port
  const { topic, payload } = req.body;       //object restructuring to grab topic and payload
  console.log('Incoming publish request:', req.body);

  if (!topic || payload === undefined) {      //to check required data is included or not
    console.error(' Missing topic or payload in request');
    return res.status(400).send('Missing topic or payload');
  }

  mqttClient.publish(topic, String(payload), { qos: 2, retain: true }, (err) => {  //QOS2= garanteed delivery exactly once
    if (err) {
      console.error('Publish failed:', err.message);   
      return res.status(500).send('Failed to publish');
    }

    console.log(` Published to topic: ${topic} | Payload: ${payload}`);
    res.send('Published');
  });
});

app.listen(PORT, () => {    //start the server and listen for HTTP request
  console.log(`Server is running at http://localhost:${PORT}`);
});
