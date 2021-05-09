#include <EEPROM.h>
/*
 * I used https://www.arduino.cc/en/Reference/EEPROM as a reference
 * for using EEPROM on Arduino
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int addr=0;
//Create struct for each Value
struct Value
{
  unsigned char hour_;
  unsigned char minute_;
  float voltage;
  float inHg;
};
int i=0;
void loop() {
  // put your main code here, to run repeatedly:
  Value var;
    //Print out sunlight Values
    for(int i =0; i<EEPROM.length();i+=sizeof(Value))
    {
      EEPROM.get(i, var);
      //Serial.print(var.hour_);
      //Serial.print(", ");
      //Serial.print(var.minute_);
      //Serial.print(", ");
      Serial.print(var.voltage);
      Serial.println();
    }
    for(int i =0; i<EEPROM.length();i+=sizeof(Value))
    {
      EEPROM.get(i, var);
      //Serial.print(var.hour_);
      //Serial.print(", ");
      //Serial.print(var.minute_);
      //Serial.print(", ");
      Serial.print(var.inHg);
      Serial.println();
    }
    Serial.println("////////////////////////////");
  delay(100000);
}
