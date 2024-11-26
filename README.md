# IoT Home Monitoring System with Blynk Integration

## System Overview
This project implements a smart home monitoring system using an ESP32 microcontroller integrated with the Blynk IoT platform. The system monitors environmental conditions and provides remote control capabilities through a web dashboard.

## Key Features
- Real-time temperature and humidity monitoring using DHT22 sensor
- Ambient light level detection using LDR sensor
- Motion detection with PIR sensor
- Automated security alarm system
- Remote temperature control for heating system
- Manual alarm control through mobile app

## Hardware Components
- ESP32 microcontroller
- DHT22 temperature/humidity sensor
- PIR motion sensor
- LDR (Light Dependent Resistor)
- 2 Green LEDs (alarm indicators)
- 1 Red LED (heater indicator)
- Buzzer for alarm sound

## Blynk Dashboard Integration
The system connects to a Blynk dashboard with the following virtual pins:
- V0: Temperature display
- V1: Humidity display
- V2: Light level display
- V3: Manual alarm control switch
- V4: Desired temperature setting

## Key Functionality
1. **Environmental Monitoring**
   - Continuously monitors temperature, humidity, and light levels
   - Data is displayed in real-time on the Blynk dashboard

2. **Smart Security System**
   - Automatically triggers alarm when motion is detected in low light conditions
   - Alarm activation turns on both green LEDs and buzzer
   - Can be manually controlled through the Blynk app

3. **Temperature Control**
   - Users can set desired temperature through the app
   - Automatically activates heater (red LED) when temperature falls below setpoint
   - Heater turns off when desired temperature is reached

## Code Implementation
The code implements:
- WiFi and Blynk connectivity management
- Sensor data reading and processing
- Automated alarm triggering based on motion and light conditions
- Temperature control logic
- Real-time data transmission to Blynk dashboard
- Manual control handling through Blynk virtual pins

## System Operation
The system operates in a continuous loop, performing these tasks:
1. Reads sensor data every 2 seconds
2. Updates Blynk dashboard with current readings
3. Checks motion and light conditions for security
4. Manages temperature control based on user settings
5. Handles manual alarm control from the app
6. Maintains stable connection with Blynk server
