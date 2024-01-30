#include "irsensor.h"
#include "temperatuur.h"
#include "watersensor.h"
#include "servo.h"

irsensor sensor1;
irsensor sensor2;
temperatuur temp;
WaterLevel watersens;
servo srv;
unsigned long savedTime = 0;
int first = 0;
float tanktemp =0;
float waterheight=0;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    float storagetop = sensor1.getSens1();
    float storagebottom = sensor2.getSens2();
    waterheight = watersens.getWaterLevel();

    if (first == 0) {
      savedTime = millis();  // Record the start time
      first = 1;
    }

    // Check if one second has passed
    if (millis() - savedTime >= 10000) {
    //  tanktemp = temp.getTemp();
      //waterheight = watersens.getWaterLevel();
      first = 0;  // Reset the start time
      savedTime = 0;
  	  }

   // Serial.print("topsensor ");
   // Serial.println(storagetop);
   // Serial.print("bottomsensor ");
   // Serial.println(storagebottom);
   // Serial.print("temperature ");
   // Serial.println(tanktemp);
    Serial.print("waterheight ");
    Serial.println(waterheight);

    if(digitalRead(0)==0)
    {
      srv.ServoTurn();
    }
    //delay(1000);
}
