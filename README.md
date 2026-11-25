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

### Prerequisites
- Visual Studio Code
- PlatformIO IDE extension
- Wokwi ESP32 simulator
- Node-RED with Dashboard 2.0 installed

### Setup and Execution

1. **Open the Project:** Open the project directory in Visual Studio Code.
2. **Configure the Environment:** Verify the PlatformIO configuration and required project dependencies.
3. **Build the Firmware:** Use PlatformIO to compile the ESP32 application.
4. **Launch the Simulation:** Start the Wokwi simulation and monitor the serial output for sensor readings, condition classifications, and model version updates.
5. **Start the Dashboard:** Run Node-RED and deploy the flow configured to receive sensor data through the `/api/sensor` HTTP endpoint.
6. **Monitor System Output:** Open the Node-RED dashboard to observe temperature, humidity, and operating status updates in real time.

### Expected Results

The simulation displays sensor readings and classifies operating conditions as **NORMAL**, **WARNING**, or **CRITICAL**. The system also demonstrates switching between inference model versions V1 and V2, with the resulting data visualized on the Node-RED dashboard.



