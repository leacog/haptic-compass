#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

void setup() {  
  for(int i; i < 8; i++){
    pinMode((i+2), OUTPUT); //Initialize digital pins 2-10 for output
  }
  if (!mag.begin()) {
    Serial.println("No LSM303 detected");
    while (1); //Does nothing if I2C fails to initialize
  }
}

void loop() {
  sensors_event_t event; //Sensor event struct from adafruit sensor library
  static float Pi = 3.14159;
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi; // Returns in degrees the angle to the x-axis (as defined on the breakout board) But does not ajust for compass not being in plane
  setHaptic(heading);
  delay(300);
}

void setHaptic(float heading) {
  static int prevHapPosition;
  int hapPosition = (int)map(heading, -180, 180, 0, 7.99); //Mapping to close to 8 to get correct rounding behaviour 
  if(hapPosition != prevHapPosition) {
    int hapPin = hapPosition + 2; //Pins start at 2 and go to 10
    int prevHapPin = prevHapPosition + 2;
    digitalWrite(hapPin, HIGH);
    digitalWrite(prevHapPin, LOW);
  }  
  prevHapPosition = hapPosition;
}
