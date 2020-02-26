#include "IMU.h"
#include "Functions.h"
#include <Wire.h>

void initIMU(){
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
  IMUCalibrate();
  
}

void IMUCalibrate(){
  
/* Display the floating point data */

  for(int i = 0; i < NUM_CALIB_READS; i++){
    mag_vector = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    zBadRange[i] = mag_vector.z();
    if(zBadRange[i] == 0){
      i--;
      delay(50);
      continue;
    }
    delay(10);
  }

  for(int i = 0; i < NUM_CALIB_READS; i++){
 
    if(zBadRange[i] < zBadLeftBound){
      zBadLeftBound = zBadRange[i];
    }
    if(zBadRange[i] > zBadRightBound){
      zBadRightBound = zBadRange[i];
    }

  }

  zBadLeftBound -= LEFT_BOUND_CHANGE;
  zBadRightBound += RIGHT_BOUND_CHANGE;

  Serial.println("Done Calibration");
  Serial.println(zBadRightBound,4);
  Serial.println(zBadLeftBound,4);

} //TO  CHANGE!!!!!!

sensors_vec_t readIMUValue(){
  /* Get a new sensor event */ 
   Serial.println("Entered readIMUValue");
  sensors_vec_t storage;
  float xMag[SENSOR_NUM_SAMPLES],yMag[SENSOR_NUM_SAMPLES],zMag[SENSOR_NUM_SAMPLES];

  //Grab multiple samples of data first
  for(int i = 0; i < SENSOR_NUM_SAMPLES; i++){
    mag_vector = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    zMag[i] = mag_vector.z();
    delay(10);

  }
  
  storage.z = filteredMean(zMag);

  return storage;
}

uint8_t magnetState(){
  Serial.println("Entered Read");
  sensors_vec_t tmp = readIMUValue();
 
  int zMagGood = tmp.z < zBadLeftBound || zBadRightBound < tmp.z; 
  Serial.print("VAL:  ");
  Serial.println(tmp.z);
  if(zMagGood){ 
    return 1;
  }else{
    return 0;
  }

}
