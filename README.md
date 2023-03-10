# PrusaBox sensor kit with WIFI & MQTT


## Table of Contents

- [Hardware Used](#hardware-used)
- [Code Explanation](#code-explanation)
- [Flash Process](#flash-process)
  - [platformio.ini](#platformioini)
  - [configuration.h](#configurationh)
  - [Attention](#attention)
- [Home Assistant Integration](#home-assistant-integration)


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


## Home Assistant Integration

To use the data sent from the PrusaBox sensor kit with WIFI & MQTT in Home Assistant, add the following to your `configuration.yaml` file:

```yaml
mqtt:
    sensor:
    - name: "prusabox_smoke_sensor"
        state_topic: "your_topic"
        unit_of_measurement: "ppm"
        value_template: "{{ value_json.smoke_value }}"

    - name: "prusabox_temperature"
        state_topic: "your_topic"
        unit_of_measurement: "C"
        value_template: "{{ value_json.temperature }}"
```

This will create two sensors in Home Assistant, one for smoke value and one for temperature value. The state_topic should be set to the same value as the MQTT_TOPIC constant in the configuration.h file, but with the placeholder value replaced with your own topic.

The value_template extracts the corresponding values from the received JSON message and updates the sensor state accordingly. The unit_of_measurement specifies the unit of the sensor's state value.

## Hardware Used

To create the PrusaBox sensor kit with WIFI & MQTT, I used the following hardware:

- Smoke Sensor MQ-2: [Amazon](https://www.amazon.com/-/de/dp/B0786DH3BW/ref=sr_1_1?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=5C5OGDEKBP3M&keywords=Sensor+MQ-2&qid=1677296578&sprefix=sensor+mq-2%2Caps%2C167&sr=8-1)
- DS18B20 Temperature Sensor: [Amazon](https://www.amazon.com/-/de/dp/B09NVFJYPS/ref=sr_1_6?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=22RGPX1YVE667&keywords=DS18B20&qid=1677296553&sprefix=ds18b20%2Caps%2C177&sr=8-6)
- 4.7k Ohm Pull-up Resistor: [Amazon](https://www.amazon.com/ELEGOO-Values-Resistor-Assortment-25pcs/dp/B072BL2VX1)

- ESP8266 D1 mini: [Amazon](https://www.amazon.com/-/de/dp/B081PX9YFV/ref=sr_1_3?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=XBKULPN9XP1D&keywords=esp8266&qid=1677296600&sprefix=esp8266%2Caps%2C184&sr=8-3)

The DS18B20 temperature sensor requires a 4.7k ohm pull-up resistor to be connected to the board (between positve + and data DO ).



I hope this information is helpful for creating your own PrusaBox sensor kit with WIFI & MQTT!
