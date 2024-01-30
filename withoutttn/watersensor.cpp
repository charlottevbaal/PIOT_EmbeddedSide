#include "watersensor.h"
#include "Arduino.h"

float WaterLevel::getWaterLevel(){
    waterlevel = analogRead(39);
    //misschien kijken naar conversion van analog naar cm waarde
    //4 cm is verschil van 1000
    //per mm 25 omhoog
    levelinmm = (waterlevel-750)/65;
    if(waterlevel == 0)
    {
      return 0;
    }
    else{
    return 40 - levelinmm;
    }
}