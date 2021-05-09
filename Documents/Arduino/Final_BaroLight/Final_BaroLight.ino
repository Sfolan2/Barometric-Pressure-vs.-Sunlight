#include <TimeLib.h>
#include <Adafruit_MPL3115A2.h>
#include <Wire.h>
#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Set time at start
  setTime(22, 17, 0, 1, 1, 1970);
  //Set up for LED
  pinMode(LED_BUILTIN, OUTPUT);
}
//Define hour 10, 11, 12, 13, 14, 15, 16, 17, 18
int nexthour=10;
//Define minute 0, 15, 30, 45
int nextminute=0;
//Define baro object
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
//define address
int addr=0;

//define struct Valur which holds all info
struct Value
{
  unsigned char hour_;
  unsigned char minute_;
  float voltage;
  float inHg;
};

//We want to take a sunlight and baro value every 15 minutes from
//10:00 to 18:00
void loop() {
  //make sure sensor is working properly
  if(!baro.begin())
  {
    //Serial.println("Couldn't find sensor");
    return;
  }

  //Define current time
  time_t t = now();

  //Check if it is the correct time interval
  if(hour(t)==nexthour&&minute(t)==nextminute)
  {
    //Calculate pressure
    float pressure = baro.getPressure();
    pressure/=3377.;

    //Calculate sunlight
    int sensorValue=analogRead(A0);
    float voltage= sensorValue*(5.0/1023.0);

    //convert to unsigned char to save space
    unsigned char h=(unsigned char)hour(t);
    unsigned char m=(unsigned char)minute(t);

    Value info;//={hour(t), minute(t), voltage, pressure};
    info.hour_=h;
    info.minute_=m;
    info.voltage=voltage;
    info.inHg=pressure;


    EEPROM.put(addr, info);

    nextminute+=15;
    if(nextminute>=60)
    {
      nextminute=0;
      nexthour++;
    }
    if(nexthour>=18&& nextminute!=0)
    {
      nexthour=10;
      nextminute=0;
    }
  addr+=sizeof(Value);
  if(addr>=1000)
  {
    addr=0;
  }

  }
  //Serial.print("Delay Ended");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    //This LED was put in so that the arduino would
  delay(13000);                      //consume more power so I could use a power bank
}
