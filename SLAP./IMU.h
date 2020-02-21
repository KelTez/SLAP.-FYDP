#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

void initIMU();
sensors_vec_t readIMUValue();
uint8_t magnetState(); //get magnet state from reading IMU value

#endif //IMU_H
