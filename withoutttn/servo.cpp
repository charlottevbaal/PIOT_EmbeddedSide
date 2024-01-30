//#include <Servo.h>
#include <ESP32Servo.h>
#include <Arduino.h>
#include "servo.h"

  const long interval = 1000;
  unsigned long previousMillis = 0;
  int timer =5;
  Servo myServo;
  unsigned long realtime = 0;
  int firsttime = 0;
  int done = 0;
  unsigned long startTime = 0;  // Variable to store the start time

void servo::ServoTurn(void)
{
  myServo.attach(12);  // attaches the servo on pin 9 to the servo object
  done = 0;
  while(done == 0){
   // Serial.println("IR Sensor detected!");

    if (firsttime == 0) {
      startTime = millis();  // Record the start time
      myServo.write(180);  // Set servo to maximum speed in one direction
      firsttime = 1;
    }

    // Check if one second has passed
    if (millis() - startTime >= 200) {
      myServo.write(90);  // Set servo to stop
      firsttime = 0;  // Reset the start time
      startTime = 0;
      done = 1;
}
}

  }
  