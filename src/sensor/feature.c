#include "feature.h"

void feature_extract(const SensorData *current,
                     const SensorData *previous,
                     float temperature_average,
                     FeatureData *features)
{
    features->temperature = current->temperature;
    features->humidity = current->humidity;

    features->temperature_rate =
        current->temperature - previous->temperature;

    features->humidity_rate =
        current->humidity - previous->humidity;

    features->temperature_average = temperature_average;
}