
#include "sensor.h"

void sensor_read(SensorData *data)
{
    static unsigned int sample = 0;

    sample++;

    data->temperature = 25.0f + (float)sample;
    data->humidity = 50.0f + (float)(sample * 2);
}
