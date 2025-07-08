# Waypoint Autonomous Guided Vehicle with GPS
The project implements a GPS-guided autonomous vehicle capable of navigating to predefined waypoints (like “home” or “store”) using real-time GPS and compass data. Built around the **ESP8266**, the system processes GPS coordinates and compares them with target waypoints to control motion via **L298N motor driver**, enabling autonomous point-to-point navigation without manual intervention.

## Features <img src="https://github.com/user-attachments/assets/e73e06e2-8952-4ae5-9ee0-664cf7a6ffaf" width="20" height="20">

1. Real-time GPS-based autonomous navigation
2. Waypoint tracking and dynamic course correction
3. Wireless handling with ESP8266
4. Motor control via L298N based on coordinate delta
5. Modular code for new waypoints and navigation logic

## Technologies <img src="https://github.com/user-attachments/assets/e4bde167-a599-4461-9c0a-c702ca337451" width="20" height="20">

- **ESP8266 NodeMCU** – Main controller for logic and Wi-Fi
- **GPS Module (e.g., NEO-6M)** – Provides real-time location
- **HMC5883L Compass** – For heading direction (optional)
- **L298N Motor Driver** – Controls motors for forward, reverse, turns
- **Arduino IDE** – For firmware development

## Future Improvements <img src="https://github.com/user-attachments/assets/5d819501-645e-45f6-ba4e-4ce553e66356" width="20" height="20">

• Including obstacle sensors for obstacle avoidance <br/> 
• Enabling multi-waypoint path planning <br/>
• Integrating web dashboard for live tracking
