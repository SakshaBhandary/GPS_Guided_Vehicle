#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// GPS module connected to D6 (RX) and D5 (TX) of ESP8266
SoftwareSerial gpsSerial(D6, D5);
TinyGPSPlus gps;

// Target waypoint coordinates (change as needed)
const float targetLat = 12.86758798536401;   // Latitude
const float targetLng = 74.92530863528779;   // Longitude

// Motor driver pins (adjust as per wiring)
const int in1 = D1;
const int in2 = D2;
const int enA = D3;

void setup() {
  Serial.begin(9600);           // Serial Monitor
  gpsSerial.begin(9600);        // GPS module

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  Serial.println("GPS Waypoint Navigation Started...");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      float currentLat = gps.location.lat();
      float currentLng = gps.location.lng();

      Serial.print("Current Location: ");
      Serial.print(currentLat, 6); Serial.print(", ");
      Serial.println(currentLng, 6);

      // Calculate distance to target
      float distance = TinyGPSPlus::distanceBetween(currentLat, currentLng, targetLat, targetLng);
      Serial.print("Distance to Target: ");
      Serial.print(distance); Serial.println(" meters");

      // Navigation logic
      if (distance > 10) {
        // Drive forward
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(enA, 180);  // Adjust speed (0-255)
        Serial.println("Moving toward target...");
      } else {
        // Stop
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA, 0);
        Serial.println("Reached target location.");
      }
    }
  }
}