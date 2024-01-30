#ifndef WATERSENSOR_H    
#define WATERSENSOR_H    


#include <Arduino.h>

  class WaterLevel{
    public:
    float getWaterLevel(void);
    float waterlevel;
    float levelinmm;

    private:
    
  };



#endif // WATERSENSOR_H  