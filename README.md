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

## Hardware Connections

The load cell is connected to the HX711 load-cell amplifier, which interfaces with the ESP32 microcontroller.

| HX711 Pin | ESP32 Connection |
|---|---|
| VCC | 3v3 |
| GND | GND |
| DT  |  18 |
| SCK | 19 |

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

## Calibration

The load-cell measurements are acquired using the HX711 amplifier and processed by the ESP32.

- **Calibration method:** Empirical calibration using known reference weights.
- **Calibration factor:** 189.51 counts per gram, determined experimentally.
- **Tare operation:** The zero-load reference is calculated by averaging 20 raw HX711 readings at startup (`read_average(20)`).
- **Measurement unit:** Mass in grams (g) and calculated force in Newtons (N).

The mass is calculated by subtracting the zero-load reference from the raw reading and dividing by the calibration factor. Force is calculated using \(F = mg\), with gravitational acceleration taken as 9.81 m/s².

Calibration should be repeated if the load cell is remounted or the mechanical arrangement changes.

## Limitations

- Measurement accuracy depends on calibration, load-cell mounting, and the correct application of force.
- Readings may fluctuate due to electrical noise, mechanical movement, vibration, or loose connections.
- The maximum rated load of the load cell is 10 kg; this is its rated mass capacity under the specified operating conditions, not a guarantee of accuracy across the entire range.
- The system's accuracy and repeatability have not been formally established against a certified reference instrument.
- The zero reference is established at startup, so the load cell should be unloaded during initialization.
- The displayed force is calculated from the measured equivalent mass using standard gravitational acceleration; it is not an independent direct force measurement.
- Wireless display requires the mobile device to connect to the ESP32's local Wi-Fi access point.
  
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
