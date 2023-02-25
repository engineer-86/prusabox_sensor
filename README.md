# PrusaBox sensor kit with WIFI & MQTT


## Code Explanation

## Code Explanation

This code is written in C++ to run on an ESP8266 board as part of the PrusaBox sensor kit with WIFI & MQTT. It uses libraries to read temperature data from a Dallas Temperature sensor and smoke data from an analog sensor, and sends this data to an MQTT broker over a Wi-Fi network.

### Libraries Used

The code includes the following libraries:

- `Arduino.h`
- `OneWire` by Jim Studt ([GitHub](https://github.com/PaulStoffregen/OneWire))
- `DallasTemperature` by Miles Burton ([GitHub](https://github.com/milesburton/Arduino-Temperature-Control-Library))
- `ESP8266WiFi` by Ivan Grokhotkov ([GitHub](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi))
- `PubSubClient` by Nick O'Leary ([GitHub](https://github.com/knolleary/pubsubclient))
- `ArduinoJson` by Benoit Blanchon ([GitHub](https://github.com/bblanchon/ArduinoJson))

### Code Functionality

The code starts by defining the `SMOKE_SENSOR_PIN` and `TEMP_SENSOR_PIN` constants, and creating an instance of `OneWire` and `DallasTemperature` to read temperature data from the Dallas Temperature sensor.

The `setupWiFi` function connects the board to the Wi-Fi network using the `WIFI_SSID` and `WIFI_PASSWORD` constants defined in `configuration.h`. It also waits until the board is connected to the network before proceeding.

The `reconnect` function connects the board to the MQTT broker using the `MQTT_CLIENT_ID`, `MQTT_USERNAME`, and `MQTT_PASSWORD` constants defined in `configuration.h`. It keeps trying to connect until successful.

The `setup` function initializes the serial port, sets the smoke sensor pin as an input, initializes the Dallas Temperature sensor, connects to the Wi-Fi network, and sets the MQTT broker address and port.

The `loop` function continuously reads smoke and temperature data from the sensors, creates a JSON object from this data using the `ArduinoJson` library, serializes the JSON object to a string, and sends the string to the MQTT broker using the `PubSubClient` library. The `delay` function is used to wait for 1 second between readings.

Overall, this code demonstrates how to use various libraries to read data from sensors and send it to an MQTT broker, making it a useful component of the PrusaBox sensor kit with WIFI & MQTT for IoT projects.


# Flash process

## platformio.ini

If you want to use this code sample with PlatformIO, make sure to use the following settings in your `platformio.ini` file:

```ini
[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino
monitor_speed = 115200
monitor_port = COM5
upload_port = COM5
upload_speed = 115200
lib_deps = 
	milesburton/DallasTemperature@^3.11.0
	paulstoffregen/OneWire@^2.3.7
	bblanchon/ArduinoJson@^6.20.1
	knolleary/PubSubClient@^2.8

```
## configuration.h

To configure this code for your own use, rename the `configuration.h.template` file to `configuration.h`, and then modify the settings as needed with your own values:

```cpp
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define MQTT_SERVER "your_mqtt_server"
#define MQTT_PORT 1883
#define MQTT_USERNAME "your_username"
#define MQTT_PASSWORD "your_password"
#define MQTT_CLIENT_ID "your_client_id"
#define MQTT_TOPIC "your_topic"

#endif
```
## Attention

Before using the code, make sure to update the `configuration.h` file with your own settings for your Wi-Fi network, MQTT server, username, password, client ID, and topic. Be sure to remove the `.template` extension from the filename before using the file, as this is just a placeholder file with example values.
