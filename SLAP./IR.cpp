#include "IR.h"
#include <Arduino.h>

uint8_t readIRValue(uint8_t pin){
  
  float flameValue = analogRead(pin)*(3.3/1024.0);
  float distance = 65*pow(flameValue, -1.10);

  if(distance < 35 && distance > 15){ //to test these values
    return 1; 
  }else{
    return 0; 
  }

}
