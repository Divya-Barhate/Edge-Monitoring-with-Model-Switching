#ifndef FEATURE_H
#define FEATURE_H

#include "sensor.h"

typedef struct
{
    float temperature;
    float humidity;
    float temperature_rate;
    float humidity_rate;
    float temperature_average;
} FeatureData;

void feature_extract(const SensorData *current,
                     const SensorData *previous,
                     float temperature_average,
                     FeatureData *features);

#endif