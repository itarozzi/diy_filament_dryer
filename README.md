3D Printer Filament Dryer Controller  
=========================================

A project based on ESP32 & TFT TouchScreen to control heater for a DIY 3D Printer filament dryer.

For the UI  LVGL 9 and [EEZ-Studio](https://github.com/eez-open/studio) are used, with some automation done with EEZ-Flow.

The controller is connected to MQTT Broker via WiFi, to send sensors and actuators data and to permit also remote control.

Node-RED is used to intercat with MQTT data and commands.



![screenshot](docs/screenshot1.png)