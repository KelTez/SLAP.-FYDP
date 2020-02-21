#include "IMU.h"
#include "Functions.h"
#include <Wire.h>

//TO CHANGE

#define MIN_GARBAGE_THRESH 1000
#define MIN_MAGNET_THRESH 60

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void initIMU(){

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  Serial.println("IMU DETECTED!");
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

sensors_vec_t readIMUValue(){
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  sensors_vec_t storage;
  float xMag[SENSOR_NUM_SAMPLES];
  float yMag[SENSOR_NUM_SAMPLES];
  float zMag[SENSOR_NUM_SAMPLES];

  //Grab multiple samples of data first
  for(int i = 0; i < SENSOR_NUM_SAMPLES; i++){
    xMag[i] = event.magnetic.x;
    yMag[i] = event.magnetic.y;
    zMag[i] = event.magnetic.z;
  }
  
  //find mean of data, filter for consistent vals
  storage.x = filteredMean(xMag);
  storage.y = filteredMean(yMag);
  storage.z = filteredMean(zMag);

  return storage;
}

uint8_t magnetState(){
  sensors_vec_t tmp = readIMUValue();
 
  int xMagGood = tmp.x <= X_MAG_UPPER_THRESH && tmp.x >= X_MAG_LOWER_THRESH; //will need to test
  int yMagGood = tmp.y <= Y_MAG_UPPER_THRESH && tmp.y >= Y_MAG_LOWER_THRESH;
  int zMagGood = tmp.z <= Z_MAG_UPPER_THRESH && tmp.z >= Z_MAG_LOWER_THRESH;
  
  if((xMagGood + yMagGood + 2*zMagGood) >= 2){ //doing this so that if z fails, x and y must pass and vice-versa. may change logic here
    return 1;
  }else{
    return 0;
  }
}
