#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// Initialize GPS
SoftwareSerial gpsSerial(D6, D5);  // RX, TX for GPS
TinyGPSPlus gps;

// Initialize compass
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// Target waypoint coordinates
const float targetLat = 12.9716;
const float targetLng = 77.5946;

// Motor driver pins
const int in1 = D1;
const int in2 = D2;
const int enA = D3;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Wire.begin();

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  if (!mag.begin()) {
    Serial.println("Could not find a valid HMC5883L sensor. Check wiring!");
    while (1);
  }

  Serial.println("GPS + Compass AGV Initialized");
}

float getHeading() {
  sensors_event_t event;
  mag.getEvent(&event);

  float heading = atan2(event.magnetic.y, event.magnetic.x);
  heading = heading * 180 / PI;

  if (heading < 0) heading += 360;
  return heading;
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      float currentLat = gps.location.lat();
      float currentLng = gps.location.lng();

      float distance = TinyGPSPlus::distanceBetween(currentLat, currentLng, targetLat, targetLng);
      float bearing = TinyGPSPlus::courseTo(currentLat, currentLng, targetLat, targetLng);
      float heading = getHeading();

      Serial.print("Distance to target: "); Serial.print(distance); Serial.println(" m");
      Serial.print("Target Bearing: "); Serial.print(bearing); Serial.print("°, ");
      Serial.print("Heading: "); Serial.print(heading); Serial.println("°");

      // If heading is not aligned with target bearing, turn
      float angleDiff = bearing - heading;
      if (angleDiff < -180) angleDiff += 360;
      if (angleDiff > 180) angleDiff -= 360;

      if (distance > 10) {
        if (abs(angleDiff) > 15) {
          if (angleDiff > 0) {
            // Turn right
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(enA, 150);
            Serial.println("Turning right...");
          } else {
            // Turn left
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            analogWrite(enA, 150);
            Serial.println("Turning left...");
          }
        } else {
          // Move forward
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          analogWrite(enA, 200);
          Serial.println("Moving forward...");
        }
      } else {
        // Stop at destination
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA, 0);
        Serial.println("Target reached.");
      }
    }
  }
}