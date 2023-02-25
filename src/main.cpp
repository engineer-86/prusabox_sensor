#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "config.h"
#include <ArduinoJson.h>

const int SMOKE_SENSOR_PIN = A0;
const int TEMP_SENSOR_PIN = D1;
OneWire onewire(D1);
DallasTemperature sensors(&onewire);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(SMOKE_SENSOR_PIN, INPUT);
  sensors.begin();
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  sensors.requestTemperatures();
  int smokeValue = analogRead(SMOKE_SENSOR_PIN);
  float temperature = sensors.getTempCByIndex(0);

  Serial.print("Smoke Value: ");
  Serial.println(smokeValue);
  Serial.print("Temp ");
  Serial.print(temperature);
  Serial.println("C");

  // Send smoke value and temperature to MQTT broker
  char msg[50];
  snprintf(msg, 50, "Smoke Value: %d", smokeValue);
  client.publish("smoke", msg);
  snprintf(msg, 50, "Temperature: %.2fC", temperature);
  client.publish("temperature", msg);

  delay(1000);
}

void setup_wifi() {
  // Connect to Wi-Fi network
  WiFi.begin("your_ssid", "your_password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  // Reconnect to MQTT broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("ESP8266Client", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}