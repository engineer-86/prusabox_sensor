#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <configuration.h>

const int SMOKE_SENSOR_PIN = A0;
const int TEMP_SENSOR_PIN = D1;
OneWire onewire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&onewire);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(SMOKE_SENSOR_PIN, INPUT);
  sensors.begin();
  setupWiFi();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  sensors.requestTemperatures();
  int smokeValue = analogRead(SMOKE_SENSOR_PIN);
  int temperature = sensors.getTempCByIndex(0);

  Serial.print("Smoke Value: ");
  Serial.print(smokeValue);
  Serial.println("ppm");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  // Create JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["smoke_value"] = smokeValue;
  jsonDoc["temperature"] = temperature;

  // Serialize JSON object to string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send JSON object to MQTT broker
  mqttClient.publish(MQTT_TOPIC, jsonString.c_str());

  delay(1000);
}



