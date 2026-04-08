# 👨‍💻 Author
M. Shoyab Sadik  
[LinkedIn](https://www.linkedin.com/in/shoyab-sadik/)  
[Website](https://shoyab-sadik.github.io/)  
[WhatsApp](https://wa.me/8801575317604)  
Pico Robotics

# Mega Agriculture Robot 🌱🤖

A smart agriculture robot developed using Arduino and sensors.

## 🚀 Features
- Soil moisture detection 🌱
- Automatic water pump 💧
- Temperature & humidity monitoring 🌡️
- Bluetooth control (HC-05) 📱
- Obstacle detection 🚧
- Solar power monitoring ☀️

## 🧰 Components
- Arduino
- DHT11
- Soil Sensor
- Ultrasonic Sensor
- Servo Motor
- HC-05
- LCD (I2C)
- Pump & Buzzer

## 📋 Control Commands
| Command | Action |
|---------|-------|
| F       | Move Forward |
| B       | Move Backward |
| L       | Turn Left |
| R       | Turn Right |
| S       | Stop All |
| s       | Continuous Servo |
| A       | Automatic Seed Planter Mode |
| P       | Pump ON |
| O       | Pump OFF |

## ⚙️ Working Principle
1. Soil sensor monitors moisture and triggers pump or buzzer if dry.  
2. DHT11 monitors temperature & humidity, displayed on LCD and via Bluetooth.  
3. Servo moves for planting in automatic mode or continuous mode.  
4. Ultrasonic sensor detects obstacles and activates buzzer.  
5. Bluetooth commands control robot manually.  

## 🌟 Future Improvements
- Add solar battery level display  
- Add mobile app UI for live monitoring  
- Integrate camera for crop monitoring  
