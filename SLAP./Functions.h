#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

/*CONSTANTS FOR MATH USE*/
#define SENSOR_NUM_SAMPLES 5
#define MAX_READS_BEFORE_EXIT 3
#define X_MAG_UPPER_THRESH 10 //placeholder values
#define X_MAG_LOWER_THRESH 5
#define Y_MAG_UPPER_THRESH 10
#define Y_MAG_LOWER_THRESH 5
#define Z_MAG_UPPER_THRESH 10
#define Z_MAG_LOWER_THRESH 5

uint8_t getParkState(uint8_t distState, uint8_t magState, uint8_t pin, uint8_t currentCount);
uint8_t bufferedRead();
float filteredMean(float[]);
float calculateSD(float data[], float mean);
float calculateMean(float data[]);
float calculateAdjustedMean(float data[], float mean, float stdDev);

#endif //FUNCTIONS_H
