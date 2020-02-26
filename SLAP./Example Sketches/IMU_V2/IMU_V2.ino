#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define NUM_CALIB_READS 10  
#define LEFT_BOUND_CHANGE 4 //how much we can shift left from our zbound before we are def under a car
#define RIGHT_BOUND_CHANGE 4   //how much we can shift left from our zbound before we are def under a car\ 
//^ the above assumes that the location of the pod is center

Adafruit_BNO055 bno = Adafruit_BNO055();
float zBadRange[NUM_CALIB_READS],xBadRange[NUM_CALIB_READS],yBadRange[NUM_CALIB_READS];
float zBadRightBound = -10000;
float zBadLeftBound= 100000;
float xBadRightBound,xBadLeftBound= 0.0;
float yBadRightBound,yBadLeftBound= 0.0;
int calibrate = 1;
int count = 0;
int startCalib = 1;
imu::Vector<3> mag_vector;

void setup(void) 
{

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); 
  Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);

  IMUCalibrate();
}

void IMUCalibrate(){
  Serial.println("Calibrating...");
  for(int i = 0; i < NUM_CALIB_READS; i++){
    mag_vector = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    zBadRange[i] = mag_vector.z();
    Serial.print(i);
    Serial.print(":    ");
    Serial.println(zBadRange[i]);
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

  Serial.println("");
  Serial.println("Done Calibration");
  Serial.println(zBadRightBound,4);
  Serial.println(zBadLeftBound,4);
  Serial.println("Starting Reads...");
  Serial.println("--------------------------------------------------------------------------------------");
  Serial.println("--------------------------------------------------------------------------------------");
  Serial.println("--------------------------------------------------------------------------------------");
  calibrate = 0;
}

void loop(void) {
  /* Get a new sensor event */ 
  imu::Vector<3> mag_vector = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER); 

  float z = mag_vector.z(); //using sqrt to get smaller vals

  int zGood = z < zBadLeftBound || zBadRightBound < z; //EX: (zBadLeftBound)012|345678(zBadRange)|9(zBadRightBound)
  if(!calibrate){
  if(zGood){
    Serial.println("under car");
  }else{
    Serial.println("not under car");
  }
  
  Serial.print("Z: ");
  Serial.print(z, 4);

  Serial.println("");
  Serial.println("--------------------------------------------------------------------------------------");
  Serial.println("");
  }
  delay(1000);

}
