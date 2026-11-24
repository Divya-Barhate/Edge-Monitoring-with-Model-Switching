# Edge Monitoring with Model Switching

A temperature and humidity monitoring project using ESP32 simulation, C-based condition detection, model switching, and a Node-RED dashboard.

## Project Overview

The project reads simulated temperature and humidity values, classifies the conditions as NORMAL, WARNING, or CRITICAL, and sends the results to a Node-RED dashboard.

It also demonstrates switching between two inference model versions (V1 and V2).

## Technologies Used

- C
- C++ / Arduino framework
- ESP32 simulation with Wokwi
- PlatformIO
- Node-RED Dashboard 2.0
- HTTP and JSON

## Main Features

- Simulated temperature and humidity readings
- C-based condition classification
- V1 and V2 model switching
- HTTP communication between ESP32 simulation and Node-RED
- Live dashboard displaying temperature, humidity, and status

## Running the Project

1. Open the project in VS Code.
2. Build it using PlatformIO.
3. Start the Wokwi simulation.
4. Run Node-RED and open the dashboard.
5. Observe the sensor readings and status updates.


