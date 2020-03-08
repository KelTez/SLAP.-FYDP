#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define NUM_CALIB_READS 10  
#define LEFT_BOUND_CHANGE 0 //how much we can shift left from our zbound before we are def under a car
#define RIGHT_BOUND_CHANGE 0 //how much we can shift left from our zbound before we are def under a car\ 
//^ the above assumes that the location of the pod is center

Adafruit_BNO055 bno = Adafruit_BNO055();
float zBadRange[NUM_CALIB_READS],xBadRange[NUM_CALIB_READS],yBadRange[NUM_CALIB_READS];
float zBadRightBound,zBadLeftBound= 0;
float xBadRightBound,xBadLeftBound= 0;
float yBadRightBound,yBadLeftBound= 0;
int calibrate = 1;
int count = 0;

void IMUCalibrate(sensors_event_t event){
  
  /* Display the floating point data */
  if(calibrate){

    for(int i = 0; i < NUM_CALIB_READS; i++){
      bno.getEvent(&event);
      zBadRange[i] = event.magnetic.z;
      xBadRange[i] = event.magnetic.x;
      yBadRange[i] = event.magnetic.y;
      Serial.print(zBadRange[i]);
      Serial.print(xBadRange[i]);
      Serial.print(yBadRange[i]);
      Serial.print("   ");
      delay(10);
    }
  


}}

void setup(void) 
{

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
  
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 

  

  bno.getEvent(&event);

  float z = event.magnetic.z; //magnetic
  float x = event.magnetic.x;
  float y = event.magnetic.y;
  if(calibrate){
    if(count == 0){
      count++;
      }else{
      zBadRange[count] = z;
      Serial.print(zBadRange[count],4);
      Serial.print("hmmm ->   ");
      delay(10);
      count++;
      }
   }

  if(count == NUM_CALIB_READS && calibrate){
   for(int i = 0; i < NUM_CALIB_READS; i++){
 
      if(zBadRange[i] < zBadLeftBound){
        zBadLeftBound = zBadRange[i];
      }
      if(zBadRange[i] > zBadRightBound){
        zBadRightBound = zBadRange[i];
      }
      if(xBadRange[i] < xBadLeftBound){
        xBadLeftBound = xBadRange[i];
      }
      if(xBadRange[i] > xBadRightBound){
        xBadRightBound = xBadRange[i];
      }
      if(yBadRange[i] < yBadLeftBound){
        yBadLeftBound = yBadRange[i];
      }
      if(yBadRange[i] > yBadRightBound){
        yBadRightBound = yBadRange[i];
      }

   }

    zBadLeftBound -= LEFT_BOUND_CHANGE;
    zBadRightBound += RIGHT_BOUND_CHANGE;
    xBadLeftBound -= LEFT_BOUND_CHANGE;
    xBadRightBound += RIGHT_BOUND_CHANGE;
    yBadLeftBound -= LEFT_BOUND_CHANGE;
    yBadRightBound += RIGHT_BOUND_CHANGE;
    Serial.println("");
    Serial.println("Done Calibration");
    Serial.println(xBadRightBound,4);
    Serial.println(xBadLeftBound,4);
    Serial.println(yBadRightBound,4);
    Serial.println(yBadLeftBound,4);
    Serial.println(zBadRightBound,4);
    Serial.println(zBadLeftBound,4);
    calibrate = 0;
  }
  //if(count == NUM_CALIB_READS && !calibrate){
  int zGood = z < zBadLeftBound || zBadRightBound < z; //EX: (zBadLeftBound)012|345678(zBadRange)|9(zBadRightBound)

  if(zGood){
    Serial.println("Under Car!");
  }else{
    Serial.println("Not Under Car!");
  }
    
  Serial.print("Z: ");
  Serial.print(z, 4);
  Serial.print("X: ");
  Serial.print(x, 4);
  Serial.print("Y: ");
  Serial.print(y, 4);
  Serial.println("");
  Serial.println("--------------------------------------------------------------------------------------");
  Serial.println("");
  delay(1000);
  //}

}
