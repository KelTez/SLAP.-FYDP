#ifndef IMU_H
#define IMU_H
/*TO CHANGE LATER*/
#include <Arduino.h>

uint8_t readIMUValue();
void setupIMU(void);
void getIMUData(void);
void getRawIMUData(void);
void debugIMUData(void);
void calibrateIMU(void);
bool didDetectMagnet(void);

#endif //IMU_H
