#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define NUM_CALIB_READS 10  
#define LEFT_BOUND_CHANGE 4 //how much we can shift left from our zbound before we are def under a car
#define RIGHT_BOUND_CHANGE 4 //how much we can shift left from our zbound before we are def under a car\ 
//^ the above assumes that the location of the pod is center

static uint8_t calibrate=1;
static float zBadRange[NUM_CALIB_READS];
static float zBadRightBound = -100000;
static float zBadLeftBound = 100000;
static Adafruit_BNO055 bno = Adafruit_BNO055();
static imu::Vector<3> mag_vector;
void initIMU();
void IMUCalibrate();
uint8_t magnetState(); 
sensors_vec_t readIMUValue();
static float savedMagValue;

#endif //IMU_H
