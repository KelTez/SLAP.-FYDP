#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

/*CONSTANTS FOR MATH USE*/
#define SENSOR_NUM_SAMPLES 5
#define MAX_READS_BEFORE_EXIT 3

float filteredMean(float[]);
float calculateSD(float data[], float mean);
float calculateMean(float data[]);
float calculateAdjustedMean(float data[], float mean, float stdDev);
float stateBuffer(); //if previious state of parking lot changes, do multiple reads before we decide its changed. TO WRITE AND DECIDE THE VARS AND HOW IT WORKS

#endif //FUNCTIONS_H
