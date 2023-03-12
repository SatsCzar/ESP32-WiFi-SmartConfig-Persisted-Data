# ESP32-WiFi-SmartConfig-Persisted-Data

This is a simple project that demonstrates how to use the ESP32's SmartConfig feature to configure WiFi credentials, and then persist them using the Preferences library. The ESP32 can then connect to WiFi automatically on subsequent reboots without the need for user intervention.

## Getting Started

### Installing
To install the project, follow these steps:

- Clone the repository to your local machine.
- Open the smartconfig.ino file in the Arduino IDE.
- Install the ESP32 core for Arduino.
- Connect your ESP32 development board to your computer.
- Select your board type and port in the Arduino IDE.
- Click the "Upload" button to compile and upload the sketch to your board.

### Usage
To use the project, follow these steps:

- Upload the sketch to your ESP32 development board as described in the Installing section.
- Launch the [EspTouch](https://www.espressif.com/en/products/software/esp-touch/resources) app on your mobile device and follow the prompts to enter your WiFi credentials.
- The ESP32 will automatically connect to the configured WiFi network on subsequent reboots.

## Contributing
If you'd like to contribute to this project, please fork the repository and submit a pull request. We welcome contributions of all kinds, including bug fixes, new features, and documentation improvements.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
Thanks to the authors of the ESP32 core for Arduino and the Preferences library for making it easy to work with the ESP32's SmartConfig feature and preferences storage functionality.
Thanks to the authors of the HTTPClient library for providing a simple way to make HTTP requests from the ESP32.
