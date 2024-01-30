#include <TTN_esp32.h>
#include "TTN_CayenneLPP.h"
#include "irsensor.h"
#include "temperatuur.h"
#include "watersensor.h"
#include "servo.h"


const char* devEui = "70B3D57ED006355C"; // Change to TTN Device EUI
const char* appEui = "8E686D26297179B4"; // Change to TTN Application EUI
const char* appKey = "BD0EF30271EA3FD6B78B742A02012604"; // Chaneg to TTN Application Key

irsensor sensor1;
irsensor sensor2;
temperatuur temp;
WaterLevel watersens;
TTN_esp32 ttn ;
TTN_CayenneLPP lpp;
servo srv;
unsigned long savedTime = 0;
int first = 0;
float tanktemp =0;
float waterheight=0;
int feedvar = 0;


void message(const uint8_t* payload, size_t size, uint8_t port, int rssi)
{
    Serial.println("-- MESSAGE");
    Serial.printf("Received %d bytes on port %d (RSSI=%ddB) :", size, port, rssi);
    int downlinkIntegerTotal=0;
    String downlinkStringTotal="";
    char downlinkString;
    int downlinkInteger;
    for (int i = 0; i < size; i++)
    {
        Serial.printf(" %02X", payload[i]);
        downlinkInteger = payload[i];
        downlinkString=char(downlinkInteger);
        downlinkStringTotal = downlinkStringTotal + downlinkString;

    if(i==0){  // first byte does not have to be multiplied with a power of 16
        downlinkIntegerTotal=downlinkIntegerTotal+downlinkInteger;
    }else{
        downlinkIntegerTotal=downlinkIntegerTotal+downlinkInteger*pow(16,2*i); //the parts are grouped in 2, so use a power of 2 times i
    }
            
    Serial.print("ASCII value:");
    Serial.println(downlinkString); 
    Serial.print("integer:");
    Serial.println(downlinkInteger); 
    Serial.println("");
    }

    Serial.print("Total downlink string = ");
    Serial.println(downlinkStringTotal);
    Serial.print("Total downlink value = ");
    Serial.println(downlinkIntegerTotal);        

    Serial.println();

    if(downlinkStringTotal == "FEED")
    {
      getmessageval(1);
      //downlinkIntegerTotal = 0;
      //downlinkStringTotal = "";
      delay(2000);
      getmessageval(0);
    }

}

int getmessageval(int messageval)
{
  feedvar = messageval;
  return feedvar;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting");
    ttn.begin();
    ttn.onMessage(message); // Declare callback function for handling downlink
                            // messages from server
    ttn.join(devEui, appEui, appKey);
    Serial.print("Joining TTN ");
    while (!ttn.isJoined())
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\njoined !");
    ttn.showStatus();
}

void loop()
{
  //FEED is codeword
    float storagetop = sensor1.getSens1();
    float storagebottom = sensor2.getSens2();

    if (first == 0) {
      savedTime = millis();  // Record the start time
      first = 1;
    }

    // Check if one second has passed
    if (millis() - savedTime >= 10000) {
      tanktemp = temp.getTemp();
      waterheight = watersens.getWaterLevel();
      first = 0;  // Reset the start time
      savedTime = 0;
  	  }
    lpp.reset();
   // lpp.addTemperature(1, tanktemp);
    lpp.addDigitalOutput(2, storagetop);
    lpp.addDigitalOutput(1, storagebottom);
    lpp.addAnalogOutput(1, waterheight);
    lpp.addTemperature(1, tanktemp);
    //Serial.println(feedvar);

    if(feedvar == 1 || digitalRead(0)==0)
    {
      srv.ServoTurn();
    }


    if (ttn.sendBytes(lpp.getBuffer(), lpp.getSize()))
    {
        Serial.printf("Sensor1: %f TTN_CayenneLPP: %d %x %02X%02X\n", tanktemp, lpp.getBuffer()[0], lpp.getBuffer()[1],
            lpp.getBuffer()[2], lpp.getBuffer()[3]);
    }
    delay(2000);
}