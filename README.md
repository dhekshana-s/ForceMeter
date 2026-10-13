# ForceMeter — ESP32-Based Digital Load Measurement System

## Overview

ForceMeter is a load measurement project built using an ESP32 microcontroller, a load cell, and an HX711 load-cell amplifier. It reads the load-cell output and displays the measurements on a web page accessible from a mobile phone or laptop.

The ESP32 creates its own Wi-Fi access point, allowing a connected device to access the measurement interface without relying on a home or college Wi-Fi network.

## Features

- Load measurement using a load cell and HX711 amplifier
- ESP32-based sensor data acquisition
- Wireless access through an ESP32-hosted Wi-Fi network
- Web-based display of live readings
- Access to the interface through a mobile phone or laptop

## Hardware Components

- ESP32 development board
- Load cell
- HX711 load-cell amplifier module
- Connecting wires
- Mobile phone or laptop for viewing the readings

## How It Works

1. The load cell responds to an applied load by producing a small electrical signal.
2. The HX711 amplifies and digitizes the signal for the ESP32.
3. The ESP32 reads the measurement data and processes it using the program.
4. The ESP32 hosts a Wi-Fi access point and a web page.
5. A connected phone or laptop can open the web interface to view the readings.

## How to Use

1. Connect the load cell to the HX711 module and connect the module to the ESP32 according to the wiring used in the project.
2. Upload `ForceMeter.ino` to the ESP32 using the Arduino IDE.
3. Power on the ESP32.
4. Connect a phone or laptop to the `ForceMeter` Wi-Fi network.
5. Open `192.168.4.1` in a web browser to access the measurement page.

## Software and Tools

- Arduino IDE
- Embedded C++ / Arduino programming
- ESP32 Wi-Fi and web server functionality

## Project Purpose

This project demonstrates the integration of a load sensor, signal-conditioning and data-conversion hardware, a microcontroller, and a wireless web interface for real-time measurement.

## Future Improvements

- Add a clear calibration procedure and measurement-unit selection.
- Improve measurement stability and accuracy.
- Add a wiring diagram and demonstration photos.
- Document the tested measurement range and calibration results.

## Repository Contents

- `ForceMeter.ino` — ESP32 program for load measurement and the web interface.
- `README.md` — Project overview, hardware description, and usage instructions.
