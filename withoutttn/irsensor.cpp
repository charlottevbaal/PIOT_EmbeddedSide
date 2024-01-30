#include "irsensor.h"

int8_t sensor1waarde = 0;

void setup_irsensor() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  pinMode(6, INPUT);
}

int irsensor::getSens1() {
  // put your main code here, to run repeatedly:
  if(digitalRead(23) == 0)
 {
    sensor1waarde =1;
    return sensor1waarde;
  }
  else{
    sensor1waarde = 0;
    return sensor1waarde;
 }

}

int irsensor::getSens2() {
  if(digitalRead(17) == 0)
  {
    return 1;
  }
  else{
    return 0;
  }
}