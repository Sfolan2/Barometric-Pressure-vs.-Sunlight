#include <EEPROM.h>
/*
 * I used https://www.arduino.cc/en/Reference/EEPROM as a reference
 * for using EEPROM on Arduino
 * 
 * This code just clears the EEPROM so fresh values can be put in
 */
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0;i<EEPROM.length();i++)
  {
    EEPROM.write(i,0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
