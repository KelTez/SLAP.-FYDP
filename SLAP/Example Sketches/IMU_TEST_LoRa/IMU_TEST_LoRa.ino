#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <LoRa.h>

#define NUM_CALIB_READS 10  
#define LEFT_BOUND_CHANGE 0 //how much we can shift left from our zbound before we are def under a car
#define RIGHT_BOUND_CHANGE 0 //how much we can shift left from our zbound before we are def under a car\ 
//^ the above assumes that the location of the pod is center

Adafruit_BNO055 bno = Adafruit_BNO055(55);
float zBadRange[NUM_CALIB_READS];
float zBadRightBound,zBadLeftBound= 0;
int calibrate = 1;
int count = 0;
int counter = 0;
//define the pins used by the transceiver module
#define ss 8
#define rst 4
#define dio0 3

void IMUCalibrate(sensors_event_t event){
  
  /* Display the floating point data */
  if(calibrate){

    for(int i = 0; i < NUM_CALIB_READS; i++){
      bno.getEvent(&event);
      zBadRange[i] = event.magnetic.z;
      Serial.print(zBadRange[i]);
      Serial.print("   ");
      delay(10);
    }
  


}}

void setup(void) 
{

  Serial.begin(115200);
  while (!Serial);
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
    
  bno.setExtCrystalUse(true);

  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 

  

  bno.getEvent(&event);

  float z = event.magnetic.z;
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

   }

    zBadLeftBound -= LEFT_BOUND_CHANGE;
    zBadRightBound += RIGHT_BOUND_CHANGE;
    Serial.println("");
    Serial.println("Done Calibration");
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
  //Send LoRa packet to receiver
  LoRa.beginPacket(); 
  LoRa.print("Z: ");
  String mystring;
  mystring = String(z);
  LoRa.print(mystring);
  LoRa.print(counter);
  Serial.println("PACKET SENT!");
  LoRa.endPacket();
  counter++;
  delay(1000);
  //}
}
