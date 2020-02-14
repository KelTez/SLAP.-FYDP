#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#define SENSOR_NUM_SAMPLES 5
#define MAX_READS_BEFORE_EXIT 10

uint8_t getParkState(uint8_t distState, uint8_t magState, uint8_t pin, uint8_t currentCount);
uint8_t bufferedRead();
float filteredMean(float[]);
float calculateSD(float data[], float mean);
float calculateMean(float data[]);
float calculateAdjustedMean(float data[], float mean, float stdDev);
uint8_t readIMUValue();
#endif //FUNCTIONS_H
