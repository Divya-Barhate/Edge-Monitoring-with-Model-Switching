#ifndef SENSOR_H
#define SENSOR_H

typedef struct
{
    float temperature;
    float humidity;
} SensorData;

void sensor_read(SensorData *data);

#endif